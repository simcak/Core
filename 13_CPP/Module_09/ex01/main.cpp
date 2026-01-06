#include "RPN.hpp"

#define USAGE	BG "Usage:" RST " ./RPN \"8 9 * 9 - 9 - 9 - 4 - 1 +\"\n"
#define ALLOWED	BRERR "Only numbers, operators, space are accepted.\n"


int main(int argc, char **argv)
{
	std::string	input;

	if (argc != 2)
		return (std::cout << USAGE, 1);

	input = argv[1];
	if (input.find_first_not_of("0123456789+-*/ ") != std::string::npos)
		return (std::cout << ALLOWED, 1);

	try {
		RPN obj1(input);
		std::cout << obj1.getResult() << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}
