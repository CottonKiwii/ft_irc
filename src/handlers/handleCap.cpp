#include "Client.hpp"
#include "Command.hpp"
#include <sys/socket.h>
#include <iostream>

void	handleCap(Client &sender, Command &command) {
	std::cout << "Ignoring CAP" << std::endl;
	(void)sender;
	(void)command;
}
