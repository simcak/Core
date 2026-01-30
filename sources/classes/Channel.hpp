#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "IRC.hpp"

class User;

class Channel
{

	private:
		std::string				_name;
		std::string				_topic;
		std::vector<User *>		_users;
		std::vector<User *>		_banList;
		std::vector<User *>		_operators;
		std::string				_password;


	public:
		/* ───────────────────────── Con/Des-tructor ──────────────────────── */
		Channel(std::string const &name);
		~Channel();

		/* ──────────────────────────── Getters ───────────────────────────── */
		std::string	getUserName() const { return _name; }
		std::string	getTopic() const { return _topic; }

		/* ──────────────────────── Member functions ──────────────────────── */
		bool	isUserInChanel(User *user) const;
		bool	isUserBanned(User *user) const;

		Channel	&addUser(User *user);
		Channel	&removeUser(User *user);

		Channel	&banUser(User *user);
		Channel	&unBanUser(User *user);

		Channel	&setTopic(const std::string &t) { _topic = t; return *this; }

};

#endif
