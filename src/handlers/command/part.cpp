#include "irc.hpp"
#include <sstream>

static void	leaveChannel(Client &sender, Channel &channel, Command &command) {
	std::string	response = ":"
		+ sender.getPrefix()
		+ " PART "
		+ channel.getName();
	if (command.getArgs().size() < 3)
		response += " :Leaving channel";
	else {
		for (size_t i = 2; i < command.getArgs().size(); i++) {
			response += " ";
			response += command.getArgs()[i];
		}
	}
	response += "\n";
	channel.sendAll(response);
	channel.removeMember(sender.getFd());
}

void	handlePart(Client &sender, Command &command) {
	if (sender.getRegisterStatus() == false) {
		sender.setIsConnected(false);
		sender.addToResponse(ERROR_CLOSINGLINK("unauthorised"));
		return ;
	}
	if (command.getArgs().size() < 2) {
		sender.addToResponse(ERR_NEEDMOREPARAMS(sender));
		return ;
	}
	std::istringstream	split(command.getArgs()[1]);
	std::string			chanName;
	while (std::getline(split, chanName, ',')) {
		Channel *channel = Server::getChannel(chanName);
		if (!channel) {
			sender.addToResponse(ERR_NOSUCHCHANNEL(chanName));
			continue ;
		}
		leaveChannel(sender, *channel, command);
	}
}
