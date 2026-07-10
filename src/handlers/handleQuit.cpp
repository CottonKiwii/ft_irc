
#include "irc.hpp"

void handleQuit(Client &sender, Command &command) {
	std::string response;

	if (sender.getRegisterStatus() == false) {
		sender.setIsConnected(false);
		sender.addToResponse(ERROR_CLOSINGLINK("unauthorised"));
		return ;
	}
	if (command.getArgs().empty()) {
		response = RPL_QUIT
			+ sender.getNick()
			+ " :Client exiting from the network";
	}
	else {
		response = RPL_QUIT
			+ sender.getNick()
			+ " "
			+ command.getArgs()[1];
	}

	response += "\n";
	sender.addToResponse(response);
	Server::disconnectClient(sender.getFd());
}
