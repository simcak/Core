#include "./headers/IRC.hpp"
#include "./headers/Server.hpp"

static bool	isValidPortString(const std::string &s)
{
	if (!onlyDigits(s))
		return false;

	long p = std::atol(s.c_str());
	return (p >= 1 && p <= 65535);
}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		WARN("Usage: " << argv[0] << " <port> <password>");
		return 1;
	}
	if (!isValidPortString(argv[1]))
	{
		ERROR("Port must be numeric in range 1..65535");
		return 1;
	}

	ServerController(argv[1], argv[2]);
	return 0;
}
