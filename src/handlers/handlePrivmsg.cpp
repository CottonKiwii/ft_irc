
#include "irc.hpp"

void handlePrivmsg(Client &sender, Command &command) {
	std::string response;

	// == handle channel msg ==
	
	// CLIENT TO CLIENT MESSAGE
	Client	*receiver = Server::getClientByNick(command.getArgs()[1]);

	// ERR_NOSUCHNICK
	if (!receiver) {
		sender.addToResponse(ERR_NOSUCHNICK(sender, command.getArgs()[1]));
		return ;
	}
	
	response = ":" + sender.getPrefix() + " ";
	for (size_t i = 2; i < command.getArgs().size(); i++) {
		response += command.getArgs()[i];
		response += " ";
	}
	response.erase(response.begin() + response.size() - 1);
	response += "\n";
	receiver->addToResponse(response);
}
