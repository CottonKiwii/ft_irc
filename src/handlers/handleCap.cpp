#include "Client.hpp"
#include "Command.hpp"
#include <sys/socket.h>
#include <iostream>

void	handleCap(Client &sender, Command &command) {
	(void)command;
	sender.setCapabilitiesResolved(false);
	std::string response = "CAP * LS :";
	
	std::cout << "we are here" << std::endl;
	send(sender.getFd(), response.c_str(), response.size(), 0);

}
