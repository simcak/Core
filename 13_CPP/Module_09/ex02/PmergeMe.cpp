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
#include <sys/time.h>

static double now_us()
{
	timeval	tv;

	gettimeofday(&tv, 0);
	return (tv.tv_sec * 1000000.0) + tv.tv_usec;
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
		if (i++ < 13) { std::cout << *it << " "; }
		else { std::cout << "[...]"; break; }
	}
	std::cout << std::endl;
}

// ─  ─  ─  ─  ─  ─  ─  ─  ─ Ford-Johnson Algorithm ─  ─  ─  ─  ─  ─  ─  ─  ─ //
struct Pair { int small; int big; };


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

/**
 * @brief Carefully decide in what order to insert the remaining small numbers.
 * 
 * Jacobsthal order depends ONLY on how many pairs there are (not on the actual
 *  numbers).
 */
static std::vector<size_t> jacobsthalOrder(size_t pairCount)
{
}

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
	mergeSortPairs(pairs);

	// 3) 1st small + all big
	C	sortedOutput; // clean container and put the sorted list there?
	sortedOutput.insert(sortedOutput.end(), pairs[0].small);
	for (size_t k = 0; k < pairs.size(); ++k)
		sortedOutput.insert(sortedOutput.end(), pairs[k].big);

	return (now_us() - timeStart);
}

// ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  ─  //
// #include <iomanip> 
void	PmergeMe::sort()
{
	std::vector<int>	vSorted = _vector;
	std::deque<int>		dSorted = _deque;

	same(_vector, _deque) ? sequence(BEFORE, _vector) : throw DiffRes();
	double	timeVector = FordJohnsonAlg(vSorted);
	double	timeDeque = FordJohnsonAlg(dSorted);
	same(vSorted, dSorted) ? sequence(AFTER, vSorted) : throw DiffRes();

	// std::cout << std::fixed << std::setprecision(0);
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
