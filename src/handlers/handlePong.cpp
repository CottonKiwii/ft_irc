
#include "irc.hpp"

void handlePong(Client &sender, Command &command) {
	std::cout << "Handling PONG" << std::endl;

	// ERR_NEEDMOREPARAMS
	if (command.getArgs().empty()) {
		sender.addToResponse(ERR_NEEDMOREPARAMS(sender));
		return ;
	}

	// RPL_PONG
	std::string response = RPL_PING
		+ sender.getNick()
		+ " :"
		+ command.getArgs()[1]
		+ "\n";
	sender.addToResponse(response);
}
