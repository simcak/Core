#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "IRC.hpp"
class User; // Forward declaration

class Channel
{
    private:
        std::string					_name;
        std::string					_topic;
        std::vector<User *>			_users;
        std::vector<User *>			_banList;
        std::vector<User *>			_operators;
        std::string					_password;
        size_t						_user_limit;

    public:
        Channel(std::string const &name);
        ~Channel();
	
//        std::vector<User *>	getUsers() const;
//        void		removeUser(User *user);
        bool		isUserInChanel(User *user) const;
        bool		isUserBanned(User *user) const;

		Channel&		addUser(User *user);
		Channel&		banUser(User *);
		Channel&		unBanUser(User *);
		Channel&		setUserLimit(size_t limit);
		Channel&		setTopic(const std::string &topic);

		size_t		getUserLimit() const;
		std::string	getUserName() const;
		std::string	getTopic() const;


//        void		addOperator(User *user);
//        void		removeOperator(User *user);
//        bool		isOperator(User *user) const;
//        std::string	getPassword() const;


};

#endif
