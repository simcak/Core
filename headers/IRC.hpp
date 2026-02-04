#ifndef IRC_H
# define IRC_H

# include <netinet/in.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <arpa/inet.h>
# include <fcntl.h>
# include <poll.h>
# include <unistd.h>

# include <csignal>
# include <cerrno>
# include <cstring>
# include <ctime>
# include <cctype>

# include <map>
# include <string>
# include <vector>
# include <sstream>
# include <algorithm>
# include <cstdlib>
# include <iostream>
# include <iomanip>

# include "NumReply.hpp"

/* Colors */
# define BR		"\033[1;31m"
# define BG		"\033[1;32m"
# define BB		"\033[1;34m"
# define BY		"\033[1;33m"
# define BM		"\033[1;35m"
# define RST	"\033[0m"

/* Logs */
# define WARN(msg)  (std::cerr << BY "[WARN] "  RST << msg << std::endl)
# define INFO(msg)  (std::cout << BB "[INFO] "  RST << msg << std::endl)
# define ERROR(msg) (std::cerr << BR "[ERROR] " RST << msg << std::endl)

#ifndef DEBUG
# define DEBUG 1
#endif

# define DEBG(msg) do { \
	if (DEBUG) { std::cerr << BY "[DEBG] " RST << msg << std::endl; } \
} while (0)

/* Defaults */
# define SERVER_NAME	"irc.42.fr"
# define BUFF_SIZE		4096

/* Utils */
bool		onlyDigits(const std::string &str);
std::string	getCurrentDateTime(void);
bool		isPortInUse(int port);

#endif
