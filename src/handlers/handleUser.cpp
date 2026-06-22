
#include "irc.hpp"

void handleUser(Client &sender, Command &command) {
	std::string response;

	std::cout << "Handling USER" << std::endl;
	
	if (sender.getPassGiven() == false) {
		response = ERR_PASSWDMISMATCH(sender.getNick());
		sender.sendMsg(response);
		Server::disconnectClient(sender.getFd(), "Bad Password");
		return ;
	}

	// ERR_ALREADYREGISTERED
	if (sender.getRegisterStatus()) {
		response = ERR_ALREADYREGISTERED(sender.getNick());
		sender.sendMsg(response);
		return ;
	}

	// ERR_NEEDMOREPARAMS
	if (command.getArgs().size() < 4
		|| command.getArgs()[1].size() < 1) {
		response = ERR_NEEDMOREPARAMS(sender.getNick());
		sender.sendMsg(response);
		return ;
	}

	// RPL_WELCOME
	sender.setName(command.getArgs()[1]);

	response = RPL_WELCOME
		+ sender.getNick()
		+ " :Welcome to the Internet Relay Network, "
		+ sender.getNick()
		+ "! "
		+ sender.getName()
		+ "@localhost\r\n";
	sender.sendMsg(response);

	sender.setRegisterStatus(true);
}
