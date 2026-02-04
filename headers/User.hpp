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
		User();
		User(int fd, const struct sockaddr_in &addr);
		~User();

		int							getFd() const;
		const std::string			&getIP() const;

		const std::string			&getRealName() const;
		const std::string			&getUserName() const;
		const std::string			&getNickName() const;

		std::string					prefix() const;

		bool						passAccepted() const;
		bool						isRegistered() const;
		bool						wantsDisconnect() const;

		void						setRealName(const std::string &real);
		void						setUserName(const std::string &user);
		void						setNickName(const std::string &nick);

		void						setPassAccepted(bool v);
		void						setRegistered(bool v);
		void						setDisconnectAfterFlush(bool v);

		std::string					&inBuffer();
		std::string					&outBuffer();

		void						addChannel(Channel *channel);
		void						removeChannel(Channel *channel);
		const std::vector<Channel*>	&getChannels() const;
};

#endif
