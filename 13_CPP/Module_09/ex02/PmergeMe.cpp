#include "PmergeMe.hpp"

/* ───────────────────────── Orthodox Canonical Form ──────────────────────── */
PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(const std::string input)
{
	std::cout << "test: " << input << std::endl;
}

// PmergeMe::PmergeMe(const PmergeMe &copy)
// {
// }

PmergeMe	&PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
	}
	return *this;
}

PmergeMe::~PmergeMe() {}

/* ──────────────────────────────── getters ──────────────────────────────── */

/* ──────────────────────────── member functions ─────────────────────────── */

/* ──────────────────────────────── exception ────────────────────────────── */
const char *PmergeMe::Error::what() const throw() {
	return (BRERR " ");
}