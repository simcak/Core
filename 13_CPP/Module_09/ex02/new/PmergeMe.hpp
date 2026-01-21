#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <vector>
#include <deque>
#include <set>
#include <string>
#include <iostream>
#include <iomanip>
#include <exception>
#include <cstdlib>
#include <ctime>
#include <limits>

#define BR		"\033[1;31m"
#define BG		"\033[1;32m"
#define BY		"\033[1;33m"
#define RST		"\033[0m"
#define BRERR	BR "Error" RST "\n"

#define COMPARISON_COUNT 1

class PmergeMe
{
public:
	PmergeMe();
	PmergeMe(const PmergeMe &copy);
	PmergeMe	&operator=(const PmergeMe &other);
	~PmergeMe();

	void	checkInput(int argc, char** argv);
	void	printBefore() const;
	void	sortVector();
	void	sortDeque();
	void	printAfter() const;

	class Error : public std::exception {
	public:
		const char* what() const throw() {
			return BRERR;
		}
	};

private:
	// ---------- input ----------
	std::vector<int>	_input;

	// ---------- results ----------
	std::vector<int>	_sortedVec;
	std::deque<int>		_sortedDeq;

	// ---------- timing ----------
	double				_msVec;
	double				_msDeq;

	// ---------- comparisons ----------
	long				_compsVec;
	long				_compsDeq;

private:
	// ===== validation helpers =====
	static bool	_isDigitString(const char* s);
	static long	_parsePositiveLong(const char* s);

	// ===== algorithm helpers (templated) =====
	template <typename Block, typename Outer>
	static void	_buildBlocks(const std::vector<int>& in, Outer& outBlocks)
	{
		outBlocks.clear();
		for (std::vector<int>::const_iterator it = in.begin(); it != in.end(); ++it) {
			Block b;
			b.push_back(*it);
			outBlocks.push_back(b);
		}
	}

	template <typename Block, typename Outer, typename IntCont>
	static void	_flattenBlocks(const Outer& blocks, IntCont& out)
	{
		out.clear();
		for (typename Outer::const_iterator it = blocks.begin(); it != blocks.end(); ++it) {
			// block is a container itself
			for (typename Block::const_iterator jt = it->begin(); jt != it->end(); ++jt)
				out.push_back(*jt);
		}
	}

	template <typename Block>
	static bool	_blockEq(const Block& a, const Block& b) { return a == b; }

	template <typename Block>
	static int	_blockKey(const Block& b) { return b.back(); }

	template <typename Block>
	static bool	_findSmallOfLarge(
		const std::vector< std::pair<Block, Block> >& pairs,
		const Block& large,
		Block& outSmall)
	{
		for (size_t i = 0; i < pairs.size(); ++i) {
			if (_blockEq(pairs[i].second, large)) {
				outSmall = pairs[i].first;
				return true;
			}
		}
		return false;
	}

	template <typename Block>
	static bool	_findLargeOfSmall(
		const std::vector< std::pair<Block, Block> >& pairs,
		const Block& small,
		Block& outLarge)
	{
		for (size_t i = 0; i < pairs.size(); ++i) {
			if (_blockEq(pairs[i].first, small)) {
				outLarge = pairs[i].second;
				return true;
			}
		}
		return false;
	}

	template <typename Outer, typename Block>
	static int	_indexOf(const Outer& chain, const Block& value)
	{
		for (int i = 0; i < (int)chain.size(); ++i) {
			if (_blockEq(chain[i], value))
				return i;
		}
		return -1;
	}

	// upper_bound in [0..hi] comparing by .back()
	template <typename Outer>
	static int	_upperBoundByBack(const Outer& chain, int hi, int target, long& comps)
	{
		if (hi < 0) return 0; // empty prefix => insert at begin
		int lo = 0;
		int r  = hi;

		while (lo <= r) {
			int mid = lo + (r - lo) / 2;
			comps++;
			if (chain[mid].back() < target)
				lo = mid + 1;
			else
				r = mid - 1;
		}
		return lo;
	}

	static std::vector<int>	_genJacobLimits(int need)
	{
		// sequence: 3, 5, 11, 21, 43, ...
		// recurrence: next = b + 2*a (with a=1, b=3)
		std::vector<int> j;
		int a = 1;
		int b = 3;
		while (b < need + 2) {
			j.push_back(b);
			int c = b + 2 * a;
			a = b;
			b = c;
		}
		return j;
	}

	template <typename Outer, typename Block>
	static void	_insertPendFordJohnson(
		Outer& mainChain,
		Outer& pend,
		const std::vector< std::pair<Block, Block> >& pairs,
		long& comps)
	{
		if (pend.empty())
			return;

		std::vector<int> jac = _genJacobLimits((int)pend.size());
		int prev = 1;

		for (size_t j = 0; j < jac.size() && !pend.empty(); ++j) {
			int cur = jac[j];
			int groupCount = cur - prev;
			if (groupCount <= 0) {
				prev = cur;
				continue;
			}

			// If not enough elements left for this group => stop and insert the rest from the back
			if (groupCount > (int)pend.size())
				break;

			// Insert first groupCount elements in reverse index order: groupCount-1 .. 0
			for (int idx = groupCount - 1; idx >= 0; --idx) {
				Block b = pend[idx];

				// bounded search end: before partner large
				Block partnerLarge;
				int searchHi = (int)mainChain.size() - 1; // default: full chain
				if (_findLargeOfSmall(pairs, b, partnerLarge)) {
					int partnerPos = _indexOf(mainChain, partnerLarge);
					if (partnerPos >= 0)
						searchHi = partnerPos - 1;
				}

				int pos = _upperBoundByBack(mainChain, searchHi, _blockKey(b), comps);
				mainChain.insert(mainChain.begin() + pos, b);

				// erase b from pend at idx (safe since idx goes down)
				pend.erase(pend.begin() + idx);
			}

			prev = cur;
		}

		// Insert whatever remains from the back (safe indices)
		for (int idx = (int)pend.size() - 1; idx >= 0; --idx) {
			Block b = pend[idx];

			Block partnerLarge;
			int searchHi = (int)mainChain.size() - 1;
			if (_findLargeOfSmall(pairs, b, partnerLarge)) {
				int partnerPos = _indexOf(mainChain, partnerLarge);
				if (partnerPos >= 0)
					searchHi = partnerPos - 1;
			}

			int pos = _upperBoundByBack(mainChain, searchHi, _blockKey(b), comps);
			mainChain.insert(mainChain.begin() + pos, b);
			pend.erase(pend.begin() + idx);
		}
	}

	template <typename Outer, typename Block>
	static void	_fordJohnsonBlocks(Outer& elems, long& comps)
	{
		if (elems.size() <= 1)
			return;

		// 1) Pair up elements, keep (small, large) + list of larges
		size_t pairCount = elems.size() / 2;
		std::vector< std::pair<Block, Block> > pairs;
		pairs.reserve(pairCount);

		Outer larges;
		bool hasStraggler = (elems.size() % 2 != 0);
		Block straggler;

		for (size_t i = 0; i < pairCount; ++i) {
			Block x = elems[2 * i];
			Block y = elems[2 * i + 1];

			comps++;
			if (x.back() <= y.back()) {
				pairs.push_back(std::make_pair(x, y)); // (small, large)
				larges.push_back(y);
			} else {
				pairs.push_back(std::make_pair(y, x));
				larges.push_back(x);
			}
		}

		if (hasStraggler)
			straggler = elems[elems.size() - 1];

		// 2) Recursively sort larges
		_fordJohnsonBlocks<Outer, Block>(larges, comps);

		// 3) Build main chain + pend
		Outer mainChain;
		Outer pend;

		// mainChain starts with b1 (small of smallest large) then smallest large
		Block smallestLarge = larges[0];
		Block b1;
		if (!_findSmallOfLarge(pairs, smallestLarge, b1)) {
			// should not happen with valid pairs
			return;
		}
		mainChain.push_back(b1);
		mainChain.push_back(smallestLarge);

		// append remaining larges in sorted order
		for (size_t i = 1; i < larges.size(); ++i)
			mainChain.push_back(larges[i]);

		// pend = small partners of larges[1..] in that order, plus straggler at end
		for (size_t i = 1; i < larges.size(); ++i) {
			Block si;
			_findSmallOfLarge(pairs, larges[i], si);
			pend.push_back(si);
		}
		if (hasStraggler)
			pend.push_back(straggler);

		// 4) Insert pend using Jacobsthal grouping + bounded search
		_insertPendFordJohnson<Outer, Block>(mainChain, pend, pairs, comps);

		elems.swap(mainChain);
	}

	static bool	_isSorted(const std::vector<int>& v);
	static bool	_sameResult(const std::vector<int>& v, const std::deque<int>& d);
};

#endif
