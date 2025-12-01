#ifndef MUTANT_STACK_HPP
# define MUTANT_STACK_HPP

#include <iostream>
#include <stack>


template<typename T>
class MutantStack : public std::stack<T>
{

	private:
		/* data */

	public:
		/* ───────────────────── Orthodox Canonical Form ──────────────────── */
		MutantStack();
		MutantStack(const MutantStack &copy);
		MutantStack	&operator=(const MutantStack &);
		~MutantStack();

		/* ──────────────────────── member functions ──────────────────────── */

};


#endif