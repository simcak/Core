#include "../headers/Message.hpp"

/////////////////////////////// helper functions ///////////////////////////////
static void	skipSpaces(const std::string &s, size_t &i)
{
	while (i < s.size() && s[i] == ' ')
		++i;
}

static std::string	toUpper(const std::string &str)
{
	std::string r = str;
	for (size_t i = 0; i < r.size(); ++i)
		r[i] = static_cast<char>(std::toupper(static_cast<unsigned char>(r[i])));
	return r;
}

static void	parseCommand(const std::string &line, size_t &i, Message &out)
{
	size_t start = i;
	while (i < line.size() && line[i] != ' ')
		++i;
	out.command = line.substr(start, i - start);
}

static void	parseParams(const std::string &line, size_t &i, Message &out)
{
	while (i < line.size())
	{
		skipSpaces(line, i);
		if (i >= line.size())
			break;

		if (line[i] == ':')
		{
			++i;
			out.params.push_back(line.substr(i));
			break;
		}

		size_t start = i;
		while (i < line.size() && line[i] != ' ')
			++i;
		out.params.push_back(line.substr(start, i - start));
	}
}

/*******************************************************************************
 * @brief Parses a raw IRC line into a Message structure.
 * 
 * FORMAT:
 * Input: ":prefix COMMAND param1 param2 :trailing param with spaces"
 * Output:
 *   Message.prefix = "prefix"
 *   Message.command = "COMMAND"
 *   Message.params = ["param1", "param2", "trailing param with spaces"]
 * 
 * EXAMPLES:
 * PRIVMSG #42 :Hello there!
 *   <- prefix="", command="PRIVMSG", params=["#42", "Hello there!"]
 * :nick!user@host JOIN #channel     // TODO
 *   <- prefix="nick!user@host", command="JOIN", params=["#channel"]
 */
bool	parseIrcLine(const std::string &line, Message &out)
{
	out.prefix.clear();
	out.command.clear();
	out.params.clear();

	size_t i = 0;
	skipSpaces(line, i);
	if (i >= line.size())
		return false;

	if (line[i] == ':')
	{
		++i;
		size_t start = i;
		while (i < line.size() && line[i] != ' ')
			++i;

		out.prefix = line.substr(start, i - start);
		skipSpaces(line, i);
		if (i >= line.size())
			return false;
	}

	parseCommand(line, i, out);
	parseParams(line, i, out);

	out.command = toUpper(out.command);
	return !out.command.empty();
}
