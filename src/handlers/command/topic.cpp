#include "irc.hpp"

static void sendResponse(Client &sender, Channel &channel)
{
	std::string response;

	response = CMD_TOPIC(sender.getPrefix())
		+ channel.getName() + " :"
		+ channel.getTopic();
	channel.sendAll(response);
}

static bool	runChecksTopic(Client &sender, Command &command) {
	Channel	*channel;
	if (sender.getRegisterStatus() == false) {
		sender.setIsConnected(false);
		sender.addToResponse(ERROR_CLOSINGLINK("unauthorised"));
		return false;
	}
	if (command.getArgs().size() < 2) {
		sender.addToResponse(ERR_NEEDMOREPARAMS(sender));
		return false;
	}
	channel = Server::getChannel(command.getArgs()[1]);
	//ERR_NOSUCHCHANNEL
	if (!channel) {
		sender.addToResponse(ERR_NOSUCHCHANNEL(command.getArgs()[1]));
		return false;
	}
	// ERR_NOTONCHANNEL
	if (!channel->isClientMember(sender.getFd())) {
		sender.addToResponse(ERR_NOTONCHANNEL((*channel)));
		return false;
	}
	return true;
}

void handleTopic(Client &sender, Command &command) {
	if (runChecksTopic(sender, command) == false)
		return ;
	Channel	*channel = Server::getChannel(command.getArgs()[1]);

	// RPL_TOPIC
	if (command.getArgs().size() == 2) {
		if (channel->getTopic().empty())
			sender.addToResponse(RPL_NOTOPIC(sender, (*channel)));
		else
			sender.addToResponse(RPL_TOPIC(sender, (*channel)));
		return ;	
	}

	// ERR_CHANOPRIVSNEEDED
	if (channel->isClientOp(sender.getFd()) == false && channel->hasMode('t')) {
		sender.addToResponse(ERR_CHANOPRIVSNEEDED(sender, (*channel)));
		return ;
	}

	// RESET TOPIC
	if ((command.getArgs().size() == 3) && (command.getArgs()[2] == ":")) {
		channel->setTopic("");
		sendResponse(sender, (*channel));
		return ;
	}

	// SET TOPIC
	std::string topic;
	for (size_t i = 2; i < command.getArgs().size(); i++) {
		topic += " " + command.getArgs()[i];
		if (i == 2)
			topic.erase(topic.begin(), topic.begin() + 2);
	}
	channel->setTopic(topic);
	sendResponse(sender, (*channel));
}
