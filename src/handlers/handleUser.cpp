#include "irc.hpp"

void handleUser(Client &sender, Command &command) {
	std::cout << "Handling USER" << std::endl;
	
	if (sender.getPassGiven() == false) {
		sender.addToResponse(ERR_PASSWDMISMATCH(sender));
		Server::disconnectClient(sender.getFd(), "Bad Password");
		return ;
	}

	// ERR_ALREADYREGISTERED
	if (sender.getRegisterStatus()) {
		sender.addToResponse(ERR_ALREADYREGISTERED(sender));
		return ;
	}

	// ERR_NEEDMOREPARAMS
	if (command.getArgs().size() < 4
		|| command.getArgs()[1].size() < 1) {
		sender.addToResponse(ERR_NEEDMOREPARAMS(sender));
		return ;
	}

	// RPL_WELCOME
	sender.setName(command.getArgs()[1]);

	std::string response = RPL_WELCOME
		+ sender.getNick()
		+ " :Welcome to the Internet Relay Network, "
		+ sender.getNick()
		+ "! "
		+ sender.getName()
		+ "@localhost\n";

	sender.addToResponse(response);

	sender.setRegisterStatus(true);
}
