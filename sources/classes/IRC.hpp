#ifndef IRC_H
# define IRC_H

# include <netinet/in.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <arpa/inet.h>
# include <fcntl.h>
# include <poll.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <string>
# include <ctime>
# include <map>
# include <sstream>
# include <algorithm>
# include <cstdlib>
# include <csignal>
# include <cctype>
# include <cstring>
# include <iostream>
# include <iomanip>
# include <vector>

# include "NumReply.hpp"

/* ───────────────────────────────── Colors ───────────────────────────────── */
# define BR		"\033[1;31m"
# define BG		"\033[1;32m"
# define BB		"\033[1;34m"
# define BY		"\033[1;33m"
# define BM		"\033[1;35m"
# define RST	"\033[0m"
# define BRERR	BR "Error: " RST

#ifndef DEBUG
# define DEBUG 0
#endif

# define WARN(msg) (std::cerr << BY "[WARN] " RST << msg << std::endl)
# define INFO(msg) (std::cout << BB "[INFO] " RST << msg << std::endl)
// flushing std::cerr is unnecessary but is fine. Kept it there just for clarity
# define ERROR(msg) (std::cerr << BR "[ERROR] " RST << msg << std::endl)
# define DEBG(msg) do {\
	if (DEBUG) { std::cerr << BM "[DEBG] " RST << msg << std::endl;}\
	} while (0)

# define	PORT 6667
# define	SERVER_NAME "irc.42.fr"
# define	BUFF_SIZE 5000

class User;
class Server;
class Channel;

void			signalController(int signum);
bool			OnlyDigits(const std::string &str);
std::string		getCurrentDateTime(void);
bool			isPortInUse(int port);

#endif
