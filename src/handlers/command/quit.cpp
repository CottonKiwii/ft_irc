#include "irc.hpp"

void handleQuit(Client &sender, Command &command) {
	if (sender.getRegisterStatus() == false) {
		sender.setIsConnected(false);
		sender.addToResponse(ERROR_CLOSINGLINK("unauthorised"));
		return ;
	}
	std::string response = CMD_QUIT(sender.getPrefix());

	if (command.getArgs().size() < 2) {
		response += ": Client exiting from the network";
	} else {
		for (size_t i = 1; i < command.getArgs().size(); i++) {
			if (i != 1)
				response += " ";
			response += command.getArgs()[i];
		}
	}

	Server::sendToAllChannels(sender, response);
	sender.setIsConnected(false);
}
