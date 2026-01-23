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
	static int	_upperBoundIndex(const Cont &c,
		int hiExclusive, int value, long &compsCount)
	{
		int	lo = 0;
		int	hi = hiExclusive;

		while (lo < hi)
		{
			int	mid = lo + (hi - lo) / 2;

			compsCount++;
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

	/**
	 * 
	 */
	template <typename Cont, typename P>
	static void	_insertPendFordJohnson(Cont &main_chain, Cont &pend,
		const P &pairs, bool hasStraggler, int straggler, long &compsCount)
	{
		if (pend.empty())
			return;

		std::vector<int>	jac = _genJacobsthalLimits((int)pend.size());
		int					prev = 1;
		int					jidx = -1;

		// Process Jacobsthal groups as long as they fit
		while (!pend.empty() && ++jidx < (int)jac.size())
		{
			int	cur = jac[jidx];
			int	groupCount = cur - prev;

			if (groupCount <= 0)
			{
				prev = cur;
				continue;
			}

			if (groupCount > (int)pend.size())
				break;

			// Insert indices groupCount-1 .. 0 (reverse inside group)
			for (int idx = groupCount - 1; idx >= 0; --idx)
			{
				int	b = pend[idx];
				int	boundExclusive = (int)main_chain.size();

				if (!(hasStraggler && b == straggler))
				{
					int	a = 0;

					if (_findLargeOfSmall(pairs, b, a))
					{
						int	posA = _indexOfValue(main_chain, a);

						if (posA >= 0)
							boundExclusive = posA; // exclusive => before a
					}
				}

				int	pos = _upperBoundIndex(main_chain, boundExclusive, b, compsCount);

				main_chain.insert(main_chain.begin() + pos, b);
				pend.erase(pend.begin() + idx);
			}
			prev = cur;
		}

		// Insert whatever remains from the back
		for (int idx = (int)pend.size() - 1; idx >= 0; --idx)
		{
			int	b = pend[idx];
			int	boundExclusive = (int)main_chain.size();

			if (!(hasStraggler && b == straggler))
			{
				int	a = 0;

				if (_findLargeOfSmall(pairs, b, a))
				{
					int	posA = _indexOfValue(main_chain, a);

					if (posA >= 0)
						boundExclusive = posA;
				}
			}
			int	pos = _upperBoundIndex(main_chain, boundExclusive, b, compsCount);

			main_chain.insert(main_chain.begin() + pos, b);
			pend.erase(pend.begin() + idx);
		}
	}

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

	template <typename Cont>
	static void	_fordJohnsonSort(Cont &arr, long &compsCount)
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

		// 3) Build main_chain = [b1, a1, a2, ...] and pend = remaining b's (in order of sorted a's)
		Cont	main_chain;
		Cont	pend;
		int		a1 = larges[0];
		int		b1 = 0;

		if (!_findSmallOfLarge(pairs, a1, b1))
			return;	// should not happen if pairs are consistent

		main_chain.push_back(b1);
		main_chain.push_back(a1);

		// For each remaining sorted a, append a to main chain and collect its partner b to pend
		for (int i = 1; i < (int)larges.size(); ++i)
		{
			int	a = larges[i];
			int	b = 0;

			_findSmallOfLarge(pairs, a, b);
			main_chain.push_back(a);
			pend.push_back(b);
		}

		if (hasStraggler)
			pend.push_back(straggler);

		// 4) Insert pend using Jacobsthal order, bounded by partner position
		_insertPendFordJohnson(main_chain, pend, pairs, hasStraggler, straggler, compsCount);

		// Write back
		arr.swap(main_chain);
	}

};

#endif
