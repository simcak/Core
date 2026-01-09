#include "PmergeMe.hpp"
#include <limits.h>
#include <stdlib.h>

static std::vector<int>	strToVector(std::string str)
{
	std::istringstream	iss(str);
	std::string			arg;
	std::vector<int>	output;

	while (iss >> arg)
	{
		char	*endptr;
		long	value = std::strtol(arg.c_str(), &endptr, 10);

		if (*endptr != '\0' || value > INT_MAX)
			throw PmergeMe::Limit();
		
		output.push_back(static_cast<int>(value));
	}
	return output;
}

/* ───────────────────────── Orthodox Canonical Form ──────────────────────── */
PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const std::string input)
{
	_vector = strToVector(input);
	_deque = std::deque<int>(_vector.begin(), _vector.end());
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
void	PmergeMe::sort()
{
	std::cout << "Vector: ";
	for (std::vector<int>::iterator it = _vector.begin(); it != _vector.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::cout << "Deque: ";
	for (std::deque<int>::iterator it = _deque.begin(); it != _deque.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

/* ──────────────────────────────── exception ────────────────────────────── */
const char *PmergeMe::Limit::what() const throw() {
	return (BRERR "There is too large int on input.");
}