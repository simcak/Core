#include "./Message.hpp"

/* ──────────────────────────── helper functions ──────────────────────────── */
static void	skipSpaces(const std::string &s, size_t &i)
{
	while (i < s.size() && s[i] == ' ')
		++i;
}

static std::string	toUpper(const std::string &str)
{
	std::string	result = str;

	for (size_t i = 0; i < result.size(); ++i)
		result[i] = static_cast<char>(std::toupper(static_cast<unsigned char>(result[i])));
	return result;
}

static void	handleCommand(const std::string &line, size_t &i, Message &out)
{
	size_t	start = i;

	while (i < line.size() && line[i] != ' ')
		++i;
	out.command = line.substr(start, i - start);
}

static void	handleParms(const std::string &line, size_t &i, Message &out)
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

		size_t	start = i;

		while (i < line.size() && line[i] != ' ')
			++i;
		out.params.push_back(line.substr(start, i - start));
	}
}

/* ────────────────────────────── parseIrcLine ────────────────────────────── */
bool	parseIrcLine(const std::string &line, Message &out)
{
	out.prefix.clear();
	out.command.clear();
	out.params.clear();

	size_t	i = 0;

	skipSpaces(line, i);
	if (i >= line.size())
		return false;

	// Optional prefix
	if (line[i] == ':')
	{
		++i;
		size_t	start = i;

		while (i < line.size() && line[i] != ' ')
			++i;
		out.prefix = line.substr(start, i - start);
		skipSpaces(line, i);
		if (i >= line.size())
			return false;
	}

	// Command
	handleCommand(line, i, out);

	// Params
	handleParms(line, i, out);

	// normalize command
	out.command = toUpper(out.command);

	return !out.command.empty();
}
