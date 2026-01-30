#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include "IRC.hpp"

// message structure: [:prefix]         command  [params ...] [:trailing]
// example:           ":nick!user@host  PRIVMSG  #channel      :Hello, world!"
struct Message
{

	std::string					prefix;
	std::string					command;
	std::vector<std::string>	params;

};

bool	parseIrcLine(const std::string &line, Message &out);

#endif
