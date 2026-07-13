#include "irc.hpp"

void handlePass(Client &sender, Command &command) {
	if (sender.getRegisterStatus()) {
		sender.addToResponse(ERR_ALREADYREGISTERED(sender));
		return ;
	}

	if (command.getArgs().size() < 2) {
		sender.addToResponse(ERR_NEEDMOREPARAMS(sender));
		return ;
	}

	if (command.getArgs()[1] != Server::getPass()) {
		sender.setPassGiven(false);
		sender.addToResponse(ERR_PASSWDMISMATCH(sender));
		return ;
	}
	sender.setPassGiven(true);
}
