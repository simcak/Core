#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <sstream>

#define	BEFORE	1
#define	AFTER	2

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
		std::vector<int>	_vector;
		std::deque<int>		_deque;

	public:
		/* ───────────────────── Orthodox Canonical Form ──────────────────── */
		PmergeMe();
		PmergeMe(const std::string input);
		PmergeMe(const PmergeMe &copy);
		PmergeMe	&operator=(const PmergeMe &other);
		~PmergeMe();

		/* ──────────────────────── member function ───────────────────────── */
		void	sort();

		/* ─────────────────────────── exception ──────────────────────────── */
		class Limit : public std::exception {
			public:
				const char *what() const throw();
		};

		class DiffRes : public std::exception {
			public:
				const char *what() const throw();
		};

		class EmptyArg : public std::exception {
			public:
				const char *what() const throw();
		};

};


#endif
