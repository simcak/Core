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
	/* ─ ─ ─ ─ ─ ─ ─ ─ ─ limits: (1), 3, 5, 11, 21, 43, ... ─ ─ ─ ─ ─ ─ ─ ─ ─ */
	static std::vector<int>	_genJacobsthalLimits(int need)
	{
		std::vector<int>	jContainer;
		int					a = 1, b = 1, next = 0;

		while (b < need + 2)
		{
			jContainer.push_back(b);
			next = b + 2 * a;
			a = b;
			b = next;
		}
		return jContainer;
	}

	/* ─ ─ ─ ─ ─ ─ ─ Find 'outSmall' from 'pairs' by 'large' el ─ ─ ─ ─ ─ ─ ─ */
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

	/* ───────────────────── _insertPendGroup() helpers ───────────────────── */
	/* ─ ─ ─ ─ ─ ─ ─ Find 'outLarge' from 'pairs' by 'small' el ─ ─ ─ ─ ─ ─ ─ */
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

	/* ─ ─ ─ ─ ─ ─ ─ ─ ─  find index in _insertPendGroup()  ─ ─ ─ ─ ─ ─ ─ ─ ─ */
	template <typename Cont>
	static int	_indexOfValue(const Cont &c, int value)
	{
		for (int i = 0; i < (int)c.size(); ++i)
			if (c[i] == value)
				return i;
		return -1;
	}

	/* ─ ─ upper_bound index in c[0...hi) for value in _insertPendGroup() ─ ─ */
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

	/* ─ ─ ─ ─ ─ ─ insert each group from 'pendC' to 'main' chain ─ ─ ─ ─ ─ ─ */
	template <typename Cont, typename P>
	static void	_insertPendGroup(int groupLen, Cont &mainC, Cont &pendC, const P &pairs, bool hasStraggler, int straggler, long &cc)
	{
		for (int i = groupLen - 1; i >= 0; --i)
		{
			int	bi = pendC[i];
			int	boundExclusive = (int)mainC.size();

			if (!(hasStraggler && bi == straggler))
			{
				int	ai = 0;

				if (_findLargeOfSmall(pairs, bi, ai))
				{
					int	posA = _indexOfValue(mainC, ai);

					if (posA >= 0)
						boundExclusive = posA; // exclusive => before ai
				}
			}

			int	pos = _upperBoundIndex(mainC, boundExclusive, bi, cc);

			mainC.insert(mainC.begin() + pos, bi);
			pendC.erase(pendC.begin() + i);
		}
	}

	/* ───────────────────────────── Hub helpers ──────────────────────────── */
	/* ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ quatro ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ */
	/** @brief
	 *  By Jacobsthal order, insert from pend to main chain in reverse order.
	 */
	template <typename Cont, typename P>
	static void	_insertPend(Cont &mainC, Cont &pendC, const P &pairs, bool hasStraggler, int straggler, long &cc)
	{
		if (pendC.empty())
			return;

		std::vector<int>	jac = _genJacobsthalLimits((int)pendC.size());

		// Process Jacobsthal groups as long as they fit
		for (int i = 1; !pendC.empty() && i < (int)jac.size(); ++i)
		{
			int	jacGroupLen = jac[i] - jac[i-1];

			if (jacGroupLen <= 0)
				continue;

			if (jacGroupLen > (int)pendC.size())
				break;

			// Insert indices jacGroupLen-1 .. 0 (reverse inside group)
			_insertPendGroup(jacGroupLen, mainC, pendC, pairs, hasStraggler, straggler, cc);
		}
\
		// Insert whatever remains from the back (reverse after groups)
		_insertPendGroup((int)pendC.size(), mainC, pendC, pairs, hasStraggler, straggler, cc);
	}

	/* ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ tr3s ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ */
	/** @brief
	 *  mainChain = [b1, a1, a2, ...]
	 *  pendChain = remaining b's (in order of sorted a's)
	 *  a = large   b = small   (for pairs)
	 */
	template <typename Cont, typename P>
	static void	_buildMainPend(Cont &mainC, Cont &pendC, P &pairs, Cont &aArr)
	{
		int	a1 = aArr[0], b1 = 0;

		if (!_findSmallOfLarge(pairs, a1, b1))
			return;	// should not happen if pairs are consistent

		mainC.push_back(b1);
		mainC.push_back(a1);

		for (int i = 1; i < (int)aArr.size(); ++i)
		{
			int	ai = aArr[i], bi = 0;

			_findSmallOfLarge(pairs, ai, bi);
			mainC.push_back(ai);
			pendC.push_back(bi);
		}
	}

	/* ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ 1) uno ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ */
	template <typename Cont, typename P>
	static void	_makePairs(Cont &arr, P &pairs, Cont &larges, int n, long &cc)
	{
		pairs.reserve(n / 2);
		for (int i = 0; i < n-1; i+=2)
		{
			int	x = arr[i], y = arr[i+1];

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

		_makePairs(arr, pairs, larges, n, compsCount);

		bool	hasStraggler = (n % 2 != 0);
		int		straggler = 0;

		if (hasStraggler)
			straggler = arr[n - 1];

		// 2) Recursively sort the a_i sequence
		_fordJohnsonSort(larges, compsCount);

		// 3) Build Chains
		Cont	mainChain;
		Cont	pendChain;

		_buildMainPend(mainChain, pendChain, pairs, larges);

		if (hasStraggler)
			pendChain.push_back(straggler);

		// 4) Insert pendChain using Jacobsthal order, bounded by partner position
		_insertPend(mainChain, pendChain, pairs, hasStraggler, straggler, compsCount);

		// Write back
		arr.swap(mainChain);
	}

};

#endif
