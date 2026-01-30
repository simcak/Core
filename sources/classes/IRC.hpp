#ifndef IRC_H
# define IRC_H

/* ──────────────────────────────── Includes ──────────────────────────────── */
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

# include <map>
# include <string>
# include <vector>
# include <sstream>
# include <algorithm>
# include <cstdlib>
# include <iostream>
# include <iomanip>

# include "NumReply.hpp"

/* ───────────────────────────────── Colors ───────────────────────────────── */
# define BR		"\033[1;31m"
# define BG		"\033[1;32m"
# define BB		"\033[1;34m"
# define BY		"\033[1;33m"
# define BM		"\033[1;35m"
# define RST	"\033[0m"
# define BRERR	BR "Error: " RST

/* ───────────────────────────────── PrintM ───────────────────────────────── */
# define WARN(msg) (std::cerr << BY "[WARN] " RST << msg << std::endl)
# define INFO(msg) (std::cout << BB "[INFO] " RST << msg << std::endl)
# define ERROR(msg) (std::cerr << BR "[ERROR] " RST << msg << std::endl)
# define DEBG(msg) do {\
	if (DEBUG) { std::cerr << BY "[DEBG] " RST << msg << std::endl; }\
} while (0)

/* ───────────────────────── Con/Des-tructor PrintM ───────────────────────── */
# define CST(msg) (std::cout << BG "[CONSTRUCTOR] " RST << msg << std::endl)
# define DST(msg) (std::cout << BR "[DESTRUCTOR] " RST << msg << std::endl)

/* ──────────────────────────────── Defines ───────────────────────────────── */
# define DEFAULT_PORT	6667
# define SERVER_NAME	"irc.42.fr"
# define BUFF_SIZE		4096

#ifndef DEBUG
# define DEBUG 0
#endif

/* ────────────────────────────── Forward Decls ───────────────────────────── */
class User;
class Server;
class Channel;

/* ───────────────────────────── Util Functions ───────────────────────────── */
bool			onlyDigits(const std::string &str);
std::string		getCurrentDateTime(void);
bool			isPortInUse(int port);

#endif
