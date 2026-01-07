#include "RPN.hpp"

#define USAGE	BG "Correct usage:" RST " ./RPN \"8 9 * 9 - 9 - 9 - 4 - 1 +\"\n"

int main(int argc, char **argv)
{
	if (argc != 2)
		return (std::cout << USAGE, 1);

	try {
		RPN obj1(argv[1]);
		std::cout << obj1.getResult() << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}
