#include "PmergeMe.hpp"

/* ───────────────────────── Orthodox Canonical Form ──────────────────────── */
PmergeMe::PmergeMe() : _input(), _sortedVec(), _sortedDeq(), _msVec(0.0),
		_msDeq(0.0), _compsVecCounter(0), _compsDeqCounter(0)
{}

PmergeMe::PmergeMe(const PmergeMe &copy) : _input(copy._input),
		_sortedVec(copy._sortedVec), _sortedDeq(copy._sortedDeq),
		_msVec(copy._msVec), _msDeq(copy._msDeq), _compsVecCounter(copy._compsVecCounter),
		_compsDeqCounter(copy._compsDeqCounter)
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
		_compsVecCounter	= other._compsVecCounter;
		_compsDeqCounter	= other._compsDeqCounter;
	}
	return *this;
}

PmergeMe::~PmergeMe() {}

/* ───────────────────────────────── helpers ──────────────────────────────── */
/*  ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ For debugging / defending ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ */
#include <math.h>
static long	_maxComparisonsAllowed(int n)
{
	long	sum = 0;

	for (int k = 1; k <= n; ++k)
	{
		double x = (3.0 / 4.0) * (double)k;
		sum += (long)std::ceil(std::log(x) / std::log(2.0));
	}
	return sum;
}

/* ─ ─ ─ ─ ─ Verification of sorting alg. If false -> throw Error() ─ ─ ─ ─ ─ */
static bool	_isSorted(const std::vector<int> &v)
{
	if (v.empty())
		return true;

	std::vector<int>::const_iterator	it = v.begin();
	int									prev = *it;

	++it;
	for (; it != v.end(); ++it)
	{
		if (*it < prev)
			return false;
		prev = *it;
	}
	return true;
}

static bool	_sameResult(const std::vector<int> &v, const std::deque<int> &d)
{
	if (v.size() != d.size())
		return false;

	for (size_t i = 0; i < v.size(); ++i)
		if (v[i] != d[i])
			return false;

	return true;
}

/* ─ ─ ─ ─ ─ ─ ─ ─ ─ ─  ─ ─ initCheckInput() helpers ─ ─ ─ ─ ─ ─ ─ ─ ─ ─  ─ ─ */
static bool	_isDigitString(const char *s)
{
	if (!s || !*s)
		return false;

	for (size_t i = 0; s[i] != '\0'; ++i)
		if (s[i] < '0' || s[i] > '9')
			return false;

	return true;
}

static long	_parsePositiveLong(const char *s)
{
	if (!_isDigitString(s))
		return -1;

	char	*end = 0;
	long	v = std::strtol(s, &end, 10);

	if (!end || *end != '\0' || v <= 0 || v > std::numeric_limits<int>::max())
		return -1;

	return v;
}

/* ──────────────────────────── member functions ──────────────────────────── */
void	PmergeMe::initCheckInput(int argc, char **argv)
{
	if (argc < 2)
		throw Error();

	_input.clear();
	for (int i = 1; i < argc; ++i) 
	{
		long	v = _parsePositiveLong(argv[i]);

		if(v == -1)
			throw Error();

		for (std::vector<int>::const_iterator it = _input.begin(); it != _input.end(); ++it)
			if (*it == (int)v)
				throw Error();	// duplicates
		_input.push_back((int)v);
	}
}

/*  ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ sorting ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ */
void	PmergeMe::sortVector()
{
	std::vector<int>	v = _input;
	clock_t				start = std::clock();

	_compsVecCounter = 0;
	_fordJohnsonSort(v, _compsVecCounter);
	_sortedVec = v;
	_msVec = (double)(std::clock() - start) * 1000.0 / (double)CLOCKS_PER_SEC;
}

void	PmergeMe::sortDeque()
{
	std::deque<int>	d;
	clock_t			start = 0;

	for (std::vector<int>::const_iterator it = _input.begin(); it != _input.end(); ++it)
		d.push_back(*it);

	start = std::clock();
	_compsDeqCounter = 0;
	_fordJohnsonSort(d, _compsDeqCounter);
	_sortedDeq = d;
	_msDeq = (double)(std::clock() - start) * 1000.0 / (double)CLOCKS_PER_SEC;
}

/* ─ ─ ─ ─ ─ ─ ─ ─ ─ ─  ─ ─ ─ ─ ─ ─ printing ─ ─ ─ ─ ─ ─ ─ ─ ─ ─  ─ ─ ─ ─ ─ ─ */
void	PmergeMe::printBefore() const
{
	std::cout << "Before: ";
	for (std::vector<int>::const_iterator it = _input.begin(); it != _input.end(); ++it)
		std::cout << *it << " ";
	std::cout << "\n";
}

void	PmergeMe::printAfter() const
{
	if (!_isSorted(_sortedVec) || !_sameResult(_sortedVec, _sortedDeq))
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
		long maxAllowed = _maxComparisonsAllowed((int)_input.size());

		std::cout << "\nMax allowed comparisons: " << maxAllowed << "\n";
		std::cout << "Comparisons vector: " << _compsVecCounter << "\n";
		std::cout << "Comparisons deque : " << _compsDeqCounter << "\n";
	}
}
