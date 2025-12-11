#include "BitcoinExchange.hpp"

void	_print_err(int key, char **argv)
{
	if (key == ERR_ARGS)
		std::cout << BRERR "Correct usage: <program> <data>" << std::endl;
	else if (key == ERR_OPEN)
		std::cout << BRERR "Couldn't open the file '" << argv[1] << "'\n";
	else if (key == ERR_MPTY)
		std::cout << BRERR "No content in the file '" << argv[1] << "'\n";
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return (_print_err(ERR_ARGS, argv), 1);

	std::ifstream inputFile(argv[1]);

	if (!inputFile.is_open())
		return (_print_err(ERR_OPEN, argv), 1);
	if (inputFile.peek() == std::ifstream::traits_type::eof())
		return (_print_err(ERR_MPTY, argv), 1);

	BitcoinExchange history(argv[1]);

	return (inputFile.close(), 0);
}
