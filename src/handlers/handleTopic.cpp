
#include "irc.hpp"

static void sendResponse(Client &sender, Channel &channel)
{
	std::string response;

	response = ":localhost TOPIC :"
		+ sender.getNick() + " "
		+ channel.getName() + " :"
		+ channel.getTopic()
		+ "\n";
	channel.sendAll(response);
}

void handleTopic(Client &sender, Command &command) {
	std::string topic;

	Channel *channel = Server::getChannelByName(command.getArgs()[1]);

	if (sender.getRegisterStatus() == false) {
		Server::disconnectClient(sender.getFd(), "unauthorised");
		return ;
	}
	//ERR_NOSUCHCHANNEL
	if (!channel) {
		sender.addToResponse(ERR_NOSUCHCHANNEL(sender, command.getArgs()[1]));
		return ;
	}

	// ERR_NOTONCHANNEL
	if (!channel->isClientMember(sender.getFd())) {
		sender.addToResponse(ERR_NOTONCHANNEL((*channel)));
		return ;
	}

	// RPL_TOPIC
	if (command.getArgs().size() == 2) {
		if (!channel->getTopic().c_str())
			sender.addToResponse(RPL_NOTOPIC(sender, (*channel)));
		else
			sender.addToResponse(RPL_TOPIC(sender, (*channel)));
		return ;	
	}

	// ERR_CHANOPRIVSNEEDED
	if (!(channel->isClientOp(sender.getFd()) && channel->hasMode('t'))) {
		sender.addToResponse(ERR_CHANOPRIVSNEEDED(sender, (*channel)));
		return ;
	}

	// RESET TOPIC
	if ((command.getArgs().size() == 3) && (command.getArgs()[2] == "")) {
		channel->setTopic(NULL);
		sendResponse(sender, (*channel));
		return ;
	}

	// SET TOPIC
	for (size_t i = 2; i < command.getArgs().size(); i++)
		topic += command.getArgs()[i] + " ";
	topic.erase(topic.size() - 1);
	channel->setTopic(topic);
	sendResponse(sender, (*channel));
}
