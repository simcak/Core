#include "PmergeMe.hpp"

/* ───────────────────────── Orthodox Canonical Form ──────────────────────── */
PmergeMe::PmergeMe() : _input(), _sortedVec(), _sortedDeq(), _msVec(0.0),
		_msDeq(0.0), _compsVec(0), _compsDeq(0)
{}

PmergeMe::PmergeMe(const PmergeMe &copy) : _input(copy._input),
		_sortedVec(copy._sortedVec), _sortedDeq(copy._sortedDeq),
		_msVec(copy._msVec), _msDeq(copy._msDeq), _compsVec(copy._compsVec),
		_compsDeq(copy._compsDeq)
{}

PmergeMe	&PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		_input		= other._input;
		_sortedVec	= other._sortedVec;
		_sortedDeq	= other._sortedDeq;
		_msVec		= other._msVec;
		_msDeq		= other._msDeq;
		_compsVec	= other._compsVec;
		_compsDeq	= other._compsDeq;
	}
	return *this;
}

PmergeMe::~PmergeMe() {}

// ================== validation helpers ==================

#include <math.h>
static long	_maxComparisonsBound(int n)
{
	long	sum = 0;
	for (int k = 1; k <= n; ++k) {
		double x = (3.0 / 4.0) * (double)k;
		sum += (long)std::ceil(std::log(x) / std::log(2.0));
	}
	return sum;
}

bool	PmergeMe::_isDigitString(const char* s)
{
	if (!s || !*s) return false;
	for (size_t i = 0; s[i] != '\0'; ++i) {
		if (s[i] < '0' || s[i] > '9')
			return false;
	}
	return true;
}

long	PmergeMe::_parsePositiveLong(const char* s)
{
	if (!_isDigitString(s))
		throw Error();

	char	*end = 0;
	long	v = std::strtol(s, &end, 10);
	if (!end || *end != '\0')
		throw Error();

	// "positive integers" => reject 0
	if (v <= 0)
		throw Error();

	if (v > std::numeric_limits<int>::max())
		throw Error();

	return v;
}

void	PmergeMe::checkInput(int argc, char **argv)
{
	if (argc < 2)
		throw Error();

	_input.clear();
	std::set<long> seen;

	for (int i = 1; i < argc; ++i) {
		long v = _parsePositiveLong(argv[i]);
		if (seen.find(v) != seen.end())
			throw Error();
		seen.insert(v);
		_input.push_back((int)v);
	}
}

void	PmergeMe::printBefore() const
{
	std::cout << "Before: ";
	for (std::vector<int>::const_iterator it = _input.begin(); it != _input.end(); ++it)
		std::cout << *it << " ";
	std::cout << "\n";
}

// ================== sorting ==================

void	PmergeMe::sortVector()
{
	clock_t	start = std::clock();
	_compsVec = 0;

	std::vector< std::vector<int> >	blocks;
	_buildBlocks< std::vector<int>, std::vector< std::vector<int> > >(_input, blocks);

	_fordJohnsonBlocks< std::vector< std::vector<int> >, std::vector<int> >(blocks, _compsVec);

	_flattenBlocks< std::vector<int>, std::vector< std::vector<int> >, std::vector<int> >(blocks, _sortedVec);

	clock_t end = std::clock();
	_msVec = (double)(end - start) * 1000.0 / (double)CLOCKS_PER_SEC;
}

void	PmergeMe::sortDeque()
{
	clock_t start = std::clock();
	_compsDeq = 0;

	std::deque< std::deque<int> > blocks;
	_buildBlocks< std::deque<int>, std::deque< std::deque<int> > >(_input, blocks);

	_fordJohnsonBlocks< std::deque< std::deque<int> >, std::deque<int> >(blocks, _compsDeq);

	_flattenBlocks< std::deque<int>, std::deque< std::deque<int> >, std::deque<int> >(blocks, _sortedDeq);

	clock_t end = std::clock();
	_msDeq = (double)(end - start) * 1000.0 / (double)CLOCKS_PER_SEC;
}

// ================== verification ==================

bool	PmergeMe::_isSorted(const std::vector<int>& v)
{
	if (v.empty()) return true;
	std::vector<int>::const_iterator it = v.begin();
	int prev = *it;
	++it;
	for (; it != v.end(); ++it) {
		if (*it < prev)
			return false;
		prev = *it;
	}
	return true;
}

bool	PmergeMe::_sameResult(const std::vector<int>& v, const std::deque<int>& d)
{
	if (v.size() != d.size()) return false;
	for (size_t i = 0; i < v.size(); ++i) {
		if (v[i] != d[i])
			return false;
	}
	return true;
}

void	PmergeMe::printAfter() const
{
	if (!_isSorted(_sortedVec))
		throw Error();
	if (!_sameResult(_sortedVec, _sortedDeq))
		throw Error();

	std::cout << "After:  ";
	for (std::deque<int>::const_iterator it = _sortedDeq.begin(); it != _sortedDeq.end(); ++it)
		std::cout << *it << " ";
	std::cout << "\n";

	std::cout << "Time to process a range of " << _input.size()
			  << " with std::vector : " << std::setprecision(5) << _msVec << " ms\n";
	std::cout << "Time to process a range of " << _input.size()
			  << " with std::deque  : " << std::setprecision(5) << _msDeq << " ms\n";

	if (COMPARISON_COUNT)
	{
		long maxAllowed = _maxComparisonsBound((int)_input.size());

		std::cout << "\nMax allowed comparisons: " << maxAllowed << "\n";
		std::cout << "Comparisons vector: " << _compsVec << "\n";
		std::cout << "Comparisons deque : " << _compsDeq << "\n";
	}
}
