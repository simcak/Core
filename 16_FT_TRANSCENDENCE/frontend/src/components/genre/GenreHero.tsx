import { useTranslation } from 'react-i18next'

interface GenreHeroProps {
  name: string
  icon: string
  color: string
  subgenresCount: number
}

export default function GenreHero({ name, icon, color, subgenresCount }: GenreHeroProps) {
  const { t } = useTranslation()
  return (
    <div
      className="rounded-2xl p-8 relative overflow-hidden"
      style={{
        background: `linear-gradient(135deg, ${color}33 0%, ${color}11 100%)`,
        border: `1px solid ${color}44`,
      }}
    >
      <div
        className="absolute -top-8 -right-8 w-48 h-48 rounded-full opacity-20 blur-3xl pointer-events-none"
        style={{ background: color }}
      />
      <div className="relative z-10">
        <span className="text-5xl mb-3 block">{icon}</span>
        <h1 className="text-4xl font-bold text-white">{name}</h1>
        <p className="text-gray-400 mt-1 text-sm">
          {t('genre.subgenresCount', { count: subgenresCount })}
        </p>
      </div>
    </div>
  )
}
