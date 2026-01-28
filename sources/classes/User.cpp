/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:53:35 by cberneri          #+#    #+#             */
/*   Updated: 2026/01/20 15:10:12 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_irc.hpp"
#include "../headers/User.hpp"
#include "../headers/Channel.hpp"

User::User() :
	_port(11111),
	_fd(-1),
	_hostname("DEFAULT_Hostname"),
	_name("DEFAULT_Name"),
	_username("DEFAULT_User"),
	_nickname("DEFAULT_Nickname"),
	_authenticated(false)	
{
	std::cout << magenta << "User created (default)" << reset << std::endl;
}

User::User(int fd, const struct sockaddr_in &addr)	:
		_port(ntohs(addr.sin_port)),	// convert port from network to host byte order
		_fd(fd),
		_name("Unknown"),
		_username("Unknown"),
		_nickname("Unknown"),
		_authenticated(false)	
{
	char ipStr[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &(addr.sin_addr), ipStr, INET_ADDRSTRLEN);
	_hostname = ipStr;
 
	std::cout << magenta << "User " << _username << " connected from "
			  << _hostname << ":" << _port
			  << " (FD: " << _fd << ")" << reset << std::endl;
}

User::~User(){
	std::cout << yellow << "User destroyed!" << reset << std::endl;
}











//done by CLaude
//para QUIT / EXIT
/*
bool User::isDisconnected() const
{
    return _disconnected;
}

void User::setDisconnected(bool value)
{
    _disconnected = value;
}

std::vector<Channel *> User::getChannels() const
{
    return _channels;
}

void User::addChannel(Channel *channel)
{
    // Check if already in this channel
    for (size_t i = 0; i < _channels.size(); i++)
    {
        if (_channels[i] == channel)
            return;
    }
    _channels.push_back(channel);
}

void User::removeChannel(Channel *channel)
{
    std::vector<Channel *>::iterator it = _channels.begin();
    while (it != _channels.end())
    {
        if (*it == channel)
        {
            _channels.erase(it);
            return;
        }
        ++it;
    }
}

std::string User::getHostname() const
{
    return _hostname;
}

void User::setHostname(const std::string &hostname)
{
    _hostname = hostname;
}


// finish of QUIT / EXIT

*/