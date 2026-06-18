#include "Client.hpp"
#include "Command.hpp"
#include <iostream>

void handleNick(Client &sender, Command &command) {
	std::cout << "Handling NICK" << std::endl;
	sender.setNick(command.getArgs()[1]);
}
