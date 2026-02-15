#include "PmergeMe.hpp"

int	main(int argc, char **argv)
{
	PmergeMe	pm2;
	PmergeMe	pm1;

	try {
		pm2.initCheckInput(argc, argv);
		pm1 = pm2;
		PmergeMe	pm(pm1);

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
