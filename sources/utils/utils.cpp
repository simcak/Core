#include "../classes/IRC.hpp"

bool	OnlyDigits(const std::string &str)
{
	for (size_t i = 0; i < str.length(); ++i)
		if (!isdigit(static_cast<unsigned char>(str[i])))
			return false;

	return !str.empty();
}

std::string	getCurrentDateTime(void)
{
	time_t		rawtime;
	struct tm	timeinfo;

	// Get current time
	time(&rawtime);

	// Copy localtime safely
	#if defined(_WIN32) || defined(_WIN64)
		localtime_s(&timeinfo, &rawtime);
	#else
		struct tm* tmp = localtime(&rawtime);
		if (tmp != NULL)
			timeinfo = *tmp;
	#endif

	// Format: YYYY-MM-DD HH:MM:SS
	std::ostringstream oss;
	oss << (1900 + timeinfo.tm_year) << "-"
		<< std::setw(2) << std::setfill('0') << (timeinfo.tm_mon + 1) << "-"
		<< std::setw(2) << std::setfill('0') << timeinfo.tm_mday << " "
		<< std::setw(2) << std::setfill('0') << timeinfo.tm_hour << ":"
		<< std::setw(2) << std::setfill('0') << timeinfo.tm_min << ":"
		<< std::setw(2) << std::setfill('0') << timeinfo.tm_sec;

	return oss.str();
}


bool	isPortInUse(int port)
{
	int	sock = socket(AF_INET, SOCK_STREAM, 0);
	int	opt = 1;

	if (sock < 0)
		return true;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	struct sockaddr_in	addr;

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);

	if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0)
	{
		close(sock);
		return true; // port is in use
	}

	close(sock);
	return false; // port is free
}
