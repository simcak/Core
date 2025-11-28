#ifndef SPAN_HPP
# define SPAN_HPP

#include <iostream>

/* ───────────────────────────────── COLORS ───────────────────────────────── */
#define BRED	"\033[1;31m"
#define BG		"\033[1;32m"
#define BY		"\033[1;33m"
#define RST		"\033[0m"

#define BRERR	BRED "Error: " RST
#define BREXC	BRED "Exception: " RST

class Span
{

	private:
		/* data */

	public:
		/************************Orthodox Canonical Form***********************/
		Span();
		Span(unsigned int N);
		Span(const Span &);
		Span &Span::operator=(const Span &);
		~Span();

		/********************************getters*******************************/

		/****************************member function***************************/
		void			addNumber();
		unsigned int	shortestSpan();
		unsigned int	longestSpan();

		/*******************************exception******************************/
		class AlreadyFilledException : public std::exception {
			public:
				const char*		what() const throw();
		};

};


#endif