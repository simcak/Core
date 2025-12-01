#include "MutantStack.hpp"

/* ───────────────────────── Orthodox Canonical Form ──────────────────────── */
template<typename T> MutantStack<T>::MutantStack(void) {}

template<typename T> MutantStack<T>::MutantStack(const MutantStack& copy)
{
	*this = copy;
}

template<typename T>
MutantStack<T> &MutantStack<T>::operator=(const MutantStack<T> &src)
{
	(void)src;
	return (*this);
}

template<typename T> MutantStack<T>::~MutantStack(void) {}

/* ──────────────────────────── member functions ──────────────────────────── */

