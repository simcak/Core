#ifndef EASYFIND_HPP
# define EASYFIND_HPP

#include <algorithm>
#include <list>
#include <iostream>
#include <vector>

/* ───────────────────────────────── COLORS ───────────────────────────────── */
#define BRED	"\033[1;31m"
#define BG		"\033[1;32m"
#define BY		"\033[1;33m"
#define RST		"\033[0m"

#define BREXC	BRED "Exception: " RST

/* ─────────────────────────────── EXCEPTION ──────────────────────────────── */
class NotFoundException : public std::exception
{
	public:
		virtual const char*	what() const throw()
		{
			return (BREXC "Match Not Found!");
		}
};

/* ──────────────────────────────── FUNCTION ──────────────────────────────── */
// @brief In a `cont` (container) of integers find the `match`
template <typename T>
typename T::iterator	easyfind(T &cont, int match)
{
	typename T::iterator	i;

	if ((i = find(cont.begin(), cont.end(), match)) == cont.end())
		throw NotFoundException();
	std::cout << match << BG " found" RST << std::endl;
	return (i);
};

// todo: use `inline` for practising it

#endif
