#include "BitcoinExchange.hpp"
#include <sstream>

/* ───────────────────────── Orthodox Canonical Form ──────────────────────── */
BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const char *inputFile)
{
	parseDatabase();
	parseInputFile(inputFile);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy)
	: _exchangeRateDatabase(copy._exchangeRateDatabase) {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
		_exchangeRateDatabase = other._exchangeRateDatabase;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

/* ──────────────────────────── member functions ──────────────────────────── */
// ─  ─  ─  ─  ─  ─  ─  ─  ─  ─ helper functions ─  ─  ─  ─  ─  ─  ─  ─  ─  ─ //
static inline bool	_thereIsHeaderLine(const std::string &line, int i)
{
	return (line == "date,exchange_rate" && i == 0);
}

static void	_printError(ErrorCode key, int i)
{
	switch (key)
	{
	case MISSING_PIPE:
		std::cout << BRERR "\tLine " << i << ": ";
		std::cout << "Invalid format - missing ' | '.\n"; return;
	case EMPTY_PART:
		std::cout << BRERR "\tLine " << i << ": ";
		std::cout << "Date or Value part is empty.\n"; return;
	case INVALID_DATE:
		std::cout << BRERR "\tLine " << i << ": ";
		std::cout << "Date format is invalid.\n"; return;
	case INVALID_VALUE:
		std::cout << BRERR "\tLine " << i << ": ";
		std::cout << "Value format is invalid.\n"; return;
	case AMOUNT_RANGE_LARGE:
		std::cout << BRERR "\tLine " << i << ": ";
		std::cout << "Number is larger than 1000.\n"; return;
	case AMOUNT_RANGE_SMALL:
		std::cout << BRERR "\tLine " << i << ": ";
		std::cout << "Number is smaller than 0.\n"; return;
	case TOO_OLD:
		std::cout << BRERR "\tLine " << i << ": ";
		std::cout << "Used date is too long ago.\n"; return;

	default:
		return;
	}
}

static std::string	_ftTrim(const std::string &s)
{
	std::string::size_type start = s.find_first_not_of(" \t");
	if (start == std::string::npos)
		return "";
	std::string::size_type end = s.find_last_not_of(" \t");

	return (s.substr(start, end - start + 1));
}

static inline bool	_isLeapYear(int year)
{
	return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

static bool _parseDate(const std::string &datePart)
{
	if (datePart.size() != 10 || datePart[4] != '-' || datePart[7] != '-')
		return false;

	for (size_t i = 0; i < datePart.size(); ++i)
	{
		if (i == 4 || i == 7)
			continue;
		if (!std::isdigit(static_cast<unsigned char>(datePart[i])))
			return false;
	}

	int	y, m, d;
	y = std::atoi(datePart.substr(0, 4).c_str());
	m = std::atoi(datePart.substr(5, 2).c_str());
	d = std::atoi(datePart.substr(8, 2).c_str());

	if (m < 1 || m > 12 || d < 1)
		return false;

	int maxDay;
	switch (m)
	{
		case 2:
			maxDay = _isLeapYear(y) ? 29 : 28;
			break;
		case 4: case 6: case 9: case 11:
			maxDay = 30;
			break;
		default:
			maxDay = 31;
	}
	return (d <= maxDay);
}

/**
 * @brief Parses a string into a double value with strict validation.
 * 
 * Attempts to convert the input string to a double. The function validates
 * that the entire string represents a valid number with no trailing characters.
 * 
 * @param s The input string to parse
 * @param out Reference to a double where the parsed value will be stored
 * 
 * @return true if the string was successfully parsed as a valid double with
 *         no extraneous characters, false otherwise
 */
static bool	_parseValue(const std::string &str, double &out)
{
	std::stringstream	stream(str);
	stream >> out;
	if (stream.fail())
		return false;

	char c;
	if (stream >> c)
		return false;
	return true;
}

double	BitcoinExchange::findPrice(const std::string &date) const
{
	std::map<std::string, double>::const_iterator it;

	it = _exchangeRateDatabase.lower_bound(date);
	if (it != _exchangeRateDatabase.end() && it->first == date)
		return it->second;

	if (it == _exchangeRateDatabase.begin())
		return PRICE_DOESNT_EXIST;

	--it;
	return it->second;
}

// ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  //

void	BitcoinExchange::parseDatabase()
{
	std::ifstream	database("./data.csv");
	std::string		line;
	int				i;

	if (!database.is_open())
		throw databaseCantOpen();

	for (i = 0; std::getline(database, line); i++)
	{
		if (_thereIsHeaderLine(line, i))
			continue;

		std::string	datePart = line.substr(0, line.find(','));
		std::string	exchangeRate = line.substr(line.find(',')+1);
		double		ratePart = std::atof(exchangeRate.c_str());

		this->_exchangeRateDatabase.insert(std::make_pair(datePart, ratePart));
	}

	if (i == 0)
		throw databaseEmpty();
}

void	BitcoinExchange::parseInputFile(const char *inputFile)
{
	std::ifstream	fileStream(inputFile);
	std::string		line;
	int				i;

	if (!fileStream.is_open())
		throw inputFileCantOpen();

	for (i = 0; std::getline(fileStream, line); i++)
	{
		if (line == "date | value" && i == 0)
			continue;

		std::string::size_type	pipePos = line.find('|');
		if (pipePos == std::string::npos) {
			_printError(MISSING_PIPE, i+1); continue;
		}

		std::string	datePart = _ftTrim(line.substr(0, pipePos));
		std::string	valuePart = _ftTrim(line.substr(pipePos+1));
		if (datePart.empty() || valuePart.empty()) {
			_printError(EMPTY_PART, i+1); continue;
		}

		if (!_parseDate(datePart)) {
			_printError(INVALID_DATE, i+1); continue;
		}

		double	btcPrice = findPrice(datePart);
		if (btcPrice == PRICE_DOESNT_EXIST) {
			_printError(TOO_OLD, i+1); continue;
		}

		double	btcAmount;
		if (!_parseValue(valuePart, btcAmount)) {
			_printError(INVALID_VALUE, i+1); continue;
		}
		if (btcAmount < 0) {
			_printError(AMOUNT_RANGE_SMALL, i+1); continue;
		}
		if (btcAmount > 1000) {
			_printError(AMOUNT_RANGE_LARGE, i+1); continue;
		}

		std::cout <<
			datePart << " => " << btcAmount << " = " << btcPrice * btcAmount <<
		std::endl;
	}

	if (i == 0)
		throw inputFileEmpty();
}

/* ──────────────────────────────── exception ─────────────────────────────── */
const char *BitcoinExchange::databaseCantOpen::what() const throw() {
	return BREXC "The provided database can't be opened.";
}

const char *BitcoinExchange::inputFileCantOpen::what() const throw() {
	return BREXC "The provided file can't be opened.";
}
const char *BitcoinExchange::databaseEmpty::what() const throw() {
	return BREXC "Database file is empty.";
}

const char *BitcoinExchange::inputFileEmpty::what() const throw() {
	return BREXC "Input file is empty.";
}