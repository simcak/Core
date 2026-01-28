#include "../headers/ft_irc.hpp"
#include "../headers/Server.hpp" 

void	signalController(int signum){
	std::cout << std::endl << red  << "Signal (" << signum << ") interrupt received." << reset << std::endl;
	//globalServer->StopServer(); // stops the loop FIX THIS LATER
}

//antes init_server
void	ServerController(std::string const &port_str, std::string const &pass){

	int port = atoi(port_str.c_str());

	if (isPortInUse(port)) {
		std::cerr << red << "Error: Port " << green << port << red << " is already in use!" << reset << std::endl;
		return;
	}
	
	signal(SIGINT, signalController);
	Server server(port, pass);	
	server.SetServer();	// crates the socket and initialize address for that socket
	server.BindServer();	// bind the socket to the IP and the address
	server.ListenServer();	// listen the socket for upcoming connections
	server.BuildPollVector();	// prepares the array (struct pollfd) before each call to poll()
	server.RunServer();	// Runs the while with the poll

}
