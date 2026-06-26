
#include "irc.hpp"

void handleClientToChannel(Client &sender, Channel &receiver, Command &command)
{
	std::string	response;

	// ERR_NOTONCHANNEL
	if (!receiver.isClientMember(sender.getFd())) {
		sender.addToResponse(ERR_NOTONCHANNEL(sender, receiver));
		return ;
	}

	// other permission checks?

	response = ":" + sender.getPrefix() + " PRIVMSG " + receiver.getName() + " ";
	for (size_t i = 2; i < command.getArgs().size(); i++) {
		response += command.getArgs()[i];
		response += " ";
	}
	response.erase(response.begin() + response.size() - 1);
	response += "\n";
	receiver.sendAll(response);
}
