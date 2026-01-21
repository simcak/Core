#include "PmergeMe.hpp"

int	main(int argc, char **argv)
{
	PmergeMe	pm;

	try {
		pm.CheckInput(argc, argv);
		pm.printBefore();
		pm.SortVector();
		pm.SortDeque();
		pm.printAfter();
	}
	catch (std::exception &e) {
		std::cerr << e.what();
		return 1;
	}
	return 0;
}
