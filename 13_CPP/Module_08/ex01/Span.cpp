#include "Span.hpp"

/****************************Orthodox Canonical Form***************************/
Span::Span() {}

Span::Span(unsigned int N)
{

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


/***********************************exception**********************************/
const char* Span::AlreadyFilledException::what() const throw()
{
	return (BREXC "There are already N elements stored.");
}
