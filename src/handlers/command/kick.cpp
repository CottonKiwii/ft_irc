#include "irc.hpp"

static void	kickClient(
	Client &sender,
	Client &toKick,
	Channel &channel,
	std::string reason
) {
	if (channel.isClientMember(toKick.getFd()) == false) {
		sender.addToResponse(ERR_USERNOTINCHANNEL(toKick.getNick(), channel));
		return ;
	}
	std::string response = ":";
	response += sender.getPrefix();
	response += " KICK ";
	response += channel.getName();
	response += " ";
	response += toKick.getNick();
	if (reason != ":") {
		response += " ";
		response += reason;
	}
	response += "\n";
	channel.removeMember(toKick.getFd());
	channel.sendAll(response);
}

static bool	runChecksKick(Client &sender, Command &command) {
	if (sender.getRegisterStatus() == false) {
		sender.setIsConnected(false);
		sender.addToResponse(ERROR_CLOSINGLINK("unauthorised"));
		return false;
	}
	if (command.getArgs().size() < 3) {
		sender.addToResponse(ERR_NEEDMOREPARAMS(sender));
		return false;
	}
	Channel	*chan = Server::getChannel(command.getArgs()[1]);
	if (!chan) {
		sender.addToResponse(ERR_NOSUCHCHANNEL(command.getArgs()[1]));
		return false;
	}
	if (chan->isClientMember(sender.getFd()) == false) {
		sender.addToResponse(ERR_NOTONCHANNEL((*chan)));
		return false;
	}
	if (chan->isClientOp(sender.getFd()) == false) {
		sender.addToResponse(ERR_CHANOPRIVSNEEDED(sender, (*chan)));
		return false;
	}

	return true;
}

void handleKick(Client &sender, Command &command) {
	if (runChecksKick(sender, command) == false)
		return ;
	
	Channel				*channel = Server::getChannel(command.getArgs()[1]);
	std::string			nick;
	std::istringstream	split(command.getArgs()[2]);
	std::string			reason = "";

	if (command.getArgs().size() > 3)
		for (size_t i = 3; i < command.getArgs().size(); i++)
			reason += i == 3 ? (command.getArgs()[i]) : (" " + command.getArgs()[i]);
	while (std::getline(split, nick, ',')) {
		Client	*toKick = Server::getClient(nick);
		if (toKick)
			kickClient(sender, *toKick, *channel, reason);
	}
}
