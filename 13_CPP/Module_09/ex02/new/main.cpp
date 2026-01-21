#include "PmergeMe.hpp"

int	main(int argc, char **argv)
{
	PmergeMe	pm;

	try {
		pm.checkInput(argc, argv);
		pm.printBefore();
		pm.sortVector();
		pm.sortDeque();
		pm.printAfter();
	}
	catch (std::exception &e) {
		std::cerr << e.what();
		return 1;
	}
	return 0;
}
