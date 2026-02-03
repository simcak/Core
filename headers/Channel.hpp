#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "IRC.hpp"

class User;

class Channel
{
	private:
		std::string			_name;
		std::string			_topic;

		std::vector<User*>	_users;
		std::vector<User*>	_banList;
		std::vector<User*>	_operators;

	public:
		Channel(const std::string &name);
		~Channel();

		const std::string			&getName() const;
		const std::string			&getTopic() const;
		void						setTopic(const std::string &topic);

		const std::vector<User*>	&users() const;

		bool						isUserInChannel(User *user) const;
		bool						isUserBanned(User *user) const;
		bool						isOperator(User *user) const;

		void						addUser(User *user);
		void						removeUser(User *user);

		void						addOperator(User *user);
		void						removeOperator(User *user);

		void						banUser(User *user);
		void						unbanUser(User *user);

		void						removeAllReferences(User *user);

		bool						empty() const;
};

#endif
