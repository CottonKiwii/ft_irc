
#include "irc.hpp"

void handlePong(Client &sender, Command &command) {
	std::string response;

	std::cout << "Handling PONG" << std::endl;

	// ERR_NEEDMOREPARAMS
	if (command.getArgs().empty()) {
		response = ERR_NEEDMOREPARAMS(sender.getNick());
		sender.sendMsg(response);
		return ;
	}

	// RPL_PONG
	response = RPL_PING
		+ sender.getNick()
		+ " :"
		+ command.getArgs()[1]
		+ "\n";
	sender.sendMsg(response);
}
