#ifndef MUTANT_STACK_HPP
# define MUTANT_STACK_HPP

#include <iostream>
#include <stack>

/* ───────────────────────────────── COLORS ───────────────────────────────── */
#define BR		"\033[1;31m"
#define BG		"\033[1;32m"
#define BY		"\033[1;33m"
#define RST		"\033[0m"

#define BRERR	BR "Error: " RST
#define BREXC	BR "Exception: " RST

/* ───────────────────────────────── CLASSES ──────────────────────────────── */
template<typename T>
class MutantStack : public std::stack<T>
{

	public:
		/* ───────────────────── Orthodox Canonical Form ──────────────────── */
		MutantStack();
		MutantStack(const MutantStack &copy);
		MutantStack	&operator=(const MutantStack &);
		~MutantStack();

		/* ──────────────────────── member functions ──────────────────────── */

};


#endif