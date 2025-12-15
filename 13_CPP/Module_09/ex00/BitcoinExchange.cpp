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
inline bool	_thereIsHeaderLine(std::string line, int i)
{
	return (line == "date,exchange_rate" && i == 0);
}

inline bool	_transfer_year(const tm &date)
{
	return ((date.tm_year % 4 == 0 && date.tm_year % 100 != 0) ||
			(date.tm_year % 400 == 0));
}

int	_printError(ErrorCode key, int i)
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

bool	_isValidDate(const tm &date)
{
	switch (date.tm_mon)
	{
	case 1:
		if (_transfer_year(date))
			return date.tm_mday <= 29;
		else
			return date.tm_mday <= 28;
	case 3: case 5: case 8: case 10:
		return date.tm_mday <= 30;

	default:
		return date.tm_mday <= 31;
	}
}

double	BitcoinExchange::findValue(std::string date)
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

		if (line.find(" | ") == std::string::npos) {
			_printError(MISSING_PIPE, i+1);
			continue;
		}

		std::string	datePart = line.substr(0, line.find(" | "));
		std::string	valuePart = line.substr(line.find(" | ")+3); // +3 is not robust enought - i dont like it

		if (datePart.empty() || valuePart.empty()) { // empty is not robust enought
			_printError(EMPTY_PART, i+1);
			continue;
		}

		struct tm tm = {}; // isnt here a better way?
		if (!strptime(datePart.c_str(), "%Y-%m-%d", &tm) || !_isValidDate(tm)) {
			_printError(INVALID_DATE, i+1);
			continue;
		}

		double	amount = std::atof(valuePart.c_str());
		if (amount < 0 || amount > 1000) {
			_printError(AMOUNT_RANGE, i+1);
			continue;
		}

		double		value = findValue(datePart); // is value a good name?

		std::cout << datePart << " => " << valuePart << " = "
			<< value * amount << std::endl;
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