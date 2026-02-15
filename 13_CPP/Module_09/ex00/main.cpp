#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
		return (std::cout << BRERR "Correct usage: <program> <data>\n", 1);

	try
	{
		BitcoinExchange history(argv[1]);
	}
	catch(const std::exception& e)
	{
		return (std::cerr << e.what() << '\n', 1);
	}

	return 0;
}
