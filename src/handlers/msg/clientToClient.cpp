#include "irc.hpp"

void handleClientToClient(Client &sender, Client &receiver, Command &command)
{
	std::string	response;

	response = ":" + sender.getPrefix() + " PRIVMSG " + receiver.getNick() + " ";
	for (size_t i = 2; i < command.getArgs().size(); i++) {
		response += command.getArgs()[i];
		response += " ";
	}
	response.erase(response.begin() + response.size() - 1);
	response += "\n";
	receiver.addToResponse(response);
}
