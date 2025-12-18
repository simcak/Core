#include "BitcoinExchange.hpp"
/* ───────────────────────── Orthodox Canonical Form ──────────────────────── */
BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const char *inputFile)
{
	parseDatabase();
	parseInputFile(inputFile);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy)
	: _container(copy._container) {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
		_container = other._container;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

/* ──────────────────────────── member functions ──────────────────────────── */
// ─  ─  ─  ─  ─  ─  ─  ─  ─  ─ helper functions ─  ─  ─  ─  ─  ─  ─  ─  ─  ─ //
static inline bool	_thereIsHeaderLine(std::string line, int i)
{
	return (line == "date,exchange_rate" && i == 0);
}

static int	_printError(ErrorCode key, int i)
{
	switch (key)
	{
	case MISSING_PIPE:
		std::cout << BRERR "\tLine " << i << ": ";
		return (std::cout << "Invalid format - missing ' | '.\n", 1);
	case EMPTY_PART:
		std::cout << BRERR "\tLine " << i << ": ";
		return (std::cout << "Date or Value part is empty.\n", 1);
	case INVALID_DATE:
		std::cout << BRERR "\tLine " << i << ": ";
		return (std::cout << "Date format is invalid.\n", 1);
	case AMOUNT_RANGE:
		std::cout << BRERR "\tLine " << i << ": ";
		return (std::cout << "Amount is out of range <0; 1000>.\n", 1);

	default:
		return 0;
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

static bool _isValidDate(const tm &date)
{
	int	year = date.tm_year + 1900;
	int	month = date.tm_mon + 1;
	int	day = date.tm_mday;

	if (month < 1 || month > 12 || day < 1)
		return false;

	int maxDay;
	switch (month) {
		case 2:
			maxDay = _isLeapYear(year) ? 29 : 28;
			break;
		case 4: case 6: case 9: case 11:
			maxDay = 30;
			break;
		default:
			maxDay = 31;
	}
	std::cout << maxDay << "  " << day << std::endl;
	return (day <= maxDay);
}


double	BitcoinExchange::findPrice(std::string date)
{
	std::map<std::string, double>::iterator it = this->_container.begin();

	for (; it != this->_container.end(); it++)
	{
		if (date <= it->first)
		{
			if ((date < it->first) && (it != _container.begin()))
				it--;
			return it->second;
		}
	}
	if ((it == this->_container.end()) && (this->_container.size() > 1))
		it--;

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

		this->_container.insert(std::make_pair(datePart, ratePart));
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
			_printError(MISSING_PIPE, i+1);
			continue;
		}

		std::string	datePart = _ftTrim(line.substr(0, pipePos));
		std::string	valuePart = _ftTrim(line.substr(pipePos+1));
		if (datePart.empty() || valuePart.empty()) {
			_printError(EMPTY_PART, i+1);
			continue;
		}

		struct tm	tm;
		if (!strptime(datePart.c_str(), "%Y-%m-%d", &tm) || !_isValidDate(tm)) {
			_printError(INVALID_DATE, i+1);
			continue;
		}

		double	price = findPrice(datePart);
		double	value = std::atof(valuePart.c_str());
		if (value < 0 || value > 1000) {
			_printError(AMOUNT_RANGE, i+1);
			continue;
		}

		std::cout <<
			datePart << " => " << valuePart << " = " << price * value <<
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