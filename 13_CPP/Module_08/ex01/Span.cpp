#include "Span.hpp"

/* ───────────────────────── Orthodox Canonical Form ──────────────────────── */
Span::Span(): _n_stored(0) {}

Span::Span(unsigned int N): _n_stored(N)
{
	this->_num_container; //td
}

Span::Span(const Span &copy): _n_stored(copy._n_stored)
{
	*this = copy;
}

Span	&Span::operator=(const Span &src)
{
	(void)src;
	return (*this);
}

Span::~Span() {}

/* ───────────────────────────────── getters ──────────────────────────────── */
unsigned int	Span::getNStored() const { return this->_n_stored; }

/* ──────────────────────────── member functions ──────────────────────────── */
void	Span::addNumber(int num)
{
	this->_num_container.push_back(num);
}

unsigned int	Span::shortestSpan() const
{

}

unsigned int	Span::longestSpan() const
{

}

/* ──────────────────────────────── exception ─────────────────────────────── */
const char* Span::AlreadyFilledException::what() const throw()
{
	return (BREXC "There are already N elements stored.");
}

const char* Span::NoSpanFoundException::what() const throw()
{
	return (BREXC "There are no numbers stored, or only one.");
}
