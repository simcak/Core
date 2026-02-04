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

		/* ────────────────────────── modes/state ─────────────────────────── */
		std::vector<User*>	_invitedUsers;
		std::string			_key;
		bool				_inviteOnly;
		bool				_topicLock;
		int					_userLimit;

	public:
		/* ──────────────────────── Con/Des-tructors ──────────────────────── */
		Channel(const std::string &name);
		~Channel();

		/* ──────────────────────────── getters ───────────────────────────── */
		const std::string			&getName() const { return _name; }
		const std::string			&getTopic() const { return _topic; }
		const std::vector<User*>	&getUsers() const { return _users; }
		const std::string			&getKey() const { return _key; }
		bool						getInviteOnly() const { return _inviteOnly; }
		bool						getTopicLock() const { return _topicLock; }
		int							getUserLimit() const { return _userLimit; }

		/* ──────────────────────────── setters ───────────────────────────── */
		void	setTopic(const std::string &t) { _topic = t; }
		void	setKey(const std::string &k) { _key = k; }
		void	setInviteOnly(bool v) { _inviteOnly = v; }
		void	setTopicLock(bool v) { _topicLock = v; }
		void	setUserLimit(int lim) { _userLimit = ((lim < 0) ? 0 : lim); }

		/* ───────────────────────────── users ────────────────────────────── */
		bool			isUserInChannel(User *user) const;
		bool			isUserBanned(User *user) const;
		bool			isOperator(User *user) const;

		void			addUser(User *user);
		void			removeUser(User *user);
		void			banUser(User *user);
		void			unbanUser(User *user);

		void			addOperator(User *user);
		void			removeOperator(User *user);

		/* ────────────────────────── invite list ─────────────────────────── */
		bool			isInvited(User *user) const;
		void			addInvited(User *user);
		void			removeInvited(User *user);

		/* ───────────────────────────── modes ────────────────────────────── */
		std::string		modeString() const;
		void			removeAllReferences(User *user);
		bool			empty() const;
};

#endif
