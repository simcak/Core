#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <map>
#include <cstdlib>	// std::atof()
#include <cctype>	// std::isdigit()
#include <bits/stdc++.h>

enum ErrorCode
{
	MISSING_PIPE = 1,
	EMPTY_PART,
	INVALID_DATE,
	INVALID_VALUE,
	AMOUNT_RANGE_LARGE,
	AMOUNT_RANGE_SMALL,
	TOO_OLD
};

#define	PRICE_DOESNT_EXIST	-1.0

/* ───────────────────────────────── COLORS ───────────────────────────────── */
#define BR		"\033[1;31m"
#define BG		"\033[1;32m"
#define BY		"\033[1;33m"
#define RST		"\033[0m"

#define BRERR	BR "Error: " RST
#define BREXC	BR "Exception: " RST

/* ───────────────────────────────── CLASSES ──────────────────────────────── */
class BitcoinExchange
{

	private:
		std::map<std::string, double> _exchangeRateDatabase;
		
		/* ──────────────────────── member function ───────────────────────── */
		double	findPrice(const std::string &date) const;
		void	parseDatabase();
		void	parseInputFile(const char *file);

	public:
		/* ───────────────────── Orthodox Canonical Form ──────────────────── */
		BitcoinExchange();
		BitcoinExchange(const char *inputFile);
		BitcoinExchange(const BitcoinExchange &copy);
		BitcoinExchange &operator=(const BitcoinExchange &);
		~BitcoinExchange();

		/* ──────────────────────────── getters ───────────────────────────── */

		/* ─────────────────────────── exception ──────────────────────────── */
		class databaseCantOpen : public std::exception {
			public: const char*		what() const throw();
		};

		class inputFileCantOpen : public std::exception {
			public: const char*		what() const throw();
		};

		class databaseEmpty : public std::exception {
			public: const char*		what() const throw();
		};

		class inputFileEmpty : public std::exception {
			public: const char*		what() const throw();
		};

};


#endif