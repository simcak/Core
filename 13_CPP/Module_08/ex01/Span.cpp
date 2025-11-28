#include "Span.hpp"

/* ───────────────────────── Orthodox Canonical Form ──────────────────────── */
Span::Span(): _n_stored(0) {}

Span::Span(unsigned int N): _n_stored(N)
{
	this->_num_container; //td
}

Span::Span(const Span &copy)
{
	*this = copy;
}

Span	&Span::operator=(const Span &src)
{
	(void)src;
	return (*this);
}

Span::~Span() {}


/* ──────────────────────────────── exception ─────────────────────────────── */
const char* Span::AlreadyFilledException::what() const throw()
{
	return (BREXC "There are already N elements stored.");
}

const char* Span::NoSpanFoundException::what() const throw()
{
	return (BREXC "There are no numbers stored, or only one.");
}
