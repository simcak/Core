#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <map>
#include <cstdlib>	// std::atof()

#define ERR_ARGS	13
#define ERR_OPEN	14
#define ERR_MPTY	15

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
		std::map<std::string, double> _container;
		
		/* ──────────────────────── member function ───────────────────────── */
		void	parseDatabase();
		void	parseInputFile(const std::string &file);

	public:
		/* ───────────────────── Orthodox Canonical Form ──────────────────── */
		BitcoinExchange();
		BitcoinExchange(const std::string &dbFile);
		BitcoinExchange(const BitcoinExchange &copy);
		BitcoinExchange &operator=(const BitcoinExchange &);
		~BitcoinExchange();

		/* ──────────────────────────── getters ───────────────────────────── */

		/* ─────────────────────────── exception ──────────────────────────── */
		class noDatabaseFile : public std::exception {
			public: const char*		what() const throw();
		};

		class amountOutOfRange : public std::exception {
			public: const char*		what() const throw();
		};

		class invalidDate : public std::exception {
			public: const char*		what() const throw();
		};

		class invalidFormat : public std::exception {
			public: const char*		what() const throw();
		};

		class wrongHeader : public std::exception {
			public: const char*		what() const throw();
		};

		class nothingToRead : public std::exception {
			public: const char*		what() const throw();
		};

};


#endif