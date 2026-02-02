#include "../classes/IRC.hpp"

/**
 * @brief Check if a string contains only digit characters
 * @param str Input string to check
 * @return true if the string contains only digits, false otherwise
 */
bool	onlyDigits(const std::string &str)
{
	if (str.empty())
		return false;
	for (size_t i = 0; i < str.size(); ++i)
		if (!std::isdigit(static_cast<unsigned char>(str[i])))
			return false;
	return true;
}

/**
 * @brief Get current date and time as a formatted string "YYYY-MM-DD HH:MM:SS"
 * @return Formatted date-time string
 */
std::string	getCurrentDateTime(void)
{
	time_t		rawtime;
	struct tm	timeinfo;

	time(&rawtime);

	struct tm *tmp = localtime(&rawtime);
	if (tmp)
		timeinfo = *tmp;
	else
		std::memset(&timeinfo, 0, sizeof(timeinfo));

	std::ostringstream oss;
	oss << (1900 + timeinfo.tm_year) << "-"
		<< std::setw(2) << std::setfill('0') << (timeinfo.tm_mon + 1) << "-"
		<< std::setw(2) << std::setfill('0') << timeinfo.tm_mday << " "
		<< std::setw(2) << std::setfill('0') << timeinfo.tm_hour << ":"
		<< std::setw(2) << std::setfill('0') << timeinfo.tm_min << ":"
		<< std::setw(2) << std::setfill('0') << timeinfo.tm_sec;

	return oss.str();
}

/**
 * @brief Check if a TCP port is already in use.
 * @param port Port number to check
 * @return true if the port is in use, false otherwise
 */
bool	isPortInUse(int port)
{
	int	sock = socket(AF_INET, SOCK_STREAM, 0), opt = 1;

	if (sock < 0)
		return true;

	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	struct sockaddr_in	addr;

	std::memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);

	if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0)
	{
		close(sock);
		return true;
	}

	close(sock);
	return false;
}
