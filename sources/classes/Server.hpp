#ifndef SERVER_HPP
# define SERVER_HPP

#include "IRC.hpp"
#include "Message.hpp"

class User;
class Channel;

class Server
{

	private:
		const int					_port;
		std::string					_password;
		std::string					_creationTime;
		std::string					_serverName;

		int							_serverSocket;
		struct sockaddr_in			_serverAddr;
		bool						_serverRunning;

		// fd -> User*  (no index coupling bugs)
		std::map<int, User*>		_users;
		std::vector<Channel *>		_channels;

		// command map
		typedef void (Server::*CommandHandler)(User*, const Message&);
		std::map<std::string, CommandHandler> _commandMap;

		/* ─────────────────────── Internal helpers ───────────────────────── */
		void	SetNonBlocking(int fd);
		void	InitCommandMap();

		void	AcceptNewUser();
		void	RemoveUser(int fd);

		void	OnReadable(User *user);
		void	OnWritable(User *user);

		void	QueueToUser(User *user, const std::string &msg);
		void	Dispatch(User *user, const Message &msg);

		/* ──────────────────────── Channels helpers ──────────────────────── */
		Channel	*findChannelByName(const std::string &name);
		Channel	*getOrCreateChannel(const std::string &name);

		/* ───────────────────────── Commands ─────────────────────────────── */
		void	CmdNick(User *user, const Message &msg);
		void	CmdUser(User *user, const Message &msg);
		void	CmdPass(User *user, const Message &msg);
		void	CmdPong(User *user, const Message &msg);
		void	CmdQuit(User *user, const Message &msg);
		void	CmdJoin(User *user, const Message &msg);


	public:
		/* ───────────────────────── Con/Des-tructor ──────────────────────── */
		Server(int port, const std::string &password);
		~Server();

		/* ──────────────────────── Member functions ──────────────────────── */
		void	SetServer();
		void	BindServer();
		void	ListenServer();
		void	RunServer();
		void	StopServer() { _serverRunning = false; }

};

/* ──────────────────────────── Global functions ──────────────────────────── */
void	ServerController(std::string const &portStr, std::string const &pass);

#endif
