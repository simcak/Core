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
		typedef typename std::stack<T>::container_type	c_type;
		typedef typename c_type::iterator				iterator;
		typedef typename c_type::const_iterator			const_iterator;
		typedef typename c_type::reverse_iterator		reverse_iterator;
		typedef typename c_type::const_reverse_iterator	const_reverse_iterator;

		/* ───────────────────── Orthodox Canonical Form ──────────────────── */
		MutantStack();
		MutantStack(const MutantStack &copy);
		MutantStack	&operator=(const MutantStack &);
		~MutantStack();

		/* ──────────────── member functions -iterator access ─────────────── */
		iterator				begin()  { return this->c.begin(); }
		iterator				end()    { return this->c.end(); }
		reverse_iterator		rbegin() { return this->c.rbegin(); }
		reverse_iterator		rend()   { return this->c.rend(); }
		const_iterator			begin() const  { return this->c.begin(); }
		const_iterator			end() const    { return this->c.end(); }
		const_reverse_iterator	rbegin() const { return this->c.rbegin(); }
		const_reverse_iterator	rend() const   { return this->c.rend(); }

};

#include "MutantStack.tpp"

#endif