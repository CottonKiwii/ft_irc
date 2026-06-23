
#include "irc.hpp"

void handlePing(Client &sender, Command &command) {
	std::cout << "Handling PING" << std::endl;

	// ERR_NEEDMOREPARAMS
	if (command.getArgs().empty()) {
		sender.addToResponse(ERR_NEEDMOREPARAMS(sender.getNick()));
		return ;
	}

	// RPL_PING
	std::string response = RPL_PING
		+ sender.getNick()
		+ " :"
		+ command.getArgs()[1]
		+ "\n";
	sender.addToResponse(response);
}
