#include "BitcoinExchange.hpp"
#include <bits/stdc++.h>
/* ───────────────────────── Orthodox Canonical Form ──────────────────────── */
BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const std::string &dbFile)
{
	parseDatabase();
	parseInputFile(dbFile);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy) { (void)copy; }

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	(void)other;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

/* ──────────────────────────── member functions ──────────────────────────── */
// ─  ─  ─  ─  ─  ─  ─  ─  ─  ─ helper functions ─  ─  ─  ─  ─  ─  ─  ─  ─  ─ //
inline bool	_thereIsHeaderLine(std::string line, int i)
{
	return (line == "date,exchange_rate" && i == 0);
}

// ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  //

void	BitcoinExchange::parseDatabase()
{
	std::ifstream	database("./data.csv");
	std::string		line;
	int				i;

	for (i = 0; std::getline(database, line); i++)
	{
		if (_thereIsHeaderLine(line, i))
			continue;

		std::string	datePart = line.substr(0, line.find(','));
		std::string	exchangeRate = line.substr(line.find(',')+1);
		double		ratePart = std::atof(exchangeRate.c_str());

		this->_container.insert(std::make_pair(datePart, ratePart));

		// if (i > 100 && i < 150) {
		// 	std::cout << line << std::endl;
		// 	std::cout << datePart << "-------" << ratePart << std::endl;
		// 	std::cout << "*********************" << std::endl;
		// 	int j = 1;
		// 	for (std::map<std::string, double>::const_iterator it = this->_container.begin(); it != this->_container.end(); ++it) {
		// 		if (j == i)
		// 			std::cout << it->first << " -> " << it->second << std::endl;
		// 		j++;
		// 	}
		// 	std::cout << "*********************" << std::endl;
		// }
	}

	database.close();
	if (i == 0)
		throw nothingToRead();
}

void	BitcoinExchange::parseInputFile(const std::string &dbFile)
{
	if (dbFile.empty())
		return ;
}

/* ──────────────────────────────── exception ─────────────────────────────── */
const char *BitcoinExchange::noDatabaseFile::what() const throw() {
	return BREXC "The 'data.csv' file doesn't exists.";
}

const char *BitcoinExchange::amountOutOfRange::what() const throw() {
	return BREXC "Amount is out of range. Use num in range <0; 1000>.";
}

const char *BitcoinExchange::invalidDate::what() const throw() {
	return BREXC "Date format is invalid.";
}

const char *BitcoinExchange::invalidFormat::what() const throw() {
	return BREXC "Invalid format - missing the ' | '.";
}

const char *BitcoinExchange::wrongHeader::what() const throw() {
	return BREXC "Wrong header in the file.";
}

const char *BitcoinExchange::nothingToRead::what() const throw() {
	return BREXC "There is nothing to read in the file.";
}