
#include "irc.hpp"

void handlePong(Client &sender, Command &command) {
	std::cout << "Handling PONG" << std::endl;

	if (command.getArgs().empty()) {

		// ERR_NEEDMOREPARAMS
		std::string response = ERR_NEEDMOREPARAMS
			+ sender.getNick()
			+ " :Not enough parameters\n";

		sender.sendMsg(response);
		return ;
	}

	// PONG
	std::string message = RPL_PING
		+ sender.getNick()
		+ " :"
		+ command.getArgs()[0]
		+ "\n";

	sender.sendMsg(message);
}
