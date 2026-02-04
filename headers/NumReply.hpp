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

		static const char	*ENDOFWHO			= "315";
		static const char	*LISTSTART			= "321";
		static const char	*LIST				= "322";
		static const char	*LISTEND			= "323";
		static const char	*CHANNELMODEIS		= "324"; // RPL_CHANNELMODEIS
		static const char	*INVITING			= "341"; // RPL_INVITING

		static const char	*NOTOPIC			= "331";
		static const char	*TOPIC				= "332";

		static const char	*WHOREPLY			= "352";
		static const char	*NAMREPLY			= "353";
		static const char	*ENDOFNAMES			= "366";
	}

	namespace err
	{
		static const char	*NOSUCHNICK			= "401";
		static const char	*NOSUCHCHANNEL		= "403";
		static const char	*CANNOTSENDTOCHAN	= "404";
		static const char	*NORECIPIENT		= "411";
		static const char	*NOTEXTTOSEND		= "412";
		static const char	*UNKNOWNCOMMAND		= "421";

		static const char	*NONICKNAMEGIVEN	= "431";
		static const char	*ERRONEUSNICKNAME	= "432";
		static const char	*NICKNAMEINUSE		= "433";

		static const char	*USERNOTINCHANNEL	= "441";
		static const char	*NOTONCHANNEL		= "442";
		static const char	*USERONCHANNEL		= "443";

		static const char	*NOTREGISTERED		= "451";
		static const char	*NEEDMOREPARAMS		= "461";
		static const char	*ALREADYREGISTRED	= "462";
		static const char	*PASSWDMISMATCH		= "464";

		static const char	*CHANNELISFULL		= "471";
		static const char	*UNKNOWNMODE		= "472";
		static const char	*INVITEONLYCHAN		= "473";
		static const char	*BANNEDFROMCHAN		= "474";
		static const char	*BADCHANNELKEY		= "475";

		static const char	*CHANOPRIVSNEEDED	= "482";
	}
}

#endif
