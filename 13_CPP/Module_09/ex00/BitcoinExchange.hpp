#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <map>

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

	public:
		/* ───────────────────── Orthodox Canonical Form ──────────────────── */
		BitcoinExchange(const std::string &dbFile);
		BitcoinExchange(const BitcoinExchange &);
		BitcoinExchange &operator=(const BitcoinExchange &);
		~BitcoinExchange();

		/* ──────────────────────────── getters ───────────────────────────── */

		/* ──────────────────────── member function ───────────────────────── */

		/* ─────────────────────────── exception ──────────────────────────── */

};


#endif