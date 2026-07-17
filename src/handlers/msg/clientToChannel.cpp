#include "irc.hpp"

void handleClientToChannel(Client &sender, Channel &receiver, Command &command)
{
	// ERR_CANNOTSENDTOCHAN
	if (!receiver.isClientMember(sender.getFd())) {
		sender.addToResponse(ERR_CANNOTSENDTOCHAN(receiver));
		return ;
	}

	std::string response = ":";
	response += sender.getPrefix();
	response += " ";
	response += command.getArgs()[0];
	response += " ";
	response += receiver.getName();
	response += " ";
	for (size_t i = 2; i < command.getArgs().size(); i++) {
		response += command.getArgs()[i];
		response += " ";
	}
	response.erase(response.begin() + response.size() - 1);
	response += "\n";
	receiver.sendAll(response, sender.getFd());
}
