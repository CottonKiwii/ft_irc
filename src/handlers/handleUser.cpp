#include "Client.hpp"
#include "Command.hpp"
#include <sys/socket.h>
#include <iostream>

void handleUser(Client &sender, Command &command) {
	std::cout << "Handling USER" << std::endl;
	sender.setName(command.getArgs()[1]);
	std::string response = ":localhost 001 "
		+ sender.getNick()
		+ " :Welcome to Internet Relay Network "
		+ sender.getNick()
		+ "!"
		+ sender.getName()
		+ "@localhost\n";
	send(sender.getFd(), response.c_str(), response.size(), 0);
}
