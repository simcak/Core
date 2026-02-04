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

		// modes/state
		std::vector<User*>	_invitedUsers;
		std::string			_key;
		bool				_inviteOnly;
		bool				_topicProtected;
		int					_userLimit;

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

		// invite list
		bool						isInvited(User *user) const;
		void						addInvited(User *user);
		void						removeInvited(User *user);

		// modes
		const std::string			&getKey() const;
		void						setKey(const std::string &key);

		bool						inviteOnly() const;
		void						setInviteOnly(bool v);

		bool						topicProtected() const;
		void						setTopicProtected(bool v);

		int							userLimit() const;
		void						setUserLimit(int limit);

		std::string					modeString() const;

		void						removeAllReferences(User *user);

		bool						empty() const;
};

#endif
