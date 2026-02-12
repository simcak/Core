#ifndef SERVER_HPP
# define SERVER_HPP

# include "IRC.hpp"
# include "Message.hpp"

class User;
class Channel;

static const size_t	MAX_OUTBUF = 64 * 1024; // 64KB
static const size_t	MAX_INBUF  = 64 * 1024; // 64KB

class Server
{
	private:
		const int							_port;
		std::string							_password;
		std::string							_creationTime;
		std::string							_serverName;

		int									_serverSocket;
		struct sockaddr_in					_serverAddr;

		bool								_serverRunning;
		bool								_shuttingDown;

		std::map<int, User*>				_users;
		std::vector<Channel*>				_channels;

		typedef void (Server::*CommandHandler)(User*, const Message&);
		std::map<std::string, CommandHandler> _commandMap;

	private:
		bool		setupSocket();
		void		setNonBlocking(int fd);

		void		runLoopOnce();
		void		buildPollFds(std::vector<struct pollfd> &pfds) const;
		void		handlePollEvents(const std::vector<struct pollfd> &pfds, size_t userStartIndex);

		void		acceptNewUser();
		void		onReadable(User *user);
		void		onWritable(User *user);

		void		queueLine(User *user, const std::string &line);
		void		sendNumeric(User *user, const std::string &code,
							 const std::string &middle, const std::string &trailing);

		void		tryRegister(User *user);

		void		beginShutdown();
		void		beginUserDisconnect(User *user, const std::string &reason);
		void		removeUserNow(int fd, const std::string &reason);

		User*		findUserByNick(const std::string &nick);
		Channel*	findChannelByName(const std::string &name);
		Channel*	getOrCreateChannel(const std::string &name);
		void		deleteChannelIfEmpty(Channel *ch);

		void		detachFromAllChannels(User *user, const std::string &reason);
		void		broadcastToChannel(Channel *ch, const std::string &line, User *exclude);

		void		initCommandMap();
		void		dispatch(User *user, const Message &msg);

		/* ───────────────────────── mode handling ────────────────────────── */
		bool		modePreprocess(User *user, const Message &msg, Channel *ch, const std::string &chanName);
		
		struct ModeCtx;
		
		typedef bool (*ModeFn)(Server*, User*, const Message&, ModeCtx&);
		
		struct ModeDispatch {
			char	mode;
			ModeFn	fn;
		};
		
		static ModeFn	getModeHandler(char c);

		static bool		mode_i(Server*, User*, const Message&, ModeCtx&);
		static bool		mode_t(Server*, User*, const Message&, ModeCtx&);
		static bool		mode_k(Server*, User*, const Message&, ModeCtx&);
		static bool		mode_o(Server*, User*, const Message&, ModeCtx&);
		static bool		mode_l(Server*, User*, const Message&, ModeCtx&);

		/* ──────────────────────────── commands ──────────────────────────── */
		void		cmdPass(User *user, const Message &msg);
		void		cmdNick(User *user, const Message &msg);
		void		cmdUser(User *user, const Message &msg);
		void		cmdQuit(User *user, const Message &msg);
		void		cmdJoin(User *user, const Message &msg);
		void		cmdPrivMsg(User *user, const Message &msg);
		void		cmdKick(User *user, const Message &msg);
		void		cmdInvite(User *user, const Message &msg);
		void		cmdTopic(User *user, const Message &msg);
		void		cmdMode(User *user, const Message &msg);
		void		cmdPart(User *user, const Message &msg);
		void		cmdNames(User *user, const Message &msg);
		void		cmdWho(User *user, const Message &msg);
		void		cmdList(User *user, const Message &msg);
//		void		cmdPing(User *user, const Message &msg);
		void		cmdPong(User *user, const Message &msg);

	public:
		Server(int port, const std::string &password);
		~Server();

		bool		start();
		void		run();
};

void	ServerController(const std::string &portStr, const std::string &pass);

#endif
