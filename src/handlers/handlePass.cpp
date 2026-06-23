#include "irc.hpp"

void handlePass(Client &sender, Command &command) {
	if (sender.getRegisterStatus()) {
		sender.addToResponse(ERR_ALREADYREGISTERED(sender.getNick()));
		return ;
	}

	if (command.getArgs().size() < 2) {
		sender.addToResponse(ERR_NEEDMOREPARAMS(sender.getNick()));
		return ;
	}

	if (command.getArgs()[1] != Server::getPass()) {
		sender.setPassGiven(false);
		return ;
	}
	sender.setPassGiven(true);
}
