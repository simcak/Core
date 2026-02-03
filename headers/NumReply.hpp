#ifndef NUMREPLY_HPP
# define NUMREPLY_HPP

namespace irc
{
	namespace rpl
	{
		static const char	*WELCOME			= "001";
		static const char	*YOURHOST			= "002";
		static const char	*CREATED			= "003";
		static const char	*MYINFO				= "004";

		static const char	*NOTOPIC			= "331";
		static const char	*TOPIC				= "332";

		static const char	*NAMREPLY			= "353";
		static const char	*ENDOFNAMES			= "366";
	}

	namespace err
	{
		static const char	*NOSUCHNICK			= "401";
		static const char	*NOSUCHCHANNEL		= "403";
		static const char	*UNKNOWNCOMMAND		= "421";

		static const char	*NONICKNAMEGIVEN	= "431";
		static const char	*ERRONEUSNICKNAME	= "432";
		static const char	*NICKNAMEINUSE		= "433";

		static const char	*NOTREGISTERED		= "451";
		static const char	*NEEDMOREPARAMS		= "461";
		static const char	*ALREADYREGISTRED	= "462";
		static const char	*PASSWDMISMATCH		= "464";

		static const char	*BANNEDFROMCHAN		= "474";
	}
}

#endif
