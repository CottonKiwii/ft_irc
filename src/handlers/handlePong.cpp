
#include "irc.hpp"

void handlePong(Client &sender, Command &command) {
	if (sender.getRegisterStatus() == false) {
		Server::disconnectClient(sender.getFd(), "unauthorised");
		return ;
	}
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
