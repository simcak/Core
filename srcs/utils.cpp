#include "../headers/IRC.hpp"

/**
 * @brief Checks if a string consists only of digit characters.
 * @param str The string to check.
 * @return bool True if the string contains only digits, false otherwise.
 */
bool	onlyDigits(const std::string &str)
{
	if (str.empty())
		return false;

	for (size_t i = 0; i < str.size(); ++i)
	{
		if (!std::isdigit(static_cast<unsigned char>(str[i])))
			return false;
	}
	return true;
}

/**
 * @brief Gets the current date and time as a formatted string.
 * @return std::string The current date and time as "yyy-mm-dd hh:mm:ss".
 */
std::string	getCurrentDateTime(void)
{
	time_t rawtime;
	time(&rawtime);

	struct tm info;
	std::memset(&info, 0, sizeof(info));

	struct tm *tmp = localtime(&rawtime);
	if (tmp)
		info = *tmp;

	std::ostringstream oss;
	oss << (1900 + info.tm_year) << "-"
		<< std::setw(2) << std::setfill('0') << (info.tm_mon + 1) << "-"
		<< std::setw(2) << std::setfill('0') << info.tm_mday << " "
		<< std::setw(2) << std::setfill('0') << info.tm_hour << ":"
		<< std::setw(2) << std::setfill('0') << info.tm_min << ":"
		<< std::setw(2) << std::setfill('0') << info.tm_sec;

	return oss.str();
}

/**
 * @brief Checks if a given port is already in use by attempting to bind to it.
 * @param port The port number to check.
 * @return bool True if the port is in use, false otherwise.
*/
bool	isPortInUse(int port)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
		return true;

	struct sockaddr_in addr;
	std::memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(static_cast<uint16_t>(port));

	int ret = bind(sock, (struct sockaddr*)&addr, sizeof(addr));
	close(sock);

	return (ret < 0);
}
