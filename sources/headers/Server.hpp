#ifndef SERVER_HPP
# define SERVER_HPP

#include "IRC.hpp"

class User;		// Forward declaration
class Channel;	// Forward declaration

class Server
{

	private:
		const int					_port;
		std::string					_password;
		std::string					_creation_time;
		std::string					_server_name;
		int							_server_socket;			//stores the server socket fd
		struct sockaddr_in			_server_address;
		bool						_server_running;		//flag for running the server
		std::vector<struct pollfd>	_poll_fds;		//List of pollfd structures — one per socket (server + clients). Used by the poll() system call to monitor socket activity
		std::vector<User *>			_users;				// container that stores info about all the connected clients (FD, nickname, IP, etc.)(So if 5 users are connected, _users.size() will be 5.) 
		std::vector<Channel *>		_channels; 
		socklen_t					_user_address_length;	//It tells accept() how large the client_addr structure is and gets updated to the actual size used. So you’ll use it when a client connects — it’s necessary for retrieving their address.
		//CommandHandler			_handler; 		// CHANGE NAME of this, comes from other class
	
	//borrar luego sino funcionan
 	typedef void (Server::*CommandHandler)(User*, const std::vector<std::string>&);	// This defines a pointer to a member function of the Server class. A CommandHandler is a pointer to a function inside Server, which takes (User*, const std::vector<std::string>&) and returns void.
	
	std::map<std::string, CommandHandler> _commandMap; //  Map of command names -> member function pointers It’s a std::map (an associative container) that links a command string (like "NICK", "USER", "PING", etc.) to the function inside your Server class that should handle it.
	void	Cmd_Nick(User *user, const std::vector<std::string> &tokens);
	void	Cmd_User(User *user, const std::vector<std::string> &tokens);
	void	Cmd_Pass(User *user, const std::vector<std::string> &tokens);
	//void	Cmd_Ping(User *user, const std::vector<std::string> &tokens);
	void	Cmd_Pong(User *user, const std::vector<std::string> &tokens);
	void	Cmd_Quit(User *user, const std::vector<std::string> &tokens);
	void	Cmd_Join(User *user, const std::vector<std::string> &tokens);
	//void	Cmd_PrivMsg(User *user, const std::vector<std::string> &tokens);
 	void	sendToUser(User *user, const std::string &msg);

	public:

		Server(int port, std::string const &password);
		~Server(void);

		Channel *	findChanelByName(const std::string &name);	
		Channel *	addChannel(Channel *chan);
		void		SetServer(void);
		void		BindServer(void);
		void		ListenServer(void);
		void		BuildPollVector(void);
		void		RunServer(void);
		void		StopServer(void);
		void		AcceptNewUser(void);
		void		RemoveUser(User *user);
		void		HandleClientMessage(User *user);
		void		SetNonBlocking(int fd);
		void		InitCommandMap();
 		void		ParseCommand(User *user, const std::vector<std::string> &tokens);
		bool		isNickInUse(const std::string &nick);

		void		debugPrintCommands() const;


		/*
		// Ejemplo de exception
		class Port: public std::exception {
			const char * what() const throw() {
				return "Error: ATTACH ERROR MESSAGE FROM PORT ERROR";
			}
		};
		*/

		// Command handlers (ni idea para que es esto, creo que para QUIT/EXIT)
		//void		cmdQuit(User *user, const std::string &message);
		//void		cmdPass(User *user, const std::string &password);
		//void		cmdNick(User *user, const std::string &nickname);
};

void	ServerController(std::string const &port_str, std::string const &pass);


#endif
