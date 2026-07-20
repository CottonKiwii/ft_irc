#include "irc.hpp"

void handlePing(Client &sender, Command &command) {
	if (sender.getRegisterStatus() == false) {
		sender.setIsConnected(false);
		sender.addToResponse(ERROR_CLOSINGLINK("unauthorised"));
		return ;
	}
	// ERR_NEEDMOREPARAMS
	if (command.getArgs().size() < 2) {
		sender.addToResponse(ERR_NEEDMOREPARAMS(sender));
		return ;
	}

	// RPL_PING
	std::string response = CMD_PONG
		+ command.getArgs()[1];
	sender.addToResponse(response);
}
