#ifndef USER_HPP
# define USER_HPP

#include "IRC.hpp"

class Channel; // Forward declaration

class User
{

	private:
		int				_port;
		int				_fd;
		std::string		_hostname;
		std::string		_name;
		std::string		_username;
		std::string		_nickname;
		bool			_authenticated;
//		bool			_is_operator;
//		bool			_invited;

// esto es para quit/exit hecho por Claude
		bool					_disconnected;
		std::vector<Channel *>	_channels;

	public:
		User();
		User(int fd, const struct sockaddr_in &addr);
		~User(void);

		int			getFd() const { return _fd; }
		bool		isAuthenticated() const { return _authenticated; }
		void		setAuthenticated(bool val) { _authenticated = val; }

		// getters
		std::string getNickName() const { return _nickname; }
		std::string getUserName() const { return _username; }
		std::string getRealName() const { return _name; }

		// setters
		void setNickName(const std::string &nick) { _nickname = nick; }
		void setUserName(const std::string &user) { _username = user; }
		void setRealName(const std::string &real) { _name = real; }

		//para QUIT/EXIT
		bool isDisconnected() const;
		void setDisconnected(bool value);
		void addChannel(Channel *channel);
		void removeChannel(Channel *channel);
		void setHostname(const std::string &hostname);
		std::vector<Channel *> getChannels() const;
		std::string getHostname() const;


};

#endif