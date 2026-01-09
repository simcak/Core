#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <string>

/* ───────────────────────────────── COLORS ───────────────────────────────── */
#define BR		"\033[1;31m"
#define BG		"\033[1;32m"
#define BY		"\033[1;33m"
#define RST		"\033[0m"

#define BRERR	BR "Error: " RST
#define BREXC	BR "Exception: " RST

/* ───────────────────────────────── CLASSES ──────────────────────────────── */
class PmergeMe
{

	private:
		/* data */

	public:
		/* ───────────────────── Orthodox Canonical Form ──────────────────── */
		PmergeMe();
		PmergeMe(const std::string input);
		// PmergeMe(const PmergeMe &copy);
		PmergeMe	&operator=(const PmergeMe &other);
		~PmergeMe();

		/* ──────────────────────── member function ───────────────────────── */
		
		/* ──────────────────────────── getters ───────────────────────────── */

		/* ─────────────────────────── exception ──────────────────────────── */
		class Error : public std::exception {
			public:
				const char *what() const throw();
		};

};


#endif