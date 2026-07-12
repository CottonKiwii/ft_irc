#include "irc.hpp"

/* only difference to privmsg is that automatic replies
are not allowed to be sent in response to a notice */
static std::vector<std::string>	getTargets(std::string str)
{
	std::vector<std::string>	targets;
	int							start = 0, idx = 0;

	for (size_t i = 0; i < str.size(); i++) {
		if (str[i] == ',') {
			targets.insert(targets.begin() + idx, str.substr(start, i));
			start = i + 1;
			idx++;
		}
	}
	targets.insert(targets.begin() + idx, str.substr(start, str.size()));

	return (targets);
}

void handleNotice(Client &sender, Command &command) {
	std::vector<std::string>	targets;

	if (sender.getRegisterStatus() == false) {
		sender.setIsConnected(false);
		sender.addToResponse(ERROR_CLOSINGLINK("unauthorised"));
		return ;
	}
	// ERR_NOTEXTTOSEND
	if (command.getArgs().size() < 3) {
		sender.addToResponse(ERR_NOTEXTTOSEND(sender));
		return ;
	}

	targets = getTargets(command.getArgs()[1]);
	for (size_t i = 0; i < targets.size(); i++) {

		// FINDING RECEIVER
		Channel	*channel = Server::getChannel(targets[i]);
		if (!channel)
			channel = 
				Server::getChannel(targets[i].substr(1, targets[i].size() - 1));
		Client	*receiver = Server::getClient(targets[i]);

		// ERR_NOSUCHNICK
		if (!channel && !receiver) {
			sender.addToResponse(ERR_NOSUCHNICK(sender, command.getArgs()[1]));
			continue ;
		}

		// CLIENT TO CHANNEL MESSAGE
		if (channel)
			handleClientToChannel(sender, *channel, command);

		// CLIENT TO CLIENT MESSAGE
		if (receiver)
			handleClientToClient(sender, *receiver, command);
	}
}
