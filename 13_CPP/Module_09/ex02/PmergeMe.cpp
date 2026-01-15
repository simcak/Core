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
#include <time.h>

static double now_us()
{
	struct timespec	ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ts.tv_sec * 1000000.0 + ts.tv_nsec / 1000.0;
}

static bool	same(std::vector<int> &vector, std::deque<int> &deque)
{
	if (vector.size() != deque.size())
		return false;
	for (size_t i = 0; i < vector.size(); ++i)
		if (vector[i] != deque[i])
			return false;
	return true;
}

template<typename C>
static void	sequence(int key, const C &v)
{
	int	i = 0;

	key == BEFORE ? std::cout << "Before:\t" : std::cout << "After:\t";
	for (typename C::const_iterator it = v.begin(); it != v.end(); ++it)
	{
		if (i++ < 42) { std::cout << *it << " "; }
		else { std::cout << "[...]"; break; }
	}
	std::cout << std::endl;
}

// ─  ─  ─  ─  ─  ─  ─  ─  ─  Big number handeling  ─  ─  ─  ─  ─  ─  ─  ─  ─ //
struct Pair { int small; int big; };

/**
 * @brief Merge step for merge-sort: merges two sorted subranges of `pairs` into
 *        one sorted range.
 *
 * Merges the half-open ranges [left, mid) and [mid, right) from `pairs` into
 * the temporary buffer `tmP`, ordered by `Pair::big`, then copies the merged
 * result back into `pairs`.
 *
 * when `pairs[l].big == pairs[m].big`, the left element is chosen first.
 */
static void mergePairs(std::vector<Pair> &pairs, std::vector<Pair> &tmP,
					   size_t left, size_t mid, size_t right)
{
	size_t	l = left, m = mid, k = left;

	while (l < mid && m < right) {
		tmP[k++] = (pairs[l].big <= pairs[m].big) ? pairs[l++] : pairs[m++];
	}
	while (l < mid)		tmP[k++] = pairs[l++];
	while (m < right)	tmP[k++] = pairs[m++];

	for (size_t x = left; x < right; ++x)
		pairs[x] = tmP[x];
}

/**
 * @brief Split list into 1 int long elements by halfs recursively and merge
 *        them by size into sorted order.
 * 
 * 1st - we split left halfs, until we have one number remaining. Than we split
 * right halfs. Once we have one element ramaining everywhere - it means we have
 * finished the recursion and stocked mergePairs() comes in place. It merge the
 * numbers by size into sorted order in a backward order. The final recursion
 * merge is comparing sorted left and right lists.
 */
static void sortMergePairsRec(std::vector<Pair> &pairs, std::vector<Pair> &tmP,
							  size_t left, size_t right)
{
	if (right - left <= 1) return;

	size_t	mid = left + (right - left) / 2;
	sortMergePairsRec(pairs, tmP, left, mid);
	sortMergePairsRec(pairs, tmP, mid, right);
	mergePairs(pairs, tmP, left, mid, right);
}

static void sortMergeBig(std::vector<Pair> &pairs)
{
	if (pairs.size() <= 1) return;

	std::vector<Pair>	tmP(pairs.size());
	sortMergePairsRec(pairs, tmP, 0, pairs.size());
}

/**
 * @brief container -> [samll, big] pairs + leftover.
 */
template<typename C>
static int	makeSmallBig(std::vector<Pair> &pairs, C &container)
{
	bool	hasOdd = (container.size() % 2 != 0);
	pairs.reserve(container.size() / 2); // could we have "container.size() / 2" in constructor?

	for (size_t i = 1; i < container.size(); i += 2)
	{
		int		frst = container[i - 1];
		int		scnd = container[i];
		Pair	p;
		p.small = frst <= scnd ? frst : scnd;
		p.big   = frst > scnd  ? frst : scnd;
		pairs.push_back(p);
	}

	int	straggler = hasOdd ? container[container.size() - 1] : 0;
	return (straggler);
}

// ─  ─  ─  ─  ─  ─  ─  ─  ─ Small number handeling ─  ─  ─  ─  ─  ─  ─  ─  ─ //
/**
 * @brief Carefully decide in what order to insert the remaining small numbers.
 * 
 * Jacobsthal order depends ONLY on how many pairs there are (not on the actual
 *  numbers).
 */
static std::vector<size_t> jacobsthalOrder(size_t pairCount)
{
	std::vector<size_t>	order;
	if (pairCount <= 1)
		return order;

	order.push_back(1);
	
	size_t	j_minus2 = 0, j_minus1 = 1, insertedUpTo = 1;
	while (insertedUpTo < pairCount - 1)
	{
		size_t	j = j_minus1 + (2 * j_minus2);
		j_minus2 = j_minus1;
		j_minus1 = j;

		if (j <= insertedUpTo)
			continue;

		size_t	limit = j;
		if (limit > pairCount - 1)
			limit = pairCount - 1;

		for (size_t idx = limit; idx > insertedUpTo; --idx)
			order.push_back(idx);

		insertedUpTo = limit;
	}
	return order;
}

#include <algorithm>	// lower/upper_bound()
template<typename C>
static void	sortMergeSmall(std::vector<Pair> &pairs, C &cont,
						   std::vector<size_t> &order,
						   std::vector<size_t> &bigPos)
{
	for (size_t oi = 0; oi < order.size(); ++oi)
	{
		size_t	idx = order[oi];

		typename C::iterator bound = cont.begin() + bigPos[idx];

		typename C::iterator pos =
			std::lower_bound(cont.begin(), bound, pairs[idx].small);

		size_t	insertIdx = static_cast<size_t>(pos - cont.begin());
		cont.insert(pos, pairs[idx].small);
		for (size_t j = 0; j < bigPos.size(); ++j)
			if (bigPos[j] >= insertIdx)
				++bigPos[j];
	}
}

// ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─ main ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─ //
template<typename C>
static double	FordJohnsonAlg(C &container)
{
	double	timeStart = now_us();
	if (container.size() <= 1)
		return (now_us() - timeStart);

	// 1)
	std::vector<Pair>	pairs;
	int	oddStraggler = makeSmallBig(pairs, container);

	// 2)
	sortMergeBig(pairs);

	// 3) 1st small + all big
	C	clean; container = clean;
	container.insert(container.end(), pairs[0].small);

	std::vector<size_t>	bigPos(pairs.size());
	for (size_t k = 0; k < pairs.size(); ++k) {
		container.push_back(pairs[k].big);
		bigPos[k] = k + 1;
	}

	// 4)
	std::vector<size_t> order = jacobsthalOrder(pairs.size());
	sortMergeSmall(pairs, container, order, bigPos);

	// 5)
	if (oddStraggler)
	{
		typename C::iterator pos =
			std::lower_bound(container.begin(), container.end(), oddStraggler);
		container.insert(pos, oddStraggler);
	}

	return (now_us() - timeStart);
}

// ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  //
#include <iomanip> 
void	PmergeMe::sort()
{
	std::vector<int>	vSorted = _vector;
	std::deque<int>		dSorted = _deque;

	same(_vector, _deque) ? sequence(BEFORE, _vector) : throw DiffRes();
	double	timeVector = FordJohnsonAlg(vSorted);
	double	timeDeque = FordJohnsonAlg(dSorted);
	same(vSorted, dSorted) ? sequence(AFTER, vSorted) : throw DiffRes();

	std::cout << std::fixed << std::setprecision(3);
	std::cout << "Time to process a range of " << vSorted.size()
			<< " elements with std::vector : " << timeVector << " us\n";
	std::cout << "Time to process a range of " << dSorted.size()
			<< " elements with std::deque  : " << timeDeque << " us\n";
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
