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

		if (*endptr != '\0' || value > INT_MAX || value <= 0)
			throw PmergeMe::Limit();
		
		output.push_back(static_cast<int>(value));
	}
	if (output.empty())
		throw PmergeMe::EmptyArg();
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

/* ──────────────────────────── member functions ─────────────────────────── */
// ─  ─  ─  ─  ─  ─  ─  ─  ─  ─ helper functions ─  ─  ─  ─  ─  ─  ─  ─  ─  ─ //
static bool	same(std::vector<int> vector, std::deque<int> deque)
{
	if (vector.size() != deque.size())
		return false;
	for (size_t i = 0; i < vector.size(); ++i)
		if (vector[i] != deque[i])
			return false;
	return true;
}

static void	sequence(int key, std::vector<int> &vector)
{
	key == BEFORE ? std::cout << "Before:\t" : std::cout << "After:\t";
	for (std::vector<int>::iterator it = vector.begin(); it != vector.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

// ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  //
void	PmergeMe::sort()
{
	// std::vector<int>	vSorted;
	// std::deque<int>	dSorted;

	same(_vector, _deque) ? sequence(BEFORE, _vector) : throw DiffRes();
	// timeVector = FordJohnson_vector(vSorted);
	// timeDeque = FordJohnson_deque(dSorted);
	// same(vSorted, dSorted) ? sequence(AFTER, vSorted) : throw DiffRes();
	// std::cout << timeVector << "\n" << timeDeque << std::endl;
}

/* ──────────────────────────────── exception ────────────────────────────── */
const char *PmergeMe::Limit::what() const throw() {
	return (BRERR "There is too large int or 0 on input.");
}

const char *PmergeMe::DiffRes::what() const throw() {
	return (BRERR "The containers must match!");
}

const char *PmergeMe::EmptyArg::what() const throw() {
	return (BRERR "There must be non-empty argument on input.");
}
