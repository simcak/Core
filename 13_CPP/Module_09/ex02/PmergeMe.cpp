#include "PmergeMe.hpp"

/* ───────────────────────── Orthodox Canonical Form ──────────────────────── */
PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const std::string input)
{
	std::cout << "test: " << input << std::endl;
}

PmergeMe::PmergeMe(const PmergeMe &copy)
	:	_vector(copy._vector.begin(), copy._vector.end()),
		_deque(copy._deque.begin(), copy._deque.end()) {}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		this->_vector = other._vector;
		this->_deque = other._deque;
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