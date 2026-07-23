import datetime
import os
import urllib.request
import urllib.error
from typing import Any
from uuid import uuid4

from models import Author, Publisher, Book, BookCategory, BookTranslation, BookBookCategory
from database import get_db
from storage import upload_cover
from sqlalchemy.orm import Session

# ---------------------------------------------------------------------------
# Static reference data
# ---------------------------------------------------------------------------

PUBLISHERS = [
    "Penguin Random House", "HarperCollins", "Simon & Schuster",
    "Macmillan Publishers", "Hachette Livre", "Scholastic",
    "Bloomsbury Publishing", "Tor Books", "Orbit Books", "Audible Originals",
    "Houghton Mifflin Harcourt", "Wizards of the Coast", "Black Library",
    "W. W. Norton & Company",
]

CATEGORIES = [
    # Top-level genres
    ("Fantasy", None),
    ("Sci-Fi", None),
    ("Mystery", None),
    ("Romance", None),
    ("Horror", None),
    ("Biography", None),
    ("History", None),
    ("Classical", None),
    ("Self-improvement", None),
    ("Comedy", None),
    ("Thriller", None),
    ("Philosophy", None),

    # Fantasy subgenres
    ("Epic Fantasy", "Fantasy"),
    ("Dark Fantasy", "Fantasy"),
    ("Urban Fantasy", "Fantasy"),
    ("Fairy Tales", "Fantasy"),
    ("Mythology", "Fantasy"),
    ("Magical Realism", "Fantasy"),

    # Sci-Fi subgenres
    ("Space Opera", "Sci-Fi"),
    ("Cyberpunk", "Sci-Fi"),
    ("Hard Sci-Fi", "Sci-Fi"),
    ("Dystopian", "Sci-Fi"),
    ("Time Travel", "Sci-Fi"),

    # Mystery subgenres
    ("Cozy Mystery", "Mystery"),
    ("Crime Thriller", "Mystery"),
    ("Noir", "Mystery"),
    ("Crime", "Mystery"),

    # Romance subgenres
    ("Contemporary Romance", "Romance"),
    ("Historical Romance", "Romance"),
    ("Paranormal Romance", "Romance"),
    ("Romantic Comedy", "Romance"),

    # Horror subgenres
    ("Psychological Horror", "Horror"),
    ("Supernatural Horror", "Horror"),
    ("Cosmic Horror", "Horror"),

    # Biography subgenres
    ("Memoir", "Biography"),
    ("Autobiography", "Biography"),
    ("Political Bio", "Biography"),

    # History subgenres
    ("Ancient History", "History"),
    ("Modern History", "History"),
    ("Military History", "History"),

    # Classical subgenres
    ("Greek Classics", "Classical"),
    ("Roman Literature", "Classical"),
    ("Medieval Literature", "Classical"),
    ("Enlightenment", "Classical"),

    # Self-improvement subgenres
    ("Personal Development", "Self-improvement"),
    ("Productivity", "Self-improvement"),
    ("Mindfulness", "Self-improvement"),
    ("Leadership", "Self-improvement"),

    # Comedy subgenres
    ("Satire", "Comedy"),
    ("Humorous Memoir", "Comedy"),
    ("Parody", "Comedy"),

    # Thriller subgenres
    ("Psychological Thriller", "Thriller"),
    ("Political Thriller", "Thriller"),
    ("Legal Thriller", "Thriller"),
    ("Spy Thriller", "Thriller"),

    # Philosophy subgenres
    ("Ancient Philosophy", "Philosophy"),
    ("Modern Philosophy", "Philosophy"),
    ("Ethics", "Philosophy"),
    ("Existentialism", "Philosophy"),
]

ACTIVE_ISBNS = {
    "978-0486419268",
    "978-1599869773",
    "978-0140455113",
}

BOOKS: list[dict[str, Any]] = [
    {
        "author": "Karel Čapek",
        "publisher": "Tor Books",
        "subgenre": "Dystopian",
        "isbn": "978-0486419268",
        "price": 8.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "R.U.R.",
             "description": "Karel Čapek's 1920 play that coined the word 'robot'. Rossum's Universal Robots manufactures artificial workers to serve humanity — until they develop contempt for their masters and revolt."},
            {"lang": "cs", "title": "R.U.R.",
             "description": "Hra Karla Čapka z roku 1920, která zavedla slovo „robot“. Rossumovi univerzální roboti vyrábějí umělé pracovníky, kteří mají sloužit lidstvu — dokud se nevzbouří proti svým pánům."},
            {"lang": "de", "title": "R.U.R.",
             "description": "Karel Čapeks Theaterstück von 1920, das das Wort »Roboter« prägte. Rossums Universal-Roboter produziert künstliche Arbeiter für die Menschheit — bis diese ihre Schöpfer verachten und sich gegen sie auflehnen."},
            {"lang": "es", "title": "R.U.R.",
             "description": "La obra de 1920 de Karel Čapek que acuñó la palabra 'robot'. Los Robots Universales de Rossum fabrican trabajadores artificiales para servir a la humanidad, hasta que se rebelan contra sus creadores."},
            {"lang": "ar", "title": "ر.أو.ر.",
             "description": "مسرحية كاريل تشابيك عام 1920 التي ابتكرت كلمة «روبوت». تُنتج شركة روسوم للروبوتات العالمية عمالاً اصطناعيين لخدمة البشرية، حتى يطوروا ازدراءً لأسيادهم ويثوروا عليهم."},
        ],
    },
    {
        "author": "Sun Tzu",
        "publisher": "Penguin Random House",
        "subgenre": "Military History",
        "isbn": "978-1599869773",
        "price": 9.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "The Art of War",
             "description": "Written over two thousand years ago, this compact masterwork on strategy, deception, and leadership remains essential reading in military affairs, business, and politics alike."},
            {"lang": "cs", "title": "Umění války",
             "description": "Toto stručné mistrovské dílo o strategii, klamu a vedení, napsané před více než dvěma tisíci lety, zůstává zásadní četbou ve vojenství, byznysu i politice."},
            {"lang": "de", "title": "Die Kunst des Krieges",
             "description": "Vor mehr als zweitausend Jahren verfasst, bleibt dieses kompakte Meisterwerk über Strategie, Täuschung und Führung in Militärangelegenheiten, Wirtschaft und Politik unverzichtbare Lektüre."},
            {"lang": "es", "title": "El arte de la guerra",
             "description": "Escrito hace más de dos mil años, este compacto trabajo maestro sobre estrategia, engaño y liderazgo sigue siendo una lectura esencial en asuntos militares, negocios y política."},
            {"lang": "ar", "title": "فن الحرب",
             "description": "كُتب منذ أكثر من ألفي عام، وهذا العمل الموجز عن الاستراتيجية والخداع والقيادة لا يزال قراءةً أساسية في الشؤون العسكرية والأعمال والسياسة على حد سواء."},
        ],
    },
    {
        "author": "Plato",
        "publisher": "Penguin Random House",
        "subgenre": "Ancient Philosophy",
        "isbn": "978-0140455113",
        "price": 7.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "The Republic",
             "description": "Plato's foundational Socratic dialogue on justice, the ideal state, and the philosopher-king. Through Socrates, Plato argues that the just city must be ruled by those who possess wisdom and virtue, and explores the nature of reality through the allegory of the cave."},
            {"lang": "cs", "title": "Republika",
             "description": "Platonův základní sokratovský dialog o spravedlnosti, ideálním státě a filosofu-vládci. Prostřednictvím Sókrata Platon tvrdí, že spravedlivé město mají řídit ti, kdo mají moudrost a ctnost."},
            {"lang": "de", "title": "Der Staat",
             "description": "Platons grundlegendes sokratisches Gespräch über Gerechtigkeit, den idealen Staat und den Philosophen-König. Sokrates legt dar, dass eine gerechte Stadt von weisen und tugendhaften Menschen regiert werden muss."},
            {"lang": "es", "title": "La República",
             "description": "El diálogo socrático fundacional de Platón sobre la justicia, el estado ideal y el filósofo-rey. A través de Sócrates, Platón argumenta que la ciudad justa debe estar gobernada por quienes poseen sabiduría y virtud."},
            {"lang": "ar", "title": "الجمهورية",
             "description": "حوار أفلاطون السقراطي التأسيسي حول العدالة والدولة المثالية وملك الفلاسفة. عبر شخصية سقراط، يؤكد أفلاطون أن المدينة العادلة يجب أن يحكمها من يمتلكون الحكمة والفضيلة."},
        ],
    },

    # ── Sci-Fi / Dystopian ───────────────────────────────────────────────────
    {
        "author": "Frank Herbert",
        "publisher": "Penguin Random House",
        "subgenre": "Space Opera",
        "isbn": "978-0441013593",
        "price": 18.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "Dune",
             "description": "On the desert planet Arrakis, young Paul Atreides must navigate politics, religion, and survival as he rises to lead the native Fremen against imperial forces."},
            {"lang": "cs", "title": "Duna",
             "description": "Na pouštní planetě Arrakis musí mladý Paul Atreides proplouvat politikou, náboženstvím a bojem o přežití, aby dovedl fremeny k odporu proti imperiálním silám."},
            {"lang": "de", "title": "Dune — Der Wüstenplanet",
             "description": "Auf dem Wüstenplaneten Arrakis muss der junge Paul Atreides politischen Intrigen, Religion und Überleben trotzen, um die einheimischen Fremen anzuführen."},
            {"lang": "es", "title": "Dune",
             "description": "En el planeta desértico Arrakis, el joven Paul Atreides debe navegar entre política, religión y supervivencia mientras lidera a los Fremen contra las fuerzas imperiales."},
            {"lang": "ar", "title": "كوكب الرمال",
             "description": "على كوكب أرّاكيس الصحراوي، يجد الشاب بول أتريديس نفسه في خضم صراعات سياسية ودينية وتحديات البقاء، وهو يقود الفريمن ضد القوى الإمبراطورية."},
        ],
    },
    {
        "author": "George Orwell",
        "publisher": "Penguin Random House",
        "subgenre": "Dystopian",
        "isbn": "978-0451524935",
        "price": 13.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "Nineteen Eighty-Four",
             "description": "In a totalitarian superstate ruled by Big Brother, Winston Smith secretly rebels against the all-seeing Party and falls into a doomed love affair."},
            {"lang": "cs", "title": "1984",
             "description": "V totalitním superstátě ovládaném Velkým bratrem se Winston Smith tajně bouří proti vševědoucí Straně a prožívá milostný vztah odsouzený k zániku."},
            {"lang": "de", "title": "1984",
             "description": "In einem totalitären Überwachungsstaat unter Big Brother rebelliert Winston Smith heimlich gegen die allwissende Partei und beginnt eine verbotene Liebesaffäre."},
            {"lang": "es", "title": "1984",
             "description": "En un estado totalitario gobernado por el Gran Hermano, Winston Smith se rebela en secreto contra el omnisciente Partido y vive un amor condenado."},
            {"lang": "ar", "title": "1984",
             "description": "في دولة شمولية يحكمها الأخ الأكبر، يتمرد وينستون سميث سراً على الحزب العليم بكل شيء، ويقع في قصة حب محكوم عليها بالفشل."},
        ],
    },
    {
        "author": "Aldous Huxley",
        "publisher": "HarperCollins",
        "subgenre": "Dystopian",
        "isbn": "978-0060850524",
        "price": 13.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "Brave New World",
             "description": "In a future where humans are factory-bred and conditioned into social castes, Bernard Marx questions the shallow pleasures of a society engineered for stability over truth."},
            {"lang": "cs", "title": "Konec civilizace",
             "description": "V budoucnosti, kde jsou lidé sériově vyráběni a podmiňováni do společenských kast, Bernard Marx zpochybňuje povrchní požitky společnosti vytvořené pro stabilitu."},
            {"lang": "de", "title": "Schöne neue Welt",
             "description": "In einer Zukunft, in der Menschen fabrikmäßig gezüchtet und in soziale Kasten konditioniert werden, hinterfragt Bernard Marx die oberflächlichen Freuden einer auf Stabilität ausgelegten Gesellschaft."},
            {"lang": "es", "title": "Un mundo feliz",
             "description": "En un futuro donde los humanos son fabricados en serie y condicionados en castas sociales, Bernard Marx cuestiona los placeres superficiales de una sociedad diseñada para la estabilidad."},
            {"lang": "ar", "title": "عالم جديد شجاع",
             "description": "في مستقبل يُنتج فيه البشر في المصانع ويُكيَّفون ضمن طبقات اجتماعية، يشكك برنارد ماركس في الملذات السطحية لمجتمع مُهندَس من أجل الاستقرار لا الحقيقة."},
        ],
    },

    # ── Philosophy / Classics ────────────────────────────────────────────────
    {
        "author": "Antoine de Saint-Exupéry",
        "publisher": "Hachette Livre",
        "subgenre": "Modern Philosophy",
        "isbn": "978-2070408504",
        "price": 11.99,
        "currency": "EUR",
        "translations": [
            {"lang": "cs", "title": "Malý princ",
             "description": "Aviatik ztroskotaný v poušti potkává záhadného malého prince z jiné planety, který mu předává zásadní pravdy o životě a lásce."},
            {"lang": "en", "title": "The Little Prince",
             "description": "A pilot stranded in the desert meets a mysterious little prince from another planet, who shares profound truths about life, love, and what truly matters."},
            {"lang": "de", "title": "Der kleine Prinz",
             "description": "Ein Pilot, der in der Wüste gestrandet ist, begegnet einem rätselhaften kleinen Prinzen von einem anderen Planeten, der tiefe Wahrheiten über das Leben teilt."},
            {"lang": "es", "title": "El Principito",
             "description": "Un piloto varado en el desierto conoce a un misterioso principito de otro planeta, que le comparte profundas verdades sobre la vida, el amor y lo que realmente importa."},
            {"lang": "ar", "title": "الأمير الصغير",
             "description": "طيار يتعطل في الصحراء يلتقي بأمير صغير غامض من كوكب آخر، يشاركه حقائق عميقة عن الحياة والحب وما يستحق الاهتمام حقاً."},
        ],
    },
    {
        "author": "Miguel de Cervantes",
        "publisher": "Penguin Random House",
        "subgenre": "Enlightenment",
        "isbn": "978-0060934347",
        "price": 14.99,
        "currency": "USD",
        "translations": [
            {"lang": "es", "title": "Don Quijote de la Mancha",
             "description": "Un hidalgo manchego, enloquecido por las novelas de caballerías, sale al mundo convencido de ser caballero andante, acompañado de su fiel escudero Sancho Panza."},
            {"lang": "en", "title": "Don Quixote",
             "description": "A Spanish nobleman, driven mad by chivalric romances, sets out as a self-styled knight-errant with his earthy squire Sancho Panza, tilting at windmills across La Mancha."},
            {"lang": "cs", "title": "Don Quijote",
             "description": "Španělský zeman, pomatený rytířskými romány, vyráží do světa jako potulný rytíř po boku svého věrného zbrojnoše Sancha Panzy."},
            {"lang": "de", "title": "Don Quijote von der Mancha",
             "description": "Ein spanischer Edelmann, durch Ritterromane dem Wahnsinn verfallen, zieht als selbsternannter Ritter mit seinem treuen Knappen Sancho Panza durch La Mancha."},
            {"lang": "ar", "title": "دون كيخوته",
             "description": "نبيل إسباني تصرّعه روايات الفروسية يخرج كفارس جوّال مع مساعده سانشو بانزا، يصارع طواحين الهواء عبر لامانشا."},
        ],
    },
    {
        "author": "Fyodor Dostoevsky",
        "publisher": "Penguin Random House",
        "subgenre": "Existentialism",
        "isbn": "978-0486415871",
        "price": 12.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "Crime and Punishment",
             "description": "A destitute student in St. Petersburg murders a pawnbroker and spends the rest of the novel tormented by guilt, police suspicion, and a slow path toward redemption."},
            {"lang": "cs", "title": "Zločin a trest",
             "description": "Zchudlý student v Petrohradě zavraždí lichvářku a poté prochází vinou, policejním podezřením a pomalou cestou k vykoupení."},
            {"lang": "de", "title": "Schuld und Sühne",
             "description": "Ein mittelloser Student in St. Petersburg ermordet eine Pfandleiherin und wird danach von Schuldgefühlen, Polizeiverdacht und einem langsamen Weg zur Erlösung geplagt."},
            {"lang": "es", "title": "Crimen y castigo",
             "description": "Un estudiante indigente en San Petersburgo asesina a una prestamista y pasa el resto de la novela atormentado por la culpa, la sospecha policial y un lento camino hacia la redención."},
            {"lang": "ar", "title": "الجريمة والعقاب",
             "description": "طالب معدم في سانت بطرسبرغ يرتكب جريمة قتل ثم يتخبط بين الذنب والشك البوليسي في رحلة طويلة ومضنية نحو الخلاص."},
        ],
    },

    # ── Self-improvement / Magical Realism ───────────────────────────────────
    {
        "author": "Paulo Coelho",
        "publisher": "HarperCollins",
        "subgenre": "Personal Development",
        "isbn": "978-0062315007",
        "price": 14.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "The Alchemist",
             "description": "A young Andalusian shepherd leaves his flock to follow a recurring dream about treasure near the Egyptian pyramids, and discovers that the journey itself is the reward."},
            {"lang": "cs", "title": "Alchymista",
             "description": "Mladý andaluský pastýř opouští své stádo, aby následoval opakující se sen o pokladu u egyptských pyramid, a zjišťuje, že skutečnou odměnou je samotná cesta."},
            {"lang": "de", "title": "Der Alchimist",
             "description": "Ein junger andalusischer Hirt verlässt seine Herde, um einem wiederkehrenden Traum von einem Schatz nahe den ägyptischen Pyramiden zu folgen."},
            {"lang": "es", "title": "El Alquimista",
             "description": "Un joven pastor andaluz deja su rebaño para seguir un sueño recurrente sobre un tesoro cerca de las pirámides de Egipto, y descubre que el viaje mismo es la recompensa."},
            {"lang": "ar", "title": "الخيميائي",
             "description": "راعٍ أندلسي شاب يترك قطيعه ليتبع حلماً متكرراً عن كنز بالقرب من أهرامات مصر، ليكتشف أن الرحلة ذاتها هي المكافأة الحقيقية."},
        ],
    },
    {
        "author": "Gabriel García Márquez",
        "publisher": "Penguin Random House",
        "subgenre": "Magical Realism",
        "isbn": "978-0060883287",
        "price": 16.99,
        "currency": "USD",
        "translations": [
            {"lang": "es", "title": "Cien años de soledad",
             "description": "La saga de la familia Buendía a lo largo de siete generaciones en el pueblo mítico de Macondo, donde lo real y lo mágico se entretejen durante un siglo de historia latinoamericana."},
            {"lang": "en", "title": "One Hundred Years of Solitude",
             "description": "The Buendía family saga across seven generations in the mythical town of Macondo, where reality and magic intertwine across a century of Latin American history."},
            {"lang": "cs", "title": "Sto roků samoty",
             "description": "Sága rodu Buendíů napříč sedmi generacemi v mýtickém městečku Macondo, kde se realita a magie prolínají během jednoho století latinskoamerických dějin."},
            {"lang": "de", "title": "Hundert Jahre Einsamkeit",
             "description": "Die Saga der Familie Buendía über sieben Generationen im mythischen Städtchen Macondo, wo Realität und Magie über ein Jahrhundert lateinamerikanischer Geschichte verschmelzen."},
            {"lang": "ar", "title": "مئة عام من العزلة",
             "description": "ملحمة عائلة بوينديا عبر سبعة أجيال في بلدة ماكوندو الأسطورية، حيث يتشابك الواقع والسحر على مدى قرن من تاريخ أمريكا اللاتينية."},
        ],
    },

    # ── Crime / Mystery ──────────────────────────────────────────────────────
    {
        "author": "Umberto Eco",
        "publisher": "Hachette Livre",
        "subgenre": "Crime",
        "isbn": "978-0156001311",
        "price": 15.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "The Name of the Rose",
             "description": "In a 14th-century Italian abbey, Franciscan monk William of Baskerville and his novice Adso investigate a series of mysterious deaths surrounding a forbidden book."},
            {"lang": "cs", "title": "Jméno růže",
             "description": "V italském opatství 14. století vyšetřuje františkánský mnich Vilém z Baskervillu se svým novicem Adsonem sérii záhadných úmrtí spojených se zakázanou knihou."},
            {"lang": "de", "title": "Der Name der Rose",
             "description": "In einem norditalienischen Kloster des 14. Jahrhunderts untersucht der Franziskanermönch Wilhelm von Baskerville eine Serie rätselhafter Todesfälle um ein verbotenes Buch."},
            {"lang": "es", "title": "El nombre de la rosa",
             "description": "En una abadía italiana del siglo XIV, el monje franciscano Guillermo de Baskerville investiga una serie de muertes misteriosas en torno a un libro prohibido."},
            {"lang": "ar", "title": "اسم الوردة",
             "description": "في دير إيطالي من القرن الرابع عشر، يحقق الراهب الفرنسيسكاني غيوم من باسكيرفيل في سلسلة وفيات غامضة مرتبطة بكتاب محظور."},
        ],
    },

    # ── Harry Potter ─────────────────────────────────────────────────────────
    {
        "author": "J.K. Rowling",
        "publisher": "Bloomsbury Publishing",
        "subgenre": "Epic Fantasy",
        "isbn": "978-0439708180",
        "price": 14.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "Harry Potter and the Philosopher's Stone",
             "description": "An orphaned boy raised by neglectful relatives discovers on his eleventh birthday that he is a wizard and is admitted to Hogwarts School of Witchcraft and Wizardry."},
            {"lang": "cs", "title": "Harry Potter a Kámen mudrců",
             "description": "Osiřelý chlapec vychovávaný zanedbávajícími příbuznými ve svých jedenácti letech zjistí, že je čaroděj, a nastupuje do školy čar a kouzel v Bradavicích."},
            {"lang": "de", "title": "Harry Potter und der Stein der Weisen",
             "description": "Ein verwaister Junge, bei gleichgültigen Verwandten aufgewachsen, entdeckt an seinem elften Geburtstag, dass er ein Zauberer ist, und wird in Hogwarts aufgenommen."},
            {"lang": "es", "title": "Harry Potter y la piedra filosofal",
             "description": "Un niño huérfano criado por unos parientes indiferentes descubre en su undécimo cumpleaños que es mago y es admitido en el Colegio Hogwarts."},
            {"lang": "ar", "title": "هاري بوتر وحجر الفيلسوف",
             "description": "صبي يتيم يتربى عند أقاربه المهملين يكتشف في عيد ميلاده الحادي عشر أنه ساحر، ويُقبل في مدرسة هوغوورتس للسحر والشعوذة."},
        ],
    },
    {
        "author": "J.K. Rowling",
        "publisher": "Bloomsbury Publishing",
        "subgenre": "Epic Fantasy",
        "isbn": "978-0439064873",
        "price": 14.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "Harry Potter and the Chamber of Secrets",
             "description": "Back at Hogwarts for his second year, Harry Potter must face a new terror: the Chamber of Secrets has been opened, unleashing a monster that is Petrifying students."},
            {"lang": "cs", "title": "Harry Potter a Tajemná komnata",
             "description": "Po návratu do Bradavic ve druhém ročníku musí Harry čelit nové hrozbě: Tajemná komnata byla otevřena a vypustila nestvůru, která zkameněním napadá studenty."},
            {"lang": "de", "title": "Harry Potter und die Kammer des Schreckens",
             "description": "In seinem zweiten Jahr in Hogwarts muss Harry Potter einer neuen Bedrohung begegnen: Die Kammer des Schreckens wurde geöffnet und ein Monster versteinert Schüler."},
            {"lang": "es", "title": "Harry Potter y la Cámara Secreta",
             "description": "De vuelta en Hogwarts para su segundo año, Harry Potter debe enfrentarse a un nuevo terror: la Cámara Secreta ha sido abierta, liberando un monstruo que petrifica a los estudiantes."},
            {"lang": "ar", "title": "هاري بوتر وحجرة الأسرار",
             "description": "في عامه الثاني في هوغوورتس، يواجه هاري بوتر خطراً جديداً: فُتحت حجرة الأسرار وأُطلق منها وحش يحوّل الطلاب إلى حجارة."},
        ],
    },
    {
        "author": "J.K. Rowling",
        "publisher": "Bloomsbury Publishing",
        "subgenre": "Epic Fantasy",
        "isbn": "978-0439136358",
        "price": 14.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "Harry Potter and the Prisoner of Azkaban",
             "description": "Harry discovers that a dangerous prisoner has escaped from the wizard prison Azkaban and seems to be hunting him, while learning the truth about his parents' past."},
            {"lang": "cs", "title": "Harry Potter a vězeň z Azkabanu",
             "description": "Harry se dozvídá, že z Azkabanu uprchl nebezpečný vězeň, který ho zřejmě pronásleduje, a zároveň odhaluje pravdu o minulosti svých rodičů."},
            {"lang": "de", "title": "Harry Potter und der Gefangene von Askaban",
             "description": "Harry erfährt, dass ein gefährlicher Gefangener aus Askaban geflohen ist und ihn zu verfolgen scheint, während er die Wahrheit über die Vergangenheit seiner Eltern aufdeckt."},
            {"lang": "es", "title": "Harry Potter y el Prisionero de Azkaban",
             "description": "Harry descubre que un peligroso prisionero ha escapado de Azkaban y parece perseguirle, mientras aprende la verdad sobre el pasado de sus padres."},
            {"lang": "ar", "title": "هاري بوتر وسجين أزكابان",
             "description": "يكتشف هاري أن سجيناً خطيراً فرّ من سجن أزكابان ويبدو أنه يطارده، فيما يتعرف على حقيقة ماضي والديه."},
        ],
    },
    {
        "author": "J.K. Rowling",
        "publisher": "Bloomsbury Publishing",
        "subgenre": "Epic Fantasy",
        "isbn": "978-0439139601",
        "price": 15.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "Harry Potter and the Goblet of Fire",
             "description": "Harry is mysteriously entered into the dangerous Triwizard Tournament, forcing him to compete in deadly tasks while Voldemort's return grows ever more imminent."},
            {"lang": "cs", "title": "Harry Potter a Ohnivý pohár",
             "description": "Harry je záhadně přihlášen do nebezpečného Turnaje tří kouzelnických škol a musí plnit smrtící úkoly, zatímco návrat Voldemorta je stále nevyhnutelnější."},
            {"lang": "de", "title": "Harry Potter und der Feuerkelch",
             "description": "Harry wird auf mysteriöse Weise in das gefährliche Trimagische Turnier eingetragen und muss tödliche Aufgaben bewältigen, während Voldemorts Rückkehr immer bedrohlicher wird."},
            {"lang": "es", "title": "Harry Potter y el Cáliz de Fuego",
             "description": "Harry es misteriosamente inscrito en el peligroso Torneo de los Tres Magos y se ve obligado a competir en pruebas mortales mientras el regreso de Voldemort es cada vez más inminente."},
            {"lang": "ar", "title": "هاري بوتر وكأس النار",
             "description": "يُدرج اسم هاري بطريقة غامضة في بطولة الساحرين الثلاثة الخطيرة، مما يجبره على خوض مهام مميتة فيما يلوح عودة فولدمورت في الأفق."},
        ],
    },
    {
        "author": "J.K. Rowling",
        "publisher": "Bloomsbury Publishing",
        "subgenre": "Epic Fantasy",
        "isbn": "978-0439358071",
        "price": 16.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "Harry Potter and the Order of the Phoenix",
             "description": "Dismissed and isolated after warning of Voldemort's return, Harry must navigate a corrupt Ministry of Magic and a cruel new teacher at Hogwarts while a secret society fights in the shadows."},
            {"lang": "cs", "title": "Harry Potter a Fénixův řád",
             "description": "Po varování před Voldemortovým návratem je Harry odmítán a izolován; musí čelit zkorumpovanému Ministerstvu kouzel i kruté nové učitelce, zatímco tajný řád bojuje ve stínech."},
            {"lang": "de", "title": "Harry Potter und der Orden des Phönix",
             "description": "Nach seiner Warnung vor Voldemorts Rückkehr isoliert und abgelehnt, muss Harry ein korruptes Zaubereiministerium und eine grausame neue Lehrerin in Hogwarts überstehen."},
            {"lang": "es", "title": "Harry Potter y la Orden del Fénix",
             "description": "Rechazado tras advertir sobre el regreso de Voldemort, Harry debe enfrentarse a un Ministerio corrupto y una nueva profesora cruel mientras una sociedad secreta lucha en las sombras."},
            {"lang": "ar", "title": "هاري بوتر وجماعة العنقاء",
             "description": "مرفوض ومعزول بعد تحذيره من عودة فولدمورت، يواجه هاري وزارة السحر الفاسدة ومعلمة قاسية جديدة، فيما تناضل جماعة سرية في الظلام."},
        ],
    },
    {
        "author": "J.K. Rowling",
        "publisher": "Bloomsbury Publishing",
        "subgenre": "Epic Fantasy",
        "isbn": "978-0439784542",
        "price": 16.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "Harry Potter and the Half-Blood Prince",
             "description": "As war looms, Harry studies Voldemort's past with Dumbledore and uncovers the mystery of the Half-Blood Prince's annotated spell book, while darkness spreads across the wizarding world."},
            {"lang": "cs", "title": "Harry Potter a princ dvojí krve",
             "description": "Jak se blíží válka, Harry s Brumbálem zkoumá Voldemortovu minulost a odhaluje tajemství knihy kouzel s poznámkami prince dvojí krve."},
            {"lang": "de", "title": "Harry Potter und der Halbblutprinz",
             "description": "Während der Krieg näher rückt, erforscht Harry mit Dumbledore Voldemorts Vergangenheit und lüftet das Geheimnis des annotierten Zauberbuchs des Halbblutprinzen."},
            {"lang": "es", "title": "Harry Potter y el Misterioso Príncipe",
             "description": "Con la guerra inminente, Harry estudia el pasado de Voldemort con Dumbledore y descubre el misterio del libro de hechizos anotado del Misterioso Príncipe."},
            {"lang": "ar", "title": "هاري بوتر والأمير الهجين",
             "description": "مع اقتراب الحرب، يدرس هاري ماضي فولدمورت مع دمبلدور ويكشف لغز كتاب التعويذات المعلَّق للأمير الهجين، فيما يعمّ الظلام العالم السحري."},
        ],
    },
    {
        "author": "J.K. Rowling",
        "publisher": "Bloomsbury Publishing",
        "subgenre": "Epic Fantasy",
        "isbn": "978-0545010221",
        "price": 17.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "Harry Potter and the Deathly Hallows",
             "description": "In the climactic final battle, Harry, Hermione, and Ron hunt Voldemort's Horcruxes while the wizarding world falls under the Dark Lord's rule — and Harry faces the true cost of sacrifice."},
            {"lang": "cs", "title": "Harry Potter a Relikvie smrti",
             "description": "V závěrečné bitvě Harry, Hermiona a Ron pátrají po Voldemortových viteálech, zatímco kouzelnický svět upadá pod vládu Pána zla."},
            {"lang": "de", "title": "Harry Potter und die Heiligtümer des Todes",
             "description": "Im abschließenden Showdown jagen Harry, Hermine und Ron Voldemorts Horkruxe, während die Zauberwelt unter die Herrschaft des Dunklen Lords fällt."},
            {"lang": "es", "title": "Harry Potter y las Reliquias de la Muerte",
             "description": "En la batalla final, Harry, Hermione y Ron cazan los Horrocruxes de Voldemort mientras el mundo mágico cae bajo el dominio del Señor Oscuro."},
            {"lang": "ar", "title": "هاري بوتر ومقدسات الموت",
             "description": "في المعركة الأخيرة الحاسمة، يطارد هاري وهيرميون ورون هوركركسات فولدمورت فيما يسقط العالم السحري تحت سيطرة اللورد المظلم."},
        ],
    },

    # ── Lord of the Rings ────────────────────────────────────────────────────
    {
        "author": "J.R.R. Tolkien",
        "publisher": "Houghton Mifflin Harcourt",
        "subgenre": "Epic Fantasy",
        "isbn": "978-0547928227",
        "price": 12.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "The Hobbit",
             "description": "Bilbo Baggins, a comfort-loving hobbit, is swept into an epic quest by the wizard Gandalf and a company of dwarves to reclaim their homeland from the fearsome dragon Smaug."},
            {"lang": "cs", "title": "Hobit",
             "description": "Bilbo Pytlík, pohodlí milující hobit, je čarodějem Gandalfem a družinou trpaslíků vtažen do epické výpravy za znovuzískáním jejich domova od obávaného draka Šmaka."},
            {"lang": "de", "title": "Der Hobbit",
             "description": "Bilbo Beutlin, ein gemütlicher Hobbit, wird vom Zauberer Gandalf und einer Gruppe von Zwergen in ein episches Abenteuer gezogen, um ihre Heimat vom Drachen Smaug zurückzuerobern."},
            {"lang": "es", "title": "El Hobbit",
             "description": "Bilbo Bolsón, un hobbit amante de la comodidad, es arrastrado a una épica aventura por el mago Gandalf y una compañía de enanos para recuperar su hogar del terrible dragón Smaug."},
            {"lang": "ar", "title": "الهوبيت",
             "description": "يُجرف بيلبو باغينز، الهوبيت المحب للراحة، إلى مغامرة ملحمية بقيادة الساحر غاندالف وزمرة من الأقزام لاسترداد وطنهم من براثن التنين الهائل سموغ."},
        ],
    },
    {
        "author": "J.R.R. Tolkien",
        "publisher": "Houghton Mifflin Harcourt",
        "subgenre": "Epic Fantasy",
        "isbn": "978-0618346257",
        "price": 16.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "The Fellowship of the Ring",
             "description": "Frodo Baggins inherits the One Ring forged by the Dark Lord Sauron and sets out on a perilous journey across Middle-earth with a fellowship of diverse companions."},
            {"lang": "cs", "title": "Společenstvo Prstenu",
             "description": "Frodo Pytlík zdědí Jeden prsten ukutý Temným pánem Sauronem a vydává se na nebezpečnou cestu Středozemím se společenstvem různorodých druhů."},
            {"lang": "de", "title": "Die Gemeinschaft des Ringes",
             "description": "Frodo Beutlin erbt den Einen Ring, geschmiedet vom Dunklen Lord Sauron, und bricht mit einer Gemeinschaft vielfältiger Gefährten auf eine gefährliche Reise auf."},
            {"lang": "es", "title": "La Comunidad del Anillo",
             "description": "Frodo Bolsón hereda el Anillo Único forjado por el Señor Oscuro Sauron y emprende un peligroso viaje por la Tierra Media con una hermandad de compañeros."},
            {"lang": "ar", "title": "رفقة الخاتم",
             "description": "يرث فرودو باغينز الخاتم الأوحد الذي صنعه سيد الظلام سورون، وينطلق في رحلة خطيرة عبر أرض الوسط برفقة صحب من أجناس مختلفة."},
        ],
    },
    {
        "author": "J.R.R. Tolkien",
        "publisher": "Houghton Mifflin Harcourt",
        "subgenre": "Epic Fantasy",
        "isbn": "978-0618346264",
        "price": 16.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "The Two Towers",
             "description": "The fellowship shattered, Frodo and Sam press on toward Mordor guided by the treacherous Gollum, while Aragorn, Legolas, and Gimli race to save their captured companions."},
            {"lang": "cs", "title": "Dvě věže",
             "description": "Společenstvo je rozbito; Frodo a Sam pokračují k Mordoru vedeni zrádným Glumem, zatímco Aragorn, Legolas a Gimli spěchají zachránit své zajaté druhy."},
            {"lang": "de", "title": "Die zwei Türme",
             "description": "Die Gemeinschaft zerbrochen, ziehen Frodo und Sam unter der Führung des hinterlistigen Gollum weiter nach Mordor, während Aragorn, Legolas und Gimli ihre gefangenen Gefährten retten."},
            {"lang": "es", "title": "Las Dos Torres",
             "description": "Tras la ruptura de la hermandad, Frodo y Sam avanzan hacia Mordor guiados por el traicionero Gollum, mientras Aragorn, Legolas y Gimli corren a salvar a sus compañeros capturados."},
            {"lang": "ar", "title": "البرجان",
             "description": "بعد تفرق الرفقة، يواصل فرودو وسام مسيرتهما نحو موردور بقيادة غولّوم المخادع، فيما يسرع أراغورن وليغولاس وغيملي لإنقاذ رفاقهم المأسورين."},
        ],
    },
    {
        "author": "J.R.R. Tolkien",
        "publisher": "Houghton Mifflin Harcourt",
        "subgenre": "Epic Fantasy",
        "isbn": "978-0618346271",
        "price": 16.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "The Return of the King",
             "description": "The War of the Ring reaches its climax as Frodo and Sam near the fires of Mount Doom, while Aragorn leads the last armies of men against the overwhelming forces of Sauron."},
            {"lang": "cs", "title": "Návrat krále",
             "description": "Válka o Prsten vrcholí, když se Frodo a Sam blíží k Hoře osudu a Aragorn vede poslední vojska lidí proti Sauronovým silám."},
            {"lang": "de", "title": "Die Rückkehr des Königs",
             "description": "Der Ringkrieg erreicht seinen Höhepunkt, während Frodo und Sam dem Schicksalsberg näherkommen und Aragorn die letzten Armeen der Menschen gegen Saurons überwältigende Mächte führt."},
            {"lang": "es", "title": "El Retorno del Rey",
             "description": "La Guerra del Anillo llega a su clímax mientras Frodo y Sam se acercan al Monte del Destino y Aragorn lidera los últimos ejércitos de los hombres contra las fuerzas de Sauron."},
            {"lang": "ar", "title": "عودة الملك",
             "description": "تبلغ حرب الخاتم ذروتها بينما يقترب فرودو وسام من نيران جبل القدر، ويقود أراغورن آخر جيوش البشر في مواجهة قوات سورون الساحقة."},
        ],
    },

    # ── Magic: The Gathering ─────────────────────────────────────────────────
    {
        "author": "Jeff Grubb",
        "publisher": "Wizards of the Coast",
        "subgenre": "Epic Fantasy",
        "isbn": "978-0786911707",
        "price": 12.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "The Brothers' War",
             "description": "On the ancient world of Dominaria, the brilliant artificers Urza and Mishra — once brothers — wage a catastrophic war of mechanical titans that will reshape the world forever."},
            {"lang": "cs", "title": "Válka bratrů",
             "description": "Na starobylém světě Dominaria vedou geniální artificéři Urza a Mishra — kdysi bratři — katastrofální válku mechanických titánů, která navždy promění svět."},
            {"lang": "de", "title": "Der Krieg der Brüder",
             "description": "Auf der alten Welt Dominaria führen die brillanten Erfinder Urza und Mishra — einst Brüder — einen katastrophalen Krieg mechanischer Titanen, der die Welt für immer verändern wird."},
            {"lang": "es", "title": "La Guerra de los Hermanos",
             "description": "En el antiguo mundo de Dominaria, los brillantes artífices Urza y Mishra — otrora hermanos — libran una guerra catastrófica de titanes mecánicos que transformará el mundo para siempre."},
            {"lang": "ar", "title": "حرب الأخوة",
             "description": "على عالم دومينيريا القديم، يخوض المخترعان العبقريان أورزا وميشرا — وكانا أخوين — حرباً مدمرة من العمالقة الآلية ستعيد تشكيل العالم إلى الأبد."},
        ],
    },

    # ── H.P. Lovecraft ───────────────────────────────────────────────────────
    {
        "author": "H.P. Lovecraft",
        "publisher": "Penguin Random House",
        "subgenre": "Cosmic Horror",
        "isbn": "978-0143106487",
        "price": 14.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "The Call of Cthulhu and Other Weird Stories",
             "description": "A collection of Lovecraft's most celebrated cosmic horror tales, including the discovery of ancient cults worshipping sleeping gods whose return would annihilate human sanity and civilization."},
            {"lang": "cs", "title": "Volání Cthulhu a jiné podivné příběhy",
             "description": "Sbírka nejslavnějších Lovecraftových kosmických hororů, včetně objevů starých kultů uctívajících spící bohy, jejichž probuzení by zničilo lidský rozum."},
            {"lang": "de", "title": "Der Ruf des Cthulhu und andere gruselige Geschichten",
             "description": "Eine Sammlung von Lovecrafts bekanntesten kosmischen Horrorgeschichten, darunter die Entdeckung alter Kulte, die schlafende Götter verehren, deren Rückkehr den menschlichen Verstand zerstören würde."},
            {"lang": "es", "title": "La llamada de Cthulhu y otros relatos de terror",
             "description": "Una colección de los más célebres relatos de terror cósmico de Lovecraft, incluyendo el descubrimiento de cultos ancestrales que adoran dioses durmientes cuyo retorno aniquilaría la cordura humana."},
            {"lang": "ar", "title": "نداء كثولهو وقصص رعب أخرى",
             "description": "مجموعة من أشهر قصص الرعب الكوني للافكرافت، تشمل اكتشاف طوائف قديمة تعبد آلهة نائمة، وعودتها ستقضي على عقل الإنسان وحضارته."},
        ],
    },
    {
        "author": "H.P. Lovecraft",
        "publisher": "Penguin Random House",
        "subgenre": "Cosmic Horror",
        "isbn": "978-0143105077",
        "price": 13.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "At the Mountains of Madness",
             "description": "A geological expedition to Antarctica uncovers ancient ruins and the remnants of a prehuman civilization — and something that should never have been awakened beneath the ice."},
            {"lang": "cs", "title": "V horách šílenství",
             "description": "Geologická expedice do Antarktidy odhaluje starobylé ruiny a pozůstatky předlidské civilizace — a také něco, co pod ledem nikdy nemělo být probuzeno."},
            {"lang": "de", "title": "Berge des Wahnsinns",
             "description": "Eine geologische Expedition in die Antarktis entdeckt antike Ruinen und Überreste einer vorhumanen Zivilisation — sowie etwas, das unter dem Eis niemals hätte geweckt werden sollen."},
            {"lang": "es", "title": "En las montañas de la locura",
             "description": "Una expedición geológica a la Antártida descubre ruinas antiguas y restos de una civilización prehumana, y algo que nunca debería haber sido despertado bajo el hielo."},
            {"lang": "ar", "title": "في جبال الجنون",
             "description": "تكشف رحلة جيولوجية إلى القارة القطبية الجنوبية عن أطلال قديمة وبقايا حضارة سابقة للإنسان، وشيئاً لم يكن ينبغي إيقاظه تحت الجليد أبداً."},
        ],
    },

    # ── Warhammer 40,000 ─────────────────────────────────────────────────────
    {
        "author": "Dan Abnett",
        "publisher": "Black Library",
        "subgenre": "Space Opera",
        "isbn": "978-1849701129",
        "price": 13.99,
        "currency": "GBP",
        "translations": [
            {"lang": "en", "title": "Horus Rising",
             "description": "In the far future, Warmaster Horus leads the Emperor's armies in their final Great Crusade to reunite humanity — before the seeds of the greatest betrayal in history are sown."},
            {"lang": "cs", "title": "Vzestup Hora",
             "description": "V daleké budoucnosti vede válečný mistr Horus císařova vojska v jejich poslední Velké křížové výpravě, než jsou zaseta semena největší zrady v dějinách."},
            {"lang": "de", "title": "Horus Rising",
             "description": "In ferner Zukunft führt Kriegsherr Horus die Armeen des Imperators in ihrem letzten Großen Kreuzzug, bevor die Saat des größten Verrats in der Geschichte gelegt wird."},
            {"lang": "es", "title": "El Ascenso de Horus",
             "description": "En el futuro lejano, el Señor de la Guerra Horus lidera los ejércitos del Emperador en su Gran Cruzada final, antes de que se siembren las semillas de la mayor traición de la historia."},
            {"lang": "ar", "title": "صعود هورس",
             "description": "في المستقبل البعيد، يقود سيد الحرب هورس جيوش الإمبراطور في حملتهم الكبرى الأخيرة لتوحيد البشرية، قبل أن تُزرع بذور أعظم خيانة في التاريخ."},
        ],
    },
    {
        "author": "Dan Abnett",
        "publisher": "Black Library",
        "subgenre": "Space Opera",
        "isbn": "978-1844161386",
        "price": 12.99,
        "currency": "GBP",
        "translations": [
            {"lang": "en", "title": "First and Only",
             "description": "Colonel-Commissar Ibram Gaunt leads the Tanith First and Only regiment across the blood-soaked battlefields of the far future, forging them into a legendary force against impossible odds."},
            {"lang": "cs", "title": "První a jediní",
             "description": "Plukovník-komisař Ibram Gaunt vede pluk Tanith První a jediní přes krví nasáklá bojiště daleké budoucnosti a formuje z něj legendární sílu."},
            {"lang": "de", "title": "Erster und Einziger",
             "description": "Oberst-Kommissar Ibram Gaunt führt das erste und einzige Regiment Tanith über die blutgetränkten Schlachtfelder der fernen Zukunft und schmiedet sie gegen alle Widerstände zu einer legendären Truppe."},
            {"lang": "es", "title": "Primero y Único",
             "description": "El Coronel-Comisario Ibram Gaunt lidera al regimiento Tanith Primero y Único a través de los ensangrentados campos de batalla del lejano futuro, forjándolos en una fuerza legendaria."},
            {"lang": "ar", "title": "الأول والأخير",
             "description": "يقود العقيد المفوض إبرام غاونت فرقة تانيث الأولى والأخيرة عبر ساحات معارك مروية بالدماء في المستقبل البعيد، محوّلاً إياها إلى قوة أسطورية رغم الصعاب."},
        ],
    },

    # ── Dungeons & Dragons ───────────────────────────────────────────────────
    {
        "author": "R.A. Salvatore",
        "publisher": "Wizards of the Coast",
        "subgenre": "Epic Fantasy",
        "isbn": "978-8477224457",
        "price": 13.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "The Crystal Shard",
             "description": "In the frozen north of the Forgotten Realms, the dark elf Drizzt Do'Urden joins barbarian warrior Wulfgar and halfling rogue Regis to battle a wizard wielding a devastating magical artifact."},
            {"lang": "cs", "title": "Křišťálový střep",
             "description": "Na zamrzlém severu Zapomenutých říší se temný elf Drizzt Do'Urden spojí s barbarským válečníkem Wulfgarem a půlčíkem zlodějem Regisem, aby bojovali proti čaroději třímajícímu ničivý magický artefakt."},
            {"lang": "de", "title": "Der Kristallsplitter",
             "description": "Im eisigen Norden der Vergessenen Reiche verbündet sich der Dunkelelf Drizzt Do'Urden mit dem Barbarenkrieger Wulfgar und dem Halbling-Schurken Regis gegen einen Zauberer mit einem verheerenden Artefakt."},
            {"lang": "es", "title": "La Lanza de Cristal",
             "description": "En el helado norte de los Reinos Olvidados, el elfo oscuro Drizzt Do'Urden se une al guerrero bárbaro Wulfgar y al ladrón mediano Regis para luchar contra un mago que empuña un artefacto devastador."},
            {"lang": "ar", "title": "شظية الكريستال",
             "description": "في شمال عوالم المنسيين المتجمدة، يتحالف الإلفي المظلم دريزت دو'أوردن مع المحارب البربري وولفغار واللص القزم ريجيس لمواجهة ساحر يمتلك قطعة سحرية مدمرة."},
        ],
    },
    {
        "author": "Margaret Weis & Tracy Hickman",
        "publisher": "Wizards of the Coast",
        "subgenre": "Epic Fantasy",
        "isbn": "978-0786915736",
        "price": 13.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "Dragons of Autumn Twilight",
             "description": "A diverse band of companions reunites after years apart and is thrust into an epic quest across war-torn Krynn, where ancient gods have returned and dragons once again darken the skies."},
            {"lang": "cs", "title": "Draci podzimního soumraku",
             "description": "Skupina různorodých společníků se po letech odloučení znovu setká a je vržena do epické výpravy napříč válkou zmítaným Krynnem, kam se vrátili staří bohové."},
            {"lang": "de", "title": "Drachen der Dämmerung",
             "description": "Eine bunte Gruppe von Gefährten findet sich nach jahrelanger Trennung wieder zusammen und wird in eine epische Suche durch das kriegszerrissene Krynn hineingezogen, wo uralte Götter zurückgekehrt sind."},
            {"lang": "es", "title": "Dragones del Crepúsculo Otoñal",
             "description": "Un variopinto grupo de compañeros se reúne tras años de separación y se ve arrastrado a una épica aventura por el mundo en guerra de Krynn, donde los dioses ancestrales han regresado."},
            {"lang": "ar", "title": "تنانين غروب الخريف",
             "description": "تلتقي مجموعة متنوعة من الرفاق بعد سنوات من الفراق، ليجدوا أنفسهم في خضم مهمة ملحمية عبر عالم كرين الممزق بالحروب، حيث عادت الآلهة القديمة والتنانين تظلم السماء من جديد."},
        ],
    },

    # ── Other genres ─────────────────────────────────────────────────────────
    {
        "author": "Jane Austen",
        "publisher": "Penguin Random House",
        "subgenre": "Historical Romance",
        "isbn": "978-0141439518",
        "price": 10.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "Pride and Prejudice",
             "description": "In Regency-era England, the witty Elizabeth Bennet navigates marriage, class, and family expectations as she falls for the proud and wealthy Mr. Darcy — despite their initial mutual disdain."},
            {"lang": "cs", "title": "Pýcha a předsudek",
             "description": "V Anglii období regentství proplouvá duchaplná Elizabeth Bennet otázkami manželství, společenské třídy a rodinných očekávání, zatímco se zamilovává do hrdého pana Darcyho."},
            {"lang": "de", "title": "Stolz und Vorurteil",
             "description": "Im England der Regency-Ära navigiert die witzige Elizabeth Bennet durch Heirat, Klassenunterschiede und Familienerwartungen, während sie sich in den stolzen Mr. Darcy verliebt."},
            {"lang": "es", "title": "Orgullo y Prejuicio",
             "description": "En la Inglaterra de la Regencia, la ingeniosa Elizabeth Bennet navega entre el matrimonio, la clase social y las expectativas familiares mientras se enamora del orgulloso Sr. Darcy."},
            {"lang": "ar", "title": "الكبرياء والتحيز",
             "description": "في إنجلترا عصر الوصاية، تجتاز إليزابيث بينيت الذكية متاهات الزواج والطبقية وتوقعات الأسرة، بينما تقع في حب السيد دارسي المتكبر الثري رغم احتقارهما المتبادل في البداية."},
        ],
    },
    {
        "author": "Bram Stoker",
        "publisher": "Simon & Schuster",
        "subgenre": "Supernatural Horror",
        "isbn": "978-0486411095",
        "price": 9.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "Dracula",
             "description": "Jonathan Harker travels to Transylvania for a real estate deal, only to discover his client is a centuries-old vampire — setting off a desperate chase across Europe to stop Count Dracula."},
            {"lang": "cs", "title": "Dracula",
             "description": "Jonathan Harker cestuje do Transylvánie kvůli realitní transakci, ale zjišťuje, že jeho klient je staletý upír, čímž začíná zoufalá honba napříč Evropou."},
            {"lang": "de", "title": "Dracula",
             "description": "Jonathan Harker reist für ein Immobiliengeschäft nach Transsylvanien, nur um zu entdecken, dass sein Auftraggeber ein jahrhundertealter Vampir ist, was eine verzweifelte Jagd durch Europa auslöst."},
            {"lang": "es", "title": "Drácula",
             "description": "Jonathan Harker viaja a Transilvania para una transacción inmobiliaria, solo para descubrir que su cliente es un vampiro de siglos de antigüedad, desencadenando una desesperada persecución por Europa."},
            {"lang": "ar", "title": "دراكولا",
             "description": "يسافر جوناثان هاركر إلى ترانسيلفانيا لإتمام صفقة عقارية، ليكتشف أن عميله مصاص دماء معمّر بمئات السنين، مما يشعل مطاردة يائسة عبر أوروبا لوقف الكونت دراكولا."},
        ],
    },
    # ── Theodore Roosevelt ───────────────────────────────────────────────────
    {
        "author": "Edmund Morris",
        "publisher": "Penguin Random House",
        "subgenre": "Political Bio",
        "isbn": "978-0375756788",
        "price": 18.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "The Rise of Theodore Roosevelt",
             "description": "The first volume of Edmund Morris's celebrated trilogy follows the extraordinary early life of Theodore Roosevelt, from his sickly childhood to his electrifying rise to national prominence."},
            {"lang": "cs", "title": "Vzestup Theodora Roosevelta",
             "description": "První díl trilogie Edmunda Morrise sleduje výjimečný raný život Theodora Roosevelta, od jeho churavého dětství až po oslnivý vzestup na národní scéně."},
            {"lang": "de", "title": "Der Aufstieg von Theodore Roosevelt",
             "description": "Der erste Band von Edmund Morris' gefeierter Trilogie schildert das außergewöhnliche frühe Leben Theodore Roosevelts, von seiner kränklichen Kindheit bis zu seinem elektrisierenden Aufstieg zur nationalen Bekanntheit."},
            {"lang": "es", "title": "El ascenso de Theodore Roosevelt",
             "description": "El primer volumen de la celebrada trilogía de Edmund Morris sigue la extraordinaria vida temprana de Theodore Roosevelt, desde su infancia enfermiza hasta su electrizante ascenso a la prominencia nacional."},
            {"lang": "ar", "title": "صعود ثيودور روزفلت",
             "description": "الجزء الأول من ثلاثية إدموند موريس المرموقة يتتبع الحياة المبكرة الاستثنائية لثيودور روزفلت، من طفولته المريضة إلى صعوده المذهل إلى مكانة وطنية بارزة."},
        ],
    },
    {
        "author": "Edmund Morris",
        "publisher": "Penguin Random House",
        "subgenre": "Political Bio",
        "isbn": "978-0375756795",
        "price": 18.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "Theodore Rex",
             "description": "The second volume covers Roosevelt's two full terms as the 26th President, a transformative era of trust-busting, conservation, and the forging of American power on the world stage."},
            {"lang": "cs", "title": "Theodore Rex",
             "description": "Druhý díl pokrývá dvě úplná Rooseveltova funkční období ve funkci 26. prezidenta — transformační éru rozbíjení trustů, ochrany přírody a upevňování americké moci."},
            {"lang": "de", "title": "Theodore Rex",
             "description": "Der zweite Band behandelt Roosevelts zwei volle Amtszeiten als 26. Präsident, eine transformative Ära der Trustbekämpfung, des Naturschutzes und der Stärkung amerikanischer Macht."},
            {"lang": "es", "title": "Theodore Rex",
             "description": "El segundo volumen cubre los dos mandatos completos de Roosevelt como 26.º presidente, una era transformadora de ruptura de monopolios, conservación y forja del poder estadounidense en el escenario mundial."},
            {"lang": "ar", "title": "ثيودور ريكس",
             "description": "الجزء الثاني يغطي فترتي روزفلت الكاملتين بوصفه الرئيس السادس والعشرين، وهو عهد تحويلي شهد كسر الاحتكارات والحفاظ على البيئة وبناء القوة الأمريكية على الساحة الدولية."},
        ],
    },
    {
        "author": "Edmund Morris",
        "publisher": "Penguin Random House",
        "subgenre": "Political Bio",
        "isbn": "978-0375756801",
        "price": 18.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "Colonel Roosevelt",
             "description": "The concluding volume follows Theodore Roosevelt's tumultuous post-presidency years, from his African safari to his bitter return to politics and his doomed Bull Moose campaign."},
            {"lang": "cs", "title": "Plukovník Roosevelt",
             "description": "Závěrečný díl sleduje bouřlivá Rooseveltova léta po prezidentském úřadu, od afrického safari po hořký návrat do politiky a neúspěšnou kampaň strany Bull Moose."},
            {"lang": "de", "title": "Colonel Roosevelt",
             "description": "Der abschließende Band verfolgt Theodore Roosevelts turbulente Jahre nach der Präsidentschaft, von seiner afrikanischen Safari bis zu seiner verbitterten Rückkehr in die Politik und seiner erfolglosen Bull-Moose-Kampagne."},
            {"lang": "es", "title": "El Coronel Roosevelt",
             "description": "El volumen final sigue los tumultuosos años postpresidenciales de Theodore Roosevelt, desde su safari africano hasta su amargo regreso a la política y su fracasada campaña del Partido Bull Moose."},
            {"lang": "ar", "title": "العقيد روزفلت",
             "description": "الجزء الختامي يتابع السنوات المضطربة لثيودور روزفلت بعد الرئاسة، من رحلته الإفريقية إلى عودته المريرة إلى السياسة وحملته الفاشلة بحزب الثور الأمريكي."},
        ],
    },
    {
        "author": "Theodore Roosevelt",
        "publisher": "Penguin Random House",
        "subgenre": "Military History",
        "isbn": "978-0306809101",
        "price": 16.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "The Naval War of 1812",
             "description": "Theodore Roosevelt's groundbreaking historical work, written at age 23, provides a rigorous and comprehensive account of the naval campaigns of the War of 1812."},
            {"lang": "cs", "title": "Námořní válka roku 1812",
             "description": "Průkopnické historické dílo Theodora Roosevelta, napsané ve třiadvaceti letech, nabízí pečlivý a rozsáhlý popis námořních kampaní války roku 1812."},
            {"lang": "de", "title": "Der Seekrieg von 1812",
             "description": "Theodore Roosevelts bahnbrechendes historisches Werk, mit 23 Jahren verfasst, liefert einen gründlichen und umfassenden Bericht über die Seekriegsführung im Krieg von 1812."},
            {"lang": "es", "title": "La Guerra Naval de 1812",
             "description": "La pionera obra histórica de Theodore Roosevelt, escrita a los 23 años, ofrece un riguroso y completo relato de las campañas navales de la Guerra de 1812."},
            {"lang": "ar", "title": "الحرب البحرية عام 1812",
             "description": "عمل تاريخي رائد كتبه ثيودور روزفلت في سن الثالثة والعشرين، يقدم روايةً صارمة وشاملة للحملات البحرية في حرب عام 1812."},
        ],
    },
    {
        "author": "Theodore Roosevelt",
        "publisher": "Simon & Schuster",
        "subgenre": "Memoir",
        "isbn": "978-0486298917",
        "price": 12.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "The Rough Riders",
             "description": "Theodore Roosevelt's firsthand account of the famous volunteer cavalry regiment he helped lead during the Spanish-American War, including the legendary charge up San Juan Hill."},
            {"lang": "cs", "title": "Drsní jezdci",
             "description": "Rooseveltovo svědectví z první ruky o slavném dobrovolnickém jezdeckém pluku, který pomáhal vést během španělsko-americké války, včetně legendárního útoku na Kettle Hill."},
            {"lang": "de", "title": "Die Rough Riders",
             "description": "Theodore Roosevelts Augenzeugenbericht über das berühmte freiwillige Kavallerieregiment, das er im Spanisch-Amerikanischen Krieg anführte, einschließlich des legendären Sturms auf San Juan Hill."},
            {"lang": "es", "title": "Los Jinetes Rudos",
             "description": "El relato de primera mano de Theodore Roosevelt sobre el famoso regimiento de caballería voluntaria que ayudó a liderar durante la guerra hispano-estadounidense, incluida la legendaria carga en la Loma San Juan."},
            {"lang": "ar", "title": "الفرسان الخشنون",
             "description": "رواية ثيودور روزفلت الشخصية عن فوج الفرسان المتطوعين الشهير الذي ساعد في قيادته إبان الحرب الإسبانية الأمريكية، بما في ذلك الهجوم الأسطوري على تلة سان خوان."},
        ],
    },

    # ── Financiers biography ─────────────────────────────────────────────────
    {
        "author": "Ron Chernow",
        "publisher": "Penguin Random House",
        "subgenre": "Political Bio",
        "isbn": "978-0679757030",
        "price": 19.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "Titan: The Life of John D. Rockefeller, Sr.",
             "description": "A sweeping biography of John D. Rockefeller, the world's first billionaire, tracing his rise from poverty to founding Standard Oil and reshaping American capitalism."},
            {"lang": "cs", "title": "Titan: Život Johna D. Rockefellera",
             "description": "Rozsáhlá biografie Johna D. Rockefellera, prvního miliardáře světa, sledující jeho cestu z chudoby k založení Standard Oil a proměně amerického kapitalismu."},
            {"lang": "de", "title": "Titan: Das Leben von John D. Rockefeller",
             "description": "Eine umfassende Biographie von John D. Rockefeller, dem ersten Milliardär der Welt, die seinen Aufstieg von der Armut zur Gründung von Standard Oil und zur Umgestaltung des amerikanischen Kapitalismus verfolgt."},
            {"lang": "es", "title": "Titán: La vida de John D. Rockefeller",
             "description": "Una gran biografía de John D. Rockefeller, el primer multimillonario del mundo, que traza su ascenso desde la pobreza hasta la fundación de la Standard Oil y la transformación del capitalismo americano."},
            {"lang": "ar", "title": "تيتان: حياة جون دي. روكفلر",
             "description": "سيرة ذاتية شاملة لجون دي. روكفلر، أول مليارديرفي العالم، تتتبع صعوده من الفقر إلى تأسيس شركة ستاندرد أويل وإعادة تشكيل الرأسمالية الأمريكية."},
        ],
    },
    {
        "author": "Ron Chernow",
        "publisher": "Penguin Random House",
        "subgenre": "Political Bio",
        "isbn": "978-0802138927",
        "price": 19.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "The House of Morgan",
             "description": "An epic chronicle of the Morgan banking dynasty across four generations, revealing how this private financial empire helped shape American and global capitalism from the Civil War to the modern era."},
            {"lang": "cs", "title": "Dům Morganů",
             "description": "Epická kronika bankovní dynastie Morganů napříč čtyřmi generacemi, ukazující, jak toto soukromé finanční impérium pomáhalo utvářet americký i světový kapitalismus od občanské války po moderní éru."},
            {"lang": "de", "title": "Das Haus Morgan",
             "description": "Eine epische Chronik der Morgan-Bankendynastie über vier Generationen, die zeigt, wie dieses private Finanzimperium den amerikanischen und globalen Kapitalismus vom Bürgerkrieg bis zur Moderne mitgeprägt hat."},
            {"lang": "es", "title": "La Casa Morgan",
             "description": "Una épica crónica de la dinastía bancaria Morgan a lo largo de cuatro generaciones, que revela cómo este imperio financiero privado ayudó a moldear el capitalismo americano y global desde la Guerra Civil hasta la era moderna."},
            {"lang": "ar", "title": "بيت مورغان",
             "description": "ملحمة تاريخية لسلالة مورغان المصرفية عبر أربعة أجيال، تكشف كيف ساعدت هذه الإمبراطورية المالية الخاصة في تشكيل الرأسمالية الأمريكية والعالمية من الحرب الأهلية حتى العصر الحديث."},
        ],
    },

    # ── Classical ────────────────────────────────────────────────────────────
    {
        "author": "Homer",
        "publisher": "Penguin Random House",
        "subgenre": "Greek Classics",
        "isbn": "978-0140268867",
        "price": 13.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "The Odyssey",
             "description": "The epic journey of Odysseus as he struggles to return home to Ithaca after the fall of Troy, battling gods, monsters, and temptation across a decade of wandering."},
            {"lang": "cs", "title": "Odysseia",
             "description": "Epická cesta Odyssea domů na Ithaku po pádu Tróje, během níž po desetiletém putování čelí bohům, nestvůrám i pokušením."},
            {"lang": "de", "title": "Die Odyssee",
             "description": "Die epische Reise des Odysseus auf seinem Weg zurück nach Ithaka nach dem Fall Trojas, auf der er gegen Götter, Monster und Versuchungen kämpft."},
            {"lang": "es", "title": "La Odisea",
             "description": "El épico viaje de Odiseo en su lucha por regresar a casa, a Ítaca, después de la caída de Troya, enfrentando dioses, monstruos y tentaciones a lo largo de una década de peregrinaje."},
            {"lang": "ar", "title": "الأوديسة",
             "description": "الرحلة الملحمية لأوديسيوس في صراعه للعودة إلى وطنه إيثاكا بعد سقوط طروادة، وهو يواجه الآلهة والوحوش والإغراء على مدى عقد من التيه."},
        ],
    },
    {
        "author": "Dante Alighieri",
        "publisher": "Penguin Random House",
        "subgenre": "Medieval Literature",
        "isbn": "978-0142437223",
        "price": 14.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "The Divine Comedy",
             "description": "Dante's monumental poem follows the pilgrim through Hell, Purgatory, and Paradise, guided by Virgil and Beatrice, in an allegorical journey through sin, redemption, and divine love."},
            {"lang": "cs", "title": "Božská komedie",
             "description": "Danteho monumentální báseň sleduje poutníka na cestě Peklem, Očistcem a Rájem, vedeného Vergiliem a Beatricí, v alegorické pouti skrze hřích, vykoupení a božskou lásku."},
            {"lang": "de", "title": "Die Göttliche Komödie",
             "description": "Dantes monumentales Gedicht folgt dem Pilger durch die Hölle, das Fegefeuer und das Paradies, geführt von Vergil und Beatrice, auf einer allegorischen Reise durch Sünde, Erlösung und göttliche Liebe."},
            {"lang": "es", "title": "La Divina Comedia",
             "description": "El poema monumental de Dante sigue al peregrino a través del Infierno, el Purgatorio y el Paraíso, guiado por Virgilio y Beatriz, en un viaje alegórico a través del pecado, la redención y el amor divino."},
            {"lang": "ar", "title": "الكوميديا الإلهية",
             "description": "قصيدة دانتي الكبرى تتابع الحاج عبر الجحيم والمطهر والفردوس، بقيادة فرجيل وبياتريس، في رحلة رمزية عبر الخطيئة والفداء والحب الإلهي."},
        ],
    },

    # ── Self-improvement ─────────────────────────────────────────────────────
    {
        "author": "James Clear",
        "publisher": "Penguin Random House",
        "subgenre": "Productivity",
        "isbn": "978-0735211292",
        "price": 16.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "Atomic Habits",
             "description": "An evidence-based framework for building good habits and breaking bad ones, showing how tiny improvements compound into remarkable results over time."},
            {"lang": "cs", "title": "Atomové návyky: drobné změny, pozoruhodné výsledky",
             "description": "Na důkazech založený rámec pro budování dobrých návyků a zbavování se těch špatných, který ukazuje, jak se drobná zlepšení skládají do pozoruhodných výsledků."},
            {"lang": "de", "title": "Die 1%-Methode",
             "description": "Ein evidenzbasierter Rahmen zum Aufbau guter Gewohnheiten und zur Überwindung schlechter, der zeigt, wie kleine Verbesserungen sich im Laufe der Zeit zu bemerkenswerten Ergebnissen summieren."},
            {"lang": "es", "title": "Hábitos atómicos",
             "description": "Un marco basado en evidencias para construir buenos hábitos y romper los malos, mostrando cómo las pequeñas mejoras se acumulan en resultados notables con el tiempo."},
            {"lang": "ar", "title": "العادات الذرية",
             "description": "إطار عمل قائم على الأدلة لبناء العادات الجيدة والتخلص من السيئة، يُظهر كيف تتراكم التحسينات الصغيرة لتُنتج نتائج مذهلة بمرور الوقت."},
        ],
    },
    {
        "author": "Dale Carnegie",
        "publisher": "Simon & Schuster",
        "subgenre": "Personal Development",
        "isbn": "978-0671027032",
        "price": 14.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "How to Win Friends and Influence People",
             "description": "Dale Carnegie's timeless guide to human relations, packed with practical advice on communication, empathy, and persuasion that has helped millions build meaningful connections."},
            {"lang": "cs", "title": "Jak získávat přátele a působit na lidi",
             "description": "Nadčasový průvodce Dalea Carnegieho mezilidskými vztahy, plný praktických rad ke komunikaci, empatii a přesvědčování, které pomohly milionům lidí budovat pevné vazby."},
            {"lang": "de", "title": "Wie man Freunde gewinnt",
             "description": "Dale Carnegies zeitloser Leitfaden zu menschlichen Beziehungen, vollgepackt mit praktischen Ratschlägen zu Kommunikation, Empathie und Überzeugung, der Millionen geholfen hat, bedeutungsvolle Verbindungen aufzubauen."},
            {"lang": "es", "title": "Cómo ganar amigos e influir sobre las personas",
             "description": "La guía atemporal de Dale Carnegie sobre las relaciones humanas, repleta de consejos prácticos sobre comunicación, empatía y persuasión que ha ayudado a millones a construir conexiones significativas."},
            {"lang": "ar", "title": "كيف تكسب الأصدقاء وتؤثر في الناس",
             "description": "دليل ديل كارنيغي الخالد في العلاقات الإنسانية، مليء بالنصائح العملية حول التواصل والتعاطف والإقناع، وقد أعان الملايين على بناء علاقات هادفة."},
        ],
    },

    # ── Comedy ───────────────────────────────────────────────────────────────
    {
        "author": "Douglas Adams",
        "publisher": "Penguin Random House",
        "subgenre": "Satire",
        "isbn": "978-0345391803",
        "price": 13.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "The Hitchhiker's Guide to the Galaxy",
             "description": "When Earth is demolished to make way for a hyperspace bypass, hapless Arthur Dent is swept into the absurd universe with only a towel and his alien friend Ford Prefect for company."},
            {"lang": "cs", "title": "Stopařův průvodce po Galaxii",
             "description": "Když je Země zbourána kvůli výstavbě hyperprostorové obchvatové trasy, nešťastný Arthur Dent je odnesen do absurdního vesmíru jen s ručníkem a svým mimozemským přítelem Fordem Prefectem."},
            {"lang": "de", "title": "Per Anhalter durch die Galaxis",
             "description": "Als die Erde für eine Hyperschnellstraße abgerissen wird, wird der glücklose Arthur Dent mit nur einem Handtuch und seinem außerirdischen Freund Ford Prefect ins absurde Universum geschleudert."},
            {"lang": "es", "title": "Guía del autoestopista galáctico",
             "description": "Cuando la Tierra es demolida para dar paso a una derivación del hiperespacio, el desafortunado Arthur Dent es arrastrado al absurdo universo con solo una toalla y su amigo alienígena Ford Prefect."},
            {"lang": "ar", "title": "دليل المسافر عبر المجرة",
             "description": "عندما يُهدم كوكب الأرض لإفساح الطريق لممر فائق السرعة، يُجرف آرثر دنت المسكين إلى الكون العبثي ومعه مناشفته وصديقه الفضائي فورد بريفكت."},
        ],
    },
    {
        "author": "Terry Pratchett & Neil Gaiman",
        "publisher": "HarperCollins",
        "subgenre": "Parody",
        "isbn": "978-0060853983",
        "price": 14.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "Good Omens",
             "description": "The angel Aziraphale and demon Crowley, friends for millennia, team up to prevent the Apocalypse — mainly because they've grown quite fond of the Earth and its peculiar inhabitants."},
            {"lang": "cs", "title": "Dobrá znamení",
             "description": "Anděl Azirafal a démon Crowley, přátelé po tisíciletí, spojí síly, aby zabránili Apokalypse — hlavně proto, že si oblíbili Zemi a její podivuhodné obyvatele."},
            {"lang": "de", "title": "Ein gutes Omen",
             "description": "Der Engel Aziraphale und der Dämon Crowley, seit Jahrtausenden befreundet, tun sich zusammen, um die Apokalypse zu verhindern — hauptsächlich weil sie der Erde und ihren merkwürdigen Bewohnern recht zugetan sind."},
            {"lang": "es", "title": "Buenos presagios",
             "description": "El ángel Aziraphale y el demonio Crowley, amigos desde hace milenios, se unen para evitar el Apocalipsis — principalmente porque se han encariñado bastante con la Tierra y sus peculiares habitantes."},
            {"lang": "ar", "title": "أوامر حسنة",
             "description": "يتحالف الملاك عزيرافيل والشيطان كراولي، صديقان منذ آلاف السنين، لمنع يوم القيامة — لأنهما باتا مغرمين بكوكب الأرض وسكانه الغريبين."},
        ],
    },
    {
        "author": "Joseph Heller",
        "publisher": "Simon & Schuster",
        "subgenre": "Satire",
        "isbn": "978-1451626650",
        "price": 15.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "Catch-22",
             "description": "Captain Yossarian and his fellow airmen in World War II Italy do everything they can to avoid flying more missions, trapped in the absurd military bureaucracy that gives the novel its name."},
            {"lang": "cs", "title": "Hlava XXII",
             "description": "Kapitán Yossarian a jeho kolegové letci v Itálii za druhé světové války dělají vše pro to, aby se vyhnuli dalším misím, uvězněni v absurdní vojenské byrokracii, která dala románu jméno."},
            {"lang": "de", "title": "Catch-22",
             "description": "Captain Yossarian und seine Fliegerkameraden im Zweiten Weltkrieg in Italien tun alles, um weitere Einsätze zu vermeiden, gefangen in der absurden Militärbürokratie, die dem Roman seinen Namen gibt."},
            {"lang": "es", "title": "Trampa-22",
             "description": "El capitán Yossarian y sus compañeros aviadores en la Italia de la Segunda Guerra Mundial hacen todo lo posible para evitar volar más misiones, atrapados en la absurda burocracia militar que da nombre a la novela."},
            {"lang": "ar", "title": "الفخ 22",
             "description": "يفعل الكابتن يوساريان ورفاقه من الطيارين في إيطاليا زمن الحرب العالمية الثانية كل ما بوسعهم لتفادي تنفيذ مزيد من المهام، محاصَرين في البيروقراطية العسكرية العبثية التي أعطت الرواية اسمها."},
        ],
    },

    # ── Thriller ─────────────────────────────────────────────────────────────
    {
        "author": "Stieg Larsson",
        "publisher": "Penguin Random House",
        "subgenre": "Psychological Thriller",
        "isbn": "978-0307454546",
        "price": 15.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "The Girl with the Dragon Tattoo",
             "description": "Disgraced journalist Mikael Blomkvist and brilliant hacker Lisbeth Salander join forces to solve the decades-old disappearance of a young woman from a wealthy and corrupt Swedish family."},
            {"lang": "cs", "title": "Muži, kteří nenávidí ženy",
             "description": "Zdiskreditovaný novinář Mikael Blomkvist a brilantní hackerka Lisbeth Salanderová spojují síly, aby vyřešili desítky let staré zmizení mladé ženy z bohaté a zkorumpované švédské rodiny."},
            {"lang": "de", "title": "Verblendung",
             "description": "Der in Ungnade gefallene Journalist Mikael Blomkvist und die brillante Hackerin Lisbeth Salander vereinen ihre Kräfte, um das jahrzehntealte Verschwinden einer jungen Frau aus einer wohlhabenden schwedischen Familie aufzuklären."},
            {"lang": "es", "title": "Los hombres que no amaban a las mujeres",
             "description": "El periodista en desgracia Mikael Blomkvist y la brillante hacker Lisbeth Salander unen fuerzas para resolver la desaparición de hace décadas de una joven de una familia sueca rica y corrupta."},
            {"lang": "ar", "title": "الفتاة ذات الوشم التنيني",
             "description": "يتشارك الصحفي المنبوذ ميكائيل بلومكفيست والمخترعة الموهوبة ليزبيث سالاندر في حل لغز اختفاء امرأة شابة منذ عقود من عائلة سويدية ثرية فاسدة."},
        ],
    },
    {
        "author": "Frederick Forsyth",
        "publisher": "Penguin Random House",
        "subgenre": "Political Thriller",
        "isbn": "978-0451239235",
        "price": 13.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "The Day of the Jackal",
             "description": "A nameless professional assassin known as the Jackal is hired to kill French President Charles de Gaulle, while a single police detective races to unmask and stop him in time."},
            {"lang": "cs", "title": "Šakal",
             "description": "Profesionální vrah bez známého jména, přezdívaný Šakal, dostane za úkol zabít francouzského prezidenta Charlese de Gaulla, zatímco jediný policejní detektiv se ho snaží včas odhalit."},
            {"lang": "de", "title": "Der Schakal",
             "description": "Ein namenloser Profikiller, bekannt als der Schakal, wird beauftragt, den französischen Präsidenten Charles de Gaulle zu töten, während ein Polizeidetektiv gegen die Zeit kämpft, um ihn zu entlarven."},
            {"lang": "es", "title": "Chacal",
             "description": "Un asesino profesional sin nombre conocido como el Chacal es contratado para matar al presidente francés Charles de Gaulle, mientras un solo detective de policía corre para desenmascararlo y detenerlo a tiempo."},
            {"lang": "ar", "title": "يوم الشاكال",
             "description": "قاتل محترف مجهول الهوية يُعرف بالشاكال يُستأجر لاغتيال الرئيس الفرنسي شارل ديغول، فيما يسابق محقق بوليسي وحيد الزمن لكشف هويته وإيقافه."},
        ],
    },

    # ── Romance ──────────────────────────────────────────────────────────────
    {
        "author": "Charlotte Brontë",
        "publisher": "Penguin Random House",
        "subgenre": "Historical Romance",
        "isbn": "978-0141441146",
        "price": 10.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "Jane Eyre",
             "description": "Orphaned Jane Eyre endures a harsh upbringing and becomes a governess at Thornfield Hall, where she falls for the brooding Mr. Rochester — and discovers his terrible secret."},
            {"lang": "cs", "title": "Jana Eyrová",
             "description": "Sirotek Jana Eyrová překoná těžké dětství a stane se vychovatelkou v Thornfield Hall, kde se zamiluje do zamlklého pana Rochestera a odhalí jeho strašlivé tajemství."},
            {"lang": "de", "title": "Jane Eyre",
             "description": "Die Waise Jane Eyre übersteht eine harte Kindheit und wird Gouvernante in Thornfield Hall, wo sie sich in den grüblerischen Mr. Rochester verliebt und sein schreckliches Geheimnis entdeckt."},
            {"lang": "es", "title": "Jane Eyre",
             "description": "La huérfana Jane Eyre soporta una infancia dura y se convierte en institutriz en Thornfield Hall, donde se enamora del sombrío Sr. Rochester y descubre su terrible secreto."},
            {"lang": "ar", "title": "جين إير",
             "description": "تعاني اليتيمة جين إير نشأةً قاسية قبل أن تصبح مربيةً في قصر ثورنفيلد، حيث تقع في حب السيد روتشستر الكئيب وتكتشف سره المروّع."},
        ],
    },
    {
        "author": "Emily Brontë",
        "publisher": "Penguin Random House",
        "subgenre": "Historical Romance",
        "isbn": "978-0141439556",
        "price": 10.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "Wuthering Heights",
             "description": "The wild and brooding Heathcliff and his passionate love for Catherine Earnshaw consume two generations on the Yorkshire moors, in a story of obsession, revenge, and the destructive power of love."},
            {"lang": "cs", "title": "Na Větrné hůrce",
             "description": "Prudký a temný Heathcliff a jeho vášnivá láska ke Catherine Earnshawové spalují dvě generace na yorkshirských vřesovištích v příběhu posedlosti, pomsty a ničivé lásky."},
            {"lang": "de", "title": "Sturmhöhe",
             "description": "Der wilde und grüblerische Heathcliff und seine leidenschaftliche Liebe zu Catherine Earnshaw verzehren zwei Generationen auf den Mooren Yorkshires, in einer Geschichte von Obsession, Rache und zerstörerischer Liebe."},
            {"lang": "es", "title": "Cumbres borrascosas",
             "description": "El salvaje y sombrío Heathcliff y su apasionado amor por Catherine Earnshaw consumen a dos generaciones en los páramos de Yorkshire, en una historia de obsesión, venganza y el poder destructivo del amor."},
            {"lang": "ar", "title": "مرتفعات ويذرينغ",
             "description": "تستهلك العلاقة المتوحشة بين هيثكليف وكاثرين إيرنشو جيلين على أراضي يوركشاير المقفرة، في قصة هوس وانتقام وقدرة الحب المدمرة."},
        ],
    },

    # ── History ──────────────────────────────────────────────────────────────
    {
        "author": "Jared Diamond",
        "publisher": "W. W. Norton & Company",
        "subgenre": "Modern History",
        "isbn": "978-0393354324",
        "price": 17.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "Guns, Germs, and Steel",
             "description": "Jared Diamond explores why Eurasian civilizations came to dominate the world, arguing that geography and environment — not race or intelligence — determined the fates of human societies."},
            {"lang": "cs", "title": "Osudy lidských společností",
             "description": "Jared Diamond zkoumá, proč eurasijské civilizace ovládly svět, a tvrdí, že osud lidských společností určily geografie a prostředí — nikoli rasa nebo inteligence."},
            {"lang": "de", "title": "Arm und Reich",
             "description": "Jared Diamond untersucht, warum eurasische Zivilisationen die Welt dominierten, und argumentiert, dass Geographie und Umwelt — nicht Rasse oder Intelligenz — das Schicksal menschlicher Gesellschaften bestimmten."},
            {"lang": "es", "title": "Armas, gérmenes y acero",
             "description": "Jared Diamond explora por qué las civilizaciones euroasiáticas llegaron a dominar el mundo, argumentando que la geografía y el entorno — no la raza ni la inteligencia — determinaron los destinos de las sociedades humanas."},
            {"lang": "ar", "title": "البنادق والجراثيم والفولاذ",
             "description": "يستكشف جاريد دايموند سبب هيمنة الحضارات الأوراسية على العالم، مجادلاً بأن الجغرافيا والبيئة — لا العرق أو الذكاء — هي التي حددت مصائر المجتمعات البشرية."},
        ],
    },
    {
        "author": "Barbara Tuchman",
        "publisher": "Penguin Random House",
        "subgenre": "Military History",
        "isbn": "978-0345476098",
        "price": 16.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "The Guns of August",
             "description": "Barbara Tuchman's Pulitzer Prize-winning account of the opening weeks of World War I, chronicling the diplomatic failures and military miscalculations that set Europe ablaze."},
            {"lang": "cs", "title": "Srpnové výstřely",
             "description": "Pulitzerovou cenou oceněné vyprávění Barbary Tuchmanové o prvních týdnech první světové války mapuje diplomatická selhání a vojenské omyly, které zažehly Evropu."},
            {"lang": "de", "title": "Die Kanonen des August",
             "description": "Barbara Tuchmans mit dem Pulitzer-Preis ausgezeichneter Bericht über die ersten Wochen des Ersten Weltkriegs, der die diplomatischen Misserfolge und militärischen Fehlkalkulationen schildert, die Europa in Brand setzten."},
            {"lang": "es", "title": "Los cañones de agosto",
             "description": "El relato ganador del Premio Pulitzer de Barbara Tuchman sobre las primeras semanas de la Primera Guerra Mundial, que narra los fracasos diplomáticos y los errores militares que pusieron Europa en llamas."},
            {"lang": "ar", "title": "مدافع أغسطس",
             "description": "رواية باربرا توكمان الحائزة على جائزة بوليتزر عن الأسابيع الأولى من الحرب العالمية الأولى، تؤرخ للإخفاقات الدبلوماسية والأخطاء العسكرية التي أشعلت أوروبا."},
        ],
    },

    # ── Mystery ──────────────────────────────────────────────────────────────
    {
        "author": "Agatha Christie",
        "publisher": "HarperCollins",
        "subgenre": "Cozy Mystery",
        "isbn": "978-0062073488",
        "price": 13.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "And Then There Were None",
             "description": "Ten strangers are lured to a remote island and murdered one by one according to a children's rhyme, with no apparent killer and no way to escape — Christie's best-selling mystery of all time."},
            {"lang": "cs", "title": "A pak nezbyl žádný",
             "description": "Deset neznámých lidí je vylákáno na odlehlý ostrov a podle dětské říkanky vražděno jeden po druhém, bez zjevného vraha a bez možnosti úniku — nejprodávanější detektivní román Agathy Christie."},
            {"lang": "de", "title": "Und dann gabs keinen mehr",
             "description": "Zehn Fremde werden auf eine abgelegene Insel gelockt und einer nach dem anderen nach einem Kinderreim ermordet, ohne erkennbaren Täter und ohne Fluchtmöglichkeit — Christies meistverkaufter Krimi."},
            {"lang": "es", "title": "Diez negritos",
             "description": "Diez extraños son atraídos a una isla remota y asesinados uno a uno según una rima infantil, sin asesino aparente y sin forma de escapar — el misterio más vendido de Agatha Christie."},
            {"lang": "ar", "title": "ثم لم يبق أحد",
             "description": "يُستدرج عشرة غرباء إلى جزيرة نائية ويُقتلون واحداً تلو الآخر وفق أغنية أطفال، دون قاتل ظاهر ودون مفر — أكثر روايات أغاثا كريستي مبيعاً على الإطلاق."},
        ],
    },
    {
        "author": "Dashiell Hammett",
        "publisher": "Penguin Random House",
        "subgenre": "Noir",
        "isbn": "978-0679722649",
        "price": 12.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "The Maltese Falcon",
             "description": "Hard-boiled San Francisco detective Sam Spade is hired to find a missing woman and soon finds himself entangled in a deadly web of deceit surrounding a priceless jewelled statuette."},
            {"lang": "cs", "title": "Maltézský sokol",
             "description": "Ostřílený sanfranciský detektiv Sam Spade je najat, aby našel pohřešovanou ženu, a brzy se ocitá v smrtící síti podvodů kolem neocenitelné sošky."},
            {"lang": "de", "title": "Der Malteser Falke",
             "description": "Der hartgesottene San Francisco-Detektiv Sam Spade wird engagiert, um eine vermisste Frau zu finden, und gerät bald in ein tödliches Netz aus Täuschungen rund um eine unbezahlbare Juwelenfigur."},
            {"lang": "es", "title": "El halcón maltés",
             "description": "El duro detective de San Francisco Sam Spade es contratado para encontrar a una mujer desaparecida y pronto se ve enredado en una mortífera red de engaños en torno a una valiosa estatuilla enjoyada."},
            {"lang": "ar", "title": "الصقر المالطي",
             "description": "يُكلَّف المحقق الصعب سام سبيد من سان فرانسيسكو بإيجاد امرأة مفقودة، فيجد نفسه سريعاً محاصراً في شبكة مميتة من الخداع حول تمثال مرصع بالجواهر لا يقدر بثمن."},
        ],
    },

    # ── Philosophy ───────────────────────────────────────────────────────────
    {
        "author": "Marcus Aurelius",
        "publisher": "Penguin Random House",
        "subgenre": "Ancient Philosophy",
        "isbn": "978-0140449334",
        "price": 11.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "Meditations",
             "description": "The private journal of Roman Emperor Marcus Aurelius, written during military campaigns, offering timeless Stoic reflections on duty, resilience, and the art of living with virtue."},
            {"lang": "cs", "title": "Hovory k sobě",
             "description": "Osobní deník římského císaře Marka Aurelia, psaný během vojenských tažení, nabízí nadčasové stoické úvahy o povinnosti, odolnosti a umění ctnostného života."},
            {"lang": "de", "title": "Selbstbetrachtungen",
             "description": "Das private Tagebuch des römischen Kaisers Marc Aurel, während seiner Feldzüge verfasst, bietet zeitlose stoische Reflexionen über Pflicht, Widerstandsfähigkeit und die Kunst, tugendhaft zu leben."},
            {"lang": "es", "title": "Meditaciones",
             "description": "El diario privado del emperador romano Marco Aurelio, escrito durante sus campañas militares, que ofrece reflexiones estoicas atemporales sobre el deber, la resiliencia y el arte de vivir con virtud."},
            {"lang": "ar", "title": "تأملات",
             "description": "اليوميات الخاصة للإمبراطور الروماني ماركوس أوريليوس، كُتبت خلال الحملات العسكرية، تقدم تأملات رواقية خالدة حول الواجب والصمود وفن العيش بفضيلة."},
        ],
    },

    # ── Sapiens (moved here, existing book) ──────────────────────────────────
    {
        "author": "Yuval Noah Harari",
        "publisher": "HarperCollins",
        "subgenre": "Modern History",
        "isbn": "978-0062316097",
        "price": 17.99,
        "currency": "USD",
        "translations": [
            {"lang": "en", "title": "Sapiens: A Brief History of Humankind",
             "description": "A sweeping narrative of humanity's journey from prehistoric foragers to the global empire of today, exploring how biology, culture, and chance made Homo sapiens the dominant species."},
            {"lang": "cs", "title": "Sapiens: Stručné dějiny lidstva",
             "description": "Panoramatické vyprávění o cestě lidstva od pravěkých lovců a sběračů po dnešní globální říši zkoumá, jak biologie, kultura a náhoda formovaly náš druh."},
            {"lang": "de", "title": "Eine kurze Geschichte der Menschheit",
             "description": "Eine weitreichende Erzählung der menschlichen Reise von prähistorischen Jäger-Sammler-Gruppen bis zum heutigen globalen Reich, die erklärt, wie Biologie, Kultur und Zufall den Homo sapiens zur dominanten Spezies machten."},
            {"lang": "es", "title": "Sapiens: De animales a dioses",
             "description": "Un relato panorámico del viaje de la humanidad desde los cazadores-recolectores prehistóricos hasta el imperio global de hoy, explorando cómo la biología, la cultura y el azar convirtieron al Homo sapiens en la especie dominante."},
            {"lang": "ar", "title": "سابينس: تاريخ موجز للبشرية",
             "description": "سرد بانورامي لرحلة البشرية من قبائل الصيادين وجامعي الثمار في عصور ما قبل التاريخ إلى الإمبراطورية العالمية اليوم، يستكشف كيف جعل تضافر البيولوجيا والثقافة والصدفة الإنسانَ العاقلَ السيدَ على الكوكب."},
        ],
    },
]


def _get_or_create_publisher(db: Session, name: str) -> Publisher:
    obj = db.query(Publisher).filter_by(publisher_name=name).first()
    if not obj:
        obj = Publisher(publisher_name=name)
        db.add(obj)
        db.flush()
    return obj


def _get_or_create_author(db: Session, name: str) -> Author:
    obj = db.query(Author).filter_by(author_name=name).first()
    if not obj:
        obj = Author(author_name=name)
        db.add(obj)
        db.flush()
    return obj


def _get_or_create_category(db: Session, name: str, parent_id: int | None) -> BookCategory:
    obj = db.query(BookCategory).filter_by(category_name=name, parent_id=parent_id).first()
    if not obj:
        obj = BookCategory(category_name=name, parent_id=parent_id)
        db.add(obj)
        db.flush()
    return obj


def fetch_cover(isbn: str) -> bytes | None:
    url = f"https://covers.openlibrary.org/b/isbn/{isbn}-L.jpg"
    try:
        with urllib.request.urlopen(url, timeout=10) as response:
            data = response.read()
        # Open Library returns a tiny 1-pixel placeholder when no cover exists
        if len(data) < 5000:
            return None
        return data
    except urllib.error.URLError:
        return None


def seed(db: Session) -> None:
    now = datetime.datetime.now()

    pub_map = {name: _get_or_create_publisher(db, name) for name in PUBLISHERS}

    category_map: dict[str, BookCategory] = {}
    for name, parent_name in CATEGORIES:
        if parent_name is None:
            category_map[name] = _get_or_create_category(db, name, None)
    for name, parent_name in CATEGORIES:
        if parent_name is not None:
            parent = category_map[parent_name]
            category_map[name] = _get_or_create_category(db, name, parent.id)

    existing_isbns = {b.isbn for b in db.query(Book.isbn).all()}
    added = 0

    for book_data in BOOKS:
        isbn = book_data["isbn"]
        if isbn in existing_isbns:
            continue

        author = _get_or_create_author(db, book_data["author"])
        publisher = pub_map.get(book_data["publisher"])
        category = category_map.get(book_data["subgenre"])
        first_lang = book_data["translations"][0]["lang"]

        book = Book(
            author_id=author.id,
            publisher_id=publisher.id if publisher else None,
            price=book_data["price"],
            currency=book_data["currency"],
            language_code=first_lang,
            isbn=isbn,
            product_status="active" if isbn in ACTIVE_ISBNS else "draft",
            created_at=now,
            updated_at=now,
        )
        db.add(book)
        db.flush()
        existing_isbns.add(isbn)
        added += 1

        for t in book_data["translations"]:
            db.add(BookTranslation(
                book_id=book.id,
                lang=t["lang"],
                title=t["title"],
                description=t["description"],
                created_at=now,
                updated_at=now,
            ))

        if category:
            db.add(BookBookCategory(book_id=book.id, category_id=category.id))
            if category.parent_id:
                db.add(BookBookCategory(book_id=book.id, category_id=category.parent_id))

    db.commit()
    print(f"✓ Books — added {added}. DB now has {db.query(Book).count()} total.")


def seed_covers(db: Session) -> None:
    if not os.getenv("MINIO_ACCESS_KEY"):
        print("⚠  MINIO_ACCESS_KEY not set — skipping covers")
        return

    books = db.query(Book).all()
    seeded = 0

    for book in books:
        if any(t.cover_image_filename for t in book.translations):
            continue
        if not book.isbn:
            continue

        isbn_clean = book.isbn.replace("-", "")
        print(f"  cover {book.isbn} … ", end="", flush=True)
        data = fetch_cover(isbn_clean)

        if not data:
            print("not found")
            continue

        storage_key = f"books/{book.id}/{uuid4()}/seed_cover.jpg"
        try:
            upload_cover(storage_key, data, "image/jpeg")
        except Exception as e:
            print(f"upload failed: {e}")
            continue

        now = datetime.datetime.now()
        for t in book.translations:
            t.cover_image_filename = storage_key
            t.updated_at = now
        db.commit()
        print(f"✓ {len(data) // 1024} KB")
        seeded += 1

    print(f"✓ Covers — {seeded}/{len(books)} uploaded.")


if __name__ == "__main__":
    db = next(get_db())
    seed(db)
    seed_covers(db)
