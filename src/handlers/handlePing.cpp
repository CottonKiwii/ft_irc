
#include "irc.hpp"

void handlePing(Client &sender, Command &command) {
	std::string	response;
	
	std::cout << "Handling PING" << std::endl;

	// ERR_NEEDMOREPARAMS
	if (command.getArgs().empty()) {
		response = ERR_NEEDMOREPARAMS(sender.getNick());
		sender.sendMsg(response);
		return ;
	}

	// RPL_PING
	response = RPL_PING
		+ sender.getNick()
		+ " :"
		+ command.getArgs()[1]
		+ "\r\n";
	sender.sendMsg(response);
}
