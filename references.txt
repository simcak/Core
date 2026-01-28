This file contains references for the project, from internet / githubs and suggestions from chatgpt/claude


references:

https://beej.us/guide/bgnet/html/split/what-is-a-socket.html
https://medium.com/@mohamedsarda/ft-irc-channels-and-command-management-ff1ff3758a0b

githubs:

https://git.chevro.fr/42-cestoliv/ft_irc/-/tree/main
https://codesandbox.io/p/github/skyheis/42_irc/master
https://github.com/caroldaniel/42sp-cursus-ft_irc



socket: 
	- A socket is an endpoint that enables two processes to communicate with each other, either on the same machine or across a network. 
		It acts as an interface between the application layer and the transport layer of the networking stack. It's a way to speak to other programs using standard Unix file descriptors.
	- It returns the socket descriptor, and you communicate through it using the specialized send() and recv() (man send, man recv) socket calls.
	- Essentially, a socket is a file descriptor.


	--== Analogy of how a socket works (in ServerController.cpp) ==--

		Think of a socket like a phone line:
		socket() → you get a phone
		bind() → assign your phone number (port)
		listen() → tell the network you’re ready to receive calls
		accept() → pick up a call
		send() / recv() → talk
		close() → hang up




telnet:
	- Telnet is an old network protocol and command-line tool that lets you connect to a server over TCP.
	- How it works: You run telnet <host> <port> and it opens a raw TCP connection. Then you can type commands, and the server will respond with whatever it sends back.
	- You can use Telnet to manually connect to your IRC server and test if it accepts connections, responds correctly, and keeps the connection open.

netcat:
	- Netcat is like Telnet but more powerful. It's often called the "Swiss Army knife of networking."
	- How it works: You can use it to open TCP/UDP connections, listen on ports, transfer files, debug servers, etc.
	- it’s great for testing raw input/output with your server without worrying about Telnet’s quirks.

server:
	- 

client:
	- A client is anything connecting to a server that is not another server. Each client is distinguished from other clients by a unique nickname. 
	- In addition to the nickname, all servers must have the following information about all clients: the real name(user name)/address of the host that the client is connecting from, 
		the username of the client on that host, and the server to which the client is connected.
	- The client registers with the IRC server using a username and must set a nickname with the NICK command in order to communicate (or update the old nickname).

channel:
	- A channel is a named group of one or more clients. All clients in the channel will receive all messages addressed to that channel.
	- The channel is created implicitly when the first client joins it, and the channel ceases to exist when the last client leaves it. While the channel exists, 
		any client can reference the channel using the name of the channel.
	- There are several types of channels used in the IRC protocol. But we are using the standard type of channel that is the regular channel which is known to all servers
		 that are connected to the network. The prefix character for this type of channel is (‘#’, 0x23).


		## How Channels Should Work in IRC (ft_irc Project)

		In a real IRC server, channels are central to the protocol. Here's what you need to implement:

		### **Core IRC Channel Features:**

		#### 1. **Channel Creation & Joining (JOIN command)**
		```
		Client: JOIN #general
		Server: :nick!user@host JOIN #general
		```
		- When a user joins a non-existent channel, it's created automatically
		- The first user becomes the channel operator
		- You need to handle:
		- Password-protected channels (+k mode)
		- User limit (+l mode)
		- Invite-only channels (+i mode)

		#### 2. **Channel Modes (MODE command)**

		Your channel needs to support these modes:

		**Channel Modes:**
		- `+i` : Invite-only channel
		- `+t` : Topic settable by operators only
		- `+k <password>` : Set/remove channel password
		- `+o <nick>` : Give/take operator privilege
		- `+l <limit>` : Set/remove user limit

		**Example:**
		```
		MODE #general +l 10       // Set user limit to 10
		MODE #general +k secret   // Set password to "secret"
		MODE #general +o alice    // Make alice an operator


		//////////////////////////
		//  CHANNEL Operators  ///
		//////////////////////////

		// You'll need to implement:
		void addOperator(User *user);
		void removeOperator(User *user);
		bool isOperator(User *user) const;
		```

		Operators can:
		- Kick users (`KICK #channel nick :reason`)
		- Ban users (you're implementing this)
		- Change topic (if +t is set)
		- Change channel modes
		- Invite users to invite-only channels

		#### 4. **Messaging in Channels (PRIVMSG command)**
		```
		Client: PRIVMSG #general :Hello everyone!
		Server sends to all users in #general except sender:
			:nick!user@host PRIVMSG #general :Hello everyone!








poll():
	- poll() is a system call that allows your server to monitor multiple sockets at once — e.g.
	- one listening socket (the server itself)
	- many client sockets (connected users)


functions used (learn about it): erase(), setsockopt(), recv(), begin(), end(), inet_ntop(), accept(), htons(), bind(), fcntl()


recv(): is used to receive data from a socket — typically when working with network communication (TCP or UDP). It’s part of the Berkeley sockets API, originally from C, but it’s fully usable in C++ as well via <sys/socket.h>







_____________________________________________________________________________________________________________________________________________


OBJECTIVE:
 - design the backend (the server), not the frontend (the client)

The main parts of the project:

    Create all the necessary classes and methods for the project
    Create a socket and handle the server signals.
    Use the poll() function to check if an event has occurred.
    If the event is a new client, register it.
    If the event is data from a registered client, handle it.

_____________________________________________________________________________________________________________________________________________







IAs (Don´t rely to much on This)

 CLAUDE APPROACH:

🟢 Understanding the Basics
	IRC Protocol Fundamentals

	Study RFC 1459 (the original IRC specification) and RFC 2812 (updated protocol)
	Understand the client-server architecture of IRC
	Learn about IRC commands (USER, NICK, JOIN, PRIVMSG, QUIT, etc.)
	Understand message formatting and parsing

🟢 Socket Programming in C++

	Master TCP sockets (socket(), bind(), listen(), accept(), recv(), send())
	Learn about non-blocking I/O and the select() or poll() system calls
	Understand socket states and error handling
	Practice with basic client-server communication

🟢 Core Implementation Steps
	1. Server Architecture Design

	Design a multi-client server using select() or poll() for I/O multiplexing
	Plan your class structure (Server, Client, Channel classes)
	Implement proper socket management and connection handling
	Set up signal handling (especially SIGPIPE)

	2. Message Parsing System

	Create a robust IRC message parser
	Handle partial messages and message buffering
	Implement proper command parsing and validation
	Handle different message formats and edge cases

	3. Client Management

	Implement client registration (PASS, NICK, USER commands)
	Handle client authentication and nickname conflicts
	Manage client states (unregistered, registered, etc.)
	Implement proper client disconnection cleanup

	4. Channel System

	Implement channel creation and management
	Handle JOIN, PART, and QUIT for channels
	Implement channel operators and basic modes
	Manage user lists per channel

	5. Core IRC Commands

	PRIVMSG (private messages and channel messages)
	JOIN/PART (channel operations)
	NICK (nickname changes)
	QUIT (client disconnection)
	Basic channel modes and operator commands

🟢 Key Technical Concepts
	Memory Management

	Proper RAII principles in C++
	Avoid memory leaks with dynamic allocations
	Handle exceptions properly

	Error Handling

	Network errors and disconnections
	Malformed messages and protocol violations
	Resource exhaustion scenarios

	Protocol Compliance

	Proper IRC response codes
	Message formatting standards
	Timing and rate limiting considerations

🟢 Testing Strategy
	Basic Testing

	Use netcat or telnet for manual testing
	Test with actual IRC clients (irssi, WeeChat, etc.)
	Create test scripts for automated testing

	Edge Cases

	Connection drops and network issues
	Malformed or oversized messages
	Rapid connects/disconnects
	Resource limits and stress testing

🟢 Common Pitfalls to Avoid

	Not handling partial reads/writes properly
	Memory leaks from improper cleanup
	Race conditions in multi-client scenarios
	Not following IRC protocol specifications exactly
	Inadequate error handling for network operations

🟢 Recommended Learning Resources

	Read the IRC RFCs carefully (especially RFC 1459 and RFC 2812)
	Study existing IRC server implementations for reference
	Practice socket programming with simpler projects first
	Use IRC clients to understand expected behavior

🟢 Development Workflow

	Start with basic socket server accepting connections
	Implement message parsing and basic command handling
	Add client registration and basic messaging
	Implement channels and multi-user communication
	Add IRC-specific features and error handling
	Extensive testing with real IRC clients



	________________________________________________________________________________________-


	CHAT GTP APPROACH:

🔑 1. Understand the Goal

	You’re building an IRC server (Internet Relay Chat).
	It should allow multiple clients (via telnet or an IRC client like Weechat/Irssi/HexChat) to connect.

You’ll implement:

	User management (nicknames, authentication, quit).
	Channels (create/join/leave, topic, kick, invite, ban, etc.).
	Messaging (private messages, channel messages).
	Conforms to the IRC RFCs (mainly RFC 1459, sometimes 2812).

🔑 2. Core Knowledge to Learn Before Coding

You’ll need to learn some network & system programming concepts that aren’t in earlier 42 projects:
	TCP/IP basics
	How sockets work (server <-> client).
	Difference between IP, port, socket.
	Sockets in C++
	socket(), bind(), listen(), accept(), connect().
	send(), recv(), close().
	I/O Multiplexing
	The server must handle many clients at once.

Learn about:
	select() (easiest, usually allowed in ft_irc).
	poll() or epoll() (faster, but maybe not required).
	This lets you wait for events on multiple sockets without blocking.
	Non-blocking I/O
	A single recv() shouldn’t freeze the server if no data comes.
	Set sockets to non-blocking.
	Protocols & Parsing
	IRC messages are text-based.
	You’ll parse commands (like /join #channel, /nick name).
	Learn string parsing, command dispatching, message formatting.

🔑 3. Project Breakdown (Pathway)
Step 1: Minimal Server

Create a server that:
	Opens a socket.
	Binds to a port.
	Listens for clients.
	Accepts connections.
	Receives and echoes back text.
	Test with telnet localhost <port>.

👉 At this point, you understand sockets + select().

Step 2: Multiple Clients
	Use select() to handle multiple clients.
	Keep a list of active connections.
	For each client:
	If there’s data, read it.
	If they disconnect, remove them.
	Now you can chat between clients (basic relay).

👉 You have a chatroom, but not an IRC server yet.

Step 3: IRC Protocol Basics

	Implement the IRC command parsing:
	NICK, USER, PASS → authentication.
	PRIVMSG → send a message.
	QUIT → disconnect.
	Build a Client class that stores:
	Nickname, username, host, authentication status, channels.

👉 You’re now speaking partial IRC.

Step 4: Channels

	Create a Channel class.

Support:
	/join #channel
	/part #channel
	/topic
	/kick

Each channel has:
	A name (#something).
	A list of members.
	Optional operators.
	Broadcast messages to all members.

👉 You now have a multi-channel chat server.

Step 5: Advanced IRC Features
	Add operator commands (/invite, /mode, /ban, etc.).
	Implement numeric replies (RFC says the server must send codes like 001, 353, 433).
	Handle edge cases (nickname already taken, channel doesn’t exist, etc.).
	Step 6: Clean Up & Robustness
	Memory leaks (use valgrind).
	Properly close all sockets on shutdown.
	Respect RFC as much as possible (test with an IRC client like Weechat).
	Good error handling & logs.

🔑 4. What to Look Up / Learn

Here’s your study checklist:

	Beej’s Guide to Network Programming (absolute must-read).
	How select() works with file descriptors.
	How to set sockets to non-blocking.
	IRC RFC 1459 (skim for commands & message format).
	C++: STL containers (map, vector, set) for client/channel storage.
	String parsing (splitting commands, handling CRLF \r\n).





