/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:53:35 by cberneri          #+#    #+#             */
/*   Updated: 2026/01/20 14:22:41 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef IRC_H
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

# include "numreply.hpp"

# define red   "\033[1;31m"
# define green "\033[1;32m"
# define blue   "\033[1;34m"
# define yellow "\033[1;33m"
# define magenta "\033[1;35m"
# define reset "\033[0m"

# define DEBUG 1 //TODO: remove later - should be enabled by flag

# ifndef DEBUG
#  define DEBUG 0
# endif

# define WARN(msg) (std::cerr << yellow << "[WARN] " << reset << msg << std::endl)
# define INFO(msg) (std::cout << blue << "[INFO] " << reset << msg << std::endl)
// flushing std::cerr is unnecessary but is fine. Kept it there just for clarity
# define ERROR(msg) (std::cerr << red << "[ERROR] " << reset << msg << std::endl)
# define DEBG(msg) do {\
       		if (DEBUG) { \
			std::cerr << magenta << "[DEBG] " << reset \
			<< msg << std::endl;}\
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
