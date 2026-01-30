#ifndef USER_HPP
# define USER_HPP

#include "IRC.hpp"

class Channel;

class User
{

	private:
		int				_port;
		int				_fd;
		std::string		_ip;
		std::string		_name;
		std::string		_username;
		std::string		_nickname;
		bool			_authenticated;

		// Buffers (required for partial recv/send correctness) :contentReference[oaicite:4]{index=4}
		/* ──────────────────────────── buffers ───────────────────────────── */
		std::string		_inBuffer;
		std::string		_outBuffer;

		/* ─────────────────────── quit/exit helpers ──────────────────────── */
		bool					_disconnected;
		std::vector<Channel *>	_channels;


	public:
		/* ──────────────────────── Con/Des-tructors ──────────────────────── */
		User();
		User(int fd, const struct sockaddr_in &addr);
		~User();

		/* ──────────────────────────── getters ───────────────────────────── */
		int			getFd() const { return _fd; }
		std::string	getIP() const { return _ip; }
		std::string	getRealName() const { return _name; }
		std::string	getUserName() const { return _username; }
		std::string	getNickName() const { return _nickname; }
		bool		isAuthenticated() const { return _authenticated; }

		/* ──────────────────────────── setters ───────────────────────────── */
		void	setIP(const std::string &ip) { _ip = ip; }
		void	setRealName(const std::string &real) { _name = real; }
		void	setUserName(const std::string &user) { _username = user; }
		void	setNickName(const std::string &nick) { _nickname = nick; }
		void	setAuthenticated(bool val) { _authenticated = val; }

		/* ──────────────────────────── buffers ───────────────────────────── */
		std::string	&inBuffer() { return _inBuffer; }
		std::string	&outBuffer() { return _outBuffer; }

		/* ─────────────────────── quit/exit helpers ──────────────────────── */
		bool	isDisconnected() const { return _disconnected; }
		void	setDisconnected(bool value) { _disconnected = value; }


		/* ──────────────────────── ChannelFunctions ──────────────────────── */
		void					addChannel(Channel *channel);
		void					removeChannel(Channel *channel);
		// getter
		std::vector<Channel *>	getChannels() const { return _channels; }

};

#endif
