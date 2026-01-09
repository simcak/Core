#include "PmergeMe.hpp"

#define ARGS_ERR	BRERR "We need a positive integer sequence as an argument"

static std::string	argsToStr(char **args)
{
	int			i = 0;
	std::string	output = "", tmpArg = "", err = "";

	while (args[++i])
	{
		tmpArg = args[i];
		if (tmpArg.find_first_not_of("0123456789 ") != std::string::npos)
			err += tmpArg + ", ";
		output += tmpArg + " ";
	}
	if (err != "")
		throw std::invalid_argument(BRERR "invalid argument(s): " + err);

	return (output);
}


int	main(int argc, char **argv)
{
	if (argc == 1)
		return (std::cerr << ARGS_ERR << std::endl, 1);

	try
	{
		PmergeMe	seqObj(argsToStr(argv));
		seqObj.sort();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}
