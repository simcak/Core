#ifndef USER_HPP
# define USER_HPP

# include "IRC.hpp"

class Channel;

class User
{
	private:
		int						_fd;
		std::string				_ip;

		std::string				_realName;
		std::string				_username;
		std::string				_nickname;

		bool					_passAccepted;
		bool					_registered;
		bool					_disconnectAfterFlush;

		std::string				_inBuffer;
		std::string				_outBuffer;

		std::vector<Channel*>	_channels;

	public:
		/* ──────────────────────── Con/Des-tructors ──────────────────────── */
		User();
		User(int fd, const struct sockaddr_in &addr);
		~User();

		/* ──────────────────────────── getters ───────────────────────────── */
		int						getFd() const { return _fd; }
		const std::string		&getIP() const { return _ip; }

		const std::string		&getRealName() const { return _realName; }
		const std::string		&getUserName() const { return _username; }
		const std::string		&getNickName() const { return _nickname; }

		bool			passAccepted() const { return _passAccepted; }
		bool			isRegistered() const { return _registered; }
		bool			wantsDisconnect() const { return _disconnectAfterFlush; }

		std::string			&inBuffer() { return _inBuffer; }
		std::string			&outBuffer() { return _outBuffer; }

		const std::vector<Channel*>		&getChannels() const { return _channels; }

		/* ──────────────────────────── setters ───────────────────────────── */
		void			setRealName(const std::string &r) { _realName = r; }
		void			setUserName(const std::string &u) { _username = u; }
		void			setNickName(const std::string &n) { _nickname = n; }
		
		void			setPassAccepted(bool v) { _passAccepted = v; }
		void			setRegistered(bool v) { _registered = v; }
		void			setDisconnectAfterFlush(bool v) { _disconnectAfterFlush = v; }

		/* ──────────────────────── member functions ──────────────────────── */
		std::string			prefix() const;
		void				addChannel(Channel *channel);
		void				removeChannel(Channel *channel);
};

#endif
