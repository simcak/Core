/*
things to do/check

- when the signal is triggered, everything has to be deleted/free/cleaned/closed
- FIX signalController when you have to stop the server pression cntrl +c / crash everything has to be stopped smoothly


- how to test the server:
 >> first, run the SIC client:
 ./sic -h localhost -p 6667 -n USERNAME -k PASSWORD

(old one, ignore this) 
./ircserv 6667 password
nc 127.0.0.1 PORT

- how to close a port though a terminal
sudo lsof -i :1212
sudo kill -9 5921 (5921 es el PID)



PROCESS (4 steps)

1) Socket Layer: Accept clients and manage file descriptors ✅
2) Client Communication: Read from and write to clients (Implement message parsing and responses) ✅
3) Command Parsing: Detect IRC commands (NICK, USER, JOIN, etc.) (Parse messages and handle each)
4) Channel & State Logic: Manage channels, users, modes (Implement channel joining, messaging, operator logic, etc.)

*/

#include "sources/headers/IRC.hpp"
#include "sources/headers/User.hpp"
#include "sources/headers/Channel.hpp"
#include "sources/headers/Server.hpp"

int	main(int argc, char **argv){

	User user1;
	Channel channel("ChannelNamePlaceholder");
	channel.addUser(&user1);
	if (channel.isUserInChanel(&user1)) 
		DEBG("New user in channel");
	else 
		DEBG("something is wrong");

	if (argc != 3)
	{ 
		WARN( "Usage: " << argv[0] << " <port> <password>" );
		return (1);
	}
	else if (!OnlyDigits(argv[1]))
	{
		ERROR( "Port must be a number");
		return (1);
	}

	ServerController(argv[1], argv[2]);
 	return (0);
}
