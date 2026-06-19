#include "irc.hpp"

void handlePass(Client &sender, Command &command) {
	std::string response;
	if (sender.getRegisterStatus()) {
		response = ERR_ALREADYREGISTERED(sender.getNick());
		sender.sendMsg(response);
		return ;
	}
	if (command.getArgs().size() < 2) {
		response = ERR_NEEDMOREPARAMS(sender.getNick());
		sender.sendMsg(response);
		return ;
	}
	if (command.getArgs()[1] != Server::getPass()) {
		response = ERR_PASSWDMISMATCH(sender.getNick());
		sender.sendMsg(response);
		return ;
	}
	sender.setRegisterStatus(true);
}
