#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <vector>
#include <deque>
#include <iostream>
#include <iomanip>
#include <exception>
#include <cstdlib>
#include <ctime>
#include <limits>

#ifndef COMPARISON_COUNT
# define COMPARISON_COUNT 0
#endif

/* ───────────────────────────────── Colors ───────────────────────────────── */
#define BR		"\033[1;31m"
#define BG		"\033[1;32m"
#define BY		"\033[1;33m"
#define RST		"\033[0m"
#define BRERR	BR "Error" RST "\n"


class PmergeMe
{
public:
	/* ─────────────────────── Orthodox Canonical Form ────────────────────── */
	PmergeMe();
	PmergeMe(const PmergeMe &copy);
	PmergeMe	&operator=(const PmergeMe &other);
	~PmergeMe();

	void	initCheckInput(int argc, char **argv);
	void	printBefore() const;
	void	sortVector();
	void	sortDeque();
	void	printAfter() const;

	/* ────────────────────────────── Exception ───────────────────────────── */
	class Error : public std::exception {
	public:
		const char* what() const throw() {
			return BRERR;
		}
	};

private:
	/* ──────────────────────────────── Input ─────────────────────────────── */
	std::vector<int>	_input;
	/* ─────────────────────────────── Results ────────────────────────────── */
	std::vector<int>	_sortedVec;
	std::deque<int>		_sortedDeq;
	/* ─────────────────────────────── Timing ─────────────────────────────── */
	double				_msVec;
	double				_msDeq;
	/* ───────────────────────────── Comparation ──────────────────────────── */
	long				_compsVecCounter;
	long				_compsDeqCounter;

private:
	/* ─────────────────────────────── Helpers ────────────────────────────── */
	/* ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ limits: 3, 5, 11, 21, 43, ...  ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ */
	static std::vector<int>	_genJacobsthalLimits(int need)
	{
		std::vector<int>	jContainer;
		int					a = 1, b = 3, next = 0;

		while (b < need + 2)
		{
			jContainer.push_back(b);
			next = b + 2 * a;
			a = b;
			b = next;
		}
		return jContainer;
	}

	template <typename Cont>
	static int	_indexOfValue(const Cont &c, int value)
	{
		for (int i = 0; i < (int)c.size(); ++i)
			if (c[i] == value)
				return i;
		return -1;
	}

	// upper_bound index in c[0..hiExclusive) for value
	template <typename Cont>
	static int	_upperBoundIndex(const Cont &c, int hi, int value, long &cc)
	{
		int	lo = 0, mid = 0;

		while (lo < hi)
		{
			mid = lo + (hi - lo) / 2;
			cc++;
			(c[mid] <= value) ? lo = mid + 1 : hi = mid;
		}
		return lo;
	}

	/** @brief:
	 *  By the `large` var, find its paired.small from `pairs` and store it to
	 *  the value `outSmall`.
	*/
	template <typename P>
	static bool	_findSmallOfLarge(const P &pairs, int large, int &outSmall)
	{
		for (int i = 0; i < (int)pairs.size(); ++i)
		{
			if (pairs[i].second == large)
			{
				outSmall = pairs[i].first;
				return true;
			}
		}
		return false;
	}

	/** @brief:
	 *  By the `small` var, find its paired.large from `pairs` and store it to
	 *  the value `outLarge`.
	*/
	template <typename P>
	static bool	_findLargeOfSmall(const P &pairs, int small, int &outLarge)
	{
		for (int i = 0; i < (int)pairs.size(); ++i)
		{
			if (pairs[i].first == small)
			{
				outLarge = pairs[i].second;
				return true;
			}
		}
		return false;
	}

	/* ───────────────────────────── Hub helpers ──────────────────────────── */
	/* ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ quatro ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ */
	/**
	 * 
	 */
	template <typename Cont, typename P>
	static void	_insertPend(Cont &mainC, Cont &pendC,
		const P &pairs, bool hasStraggler, int straggler, long &cc)
	{
		if (pendC.empty())
			return;

		std::vector<int>	jac = _genJacobsthalLimits((int)pendC.size());
		int					prev = 1;
		int					jidx = -1;

		// Process Jacobsthal groups as long as they fit
		while (!pendC.empty() && ++jidx < (int)jac.size())
		{
			int	cur = jac[jidx];
			int	groupCount = cur - prev;

			if (groupCount <= 0)
			{
				prev = cur;
				continue;
			}

			if (groupCount > (int)pendC.size())
				break;

			// Insert indices groupCount-1 .. 0 (reverse inside group)
			for (int idx = groupCount - 1; idx >= 0; --idx)
			{
				int	b = pendC[idx];
				int	boundExclusive = (int)mainC.size();

				if (!(hasStraggler && b == straggler))
				{
					int	a = 0;

					if (_findLargeOfSmall(pairs, b, a))
					{
						int	posA = _indexOfValue(mainC, a);

						if (posA >= 0)
							boundExclusive = posA; // exclusive => before a
					}
				}

				int	pos = _upperBoundIndex(mainC, boundExclusive, b, cc);

				mainC.insert(mainC.begin() + pos, b);
				pendC.erase(pendC.begin() + idx);
			}
			prev = cur;
		}

		// Insert whatever remains from the back
		for (int idx = (int)pendC.size() - 1; idx >= 0; --idx)
		{
			int	b = pendC[idx];
			int	boundExclusive = (int)mainC.size();

			if (!(hasStraggler && b == straggler))
			{
				int	a = 0;

				if (_findLargeOfSmall(pairs, b, a))
				{
					int	posA = _indexOfValue(mainC, a);

					if (posA >= 0)
						boundExclusive = posA;
				}
			}
			int	pos = _upperBoundIndex(mainC, boundExclusive, b, cc);

			mainC.insert(mainC.begin() + pos, b);
			pendC.erase(pendC.begin() + idx);
		}
	}

	/* ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ tr3s ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ */
	template <typename Cont, typename P>
	static void	_build_mainAndPend_chains(Cont &mainC, Cont &pendC, P &pairs,
		Cont &larges)
	{
		int	a1 = larges[0], b1 = 0;

		if (!_findSmallOfLarge(pairs, a1, b1))
			return;	// should not happen if pairs are consistent

		mainC.push_back(b1);
		mainC.push_back(a1);

		// For each remaining sorted a, append a to main chain and collect its partner b to pend
		for (int i = 1; i < (int)larges.size(); ++i)
		{
			int	a = larges[i], b = 0;

			_findSmallOfLarge(pairs, a, b);
			mainC.push_back(a);
			pendC.push_back(b);
		}
	}

	/* ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ 1) uno ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ */
	template <typename Cont, typename P>
	static void	_makePairs(Cont &arr, long &cc, P &pairs, Cont &larges, int n)
	{
		int	pairCount = n / 2;

		pairs.reserve(pairCount);
		for (int i = 0; i < pairCount; ++i)
		{
			int	x = arr[2*i];
			int	y = arr[2*i + 1];

			cc++;
			if (x <= y)
			{
				pairs.push_back(std::make_pair(x, y));
				larges.push_back(y);
			} else {
				pairs.push_back(std::make_pair(y, x));
				larges.push_back(x);
			}
		}
	}

	/* ───────────────────────────────── Hub ──────────────────────────────── */
	template <typename Cont>
	void	_fordJohnsonSort(Cont &arr, long &compsCount)
	{
		int	n = (int)arr.size();
		if (n <= 1)
			return;

		// 1) Pair into (b_i, a_i) where b_i <= a_i, collect all a_i
		std::vector< std::pair<int,int> >	pairs;
		Cont								larges;

		_makePairs(arr, compsCount, pairs, larges, n);

		bool	hasStraggler = (n % 2 != 0);
		int		straggler = 0;

		if (hasStraggler)
			straggler = arr[n - 1];

		// 2) Recursively sort the a_i sequence
		_fordJohnsonSort(larges, compsCount);

		// 3) Build mainChain = [b1, a1, a2, ...] and pendChain = remaining b's (in order of sorted a's)
		Cont	mainChain;
		Cont	pendChain;

		_build_mainAndPend_chains(mainChain, pendChain, pairs, larges);

		if (hasStraggler)
			pendChain.push_back(straggler);

		// 4) Insert pendChain using Jacobsthal order, bounded by partner position
		_insertPend(mainChain, pendChain, pairs, hasStraggler, straggler, compsCount);

		// Write back
		arr.swap(mainChain);
	}

};

#endif
