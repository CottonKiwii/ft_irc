
#include "irc.hpp"

void handleQuit(Client &sender, Command &command) {
	std::string response;

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

	sender.addToResponse(response);
	Server::disconnectClient(sender.getFd());
}
