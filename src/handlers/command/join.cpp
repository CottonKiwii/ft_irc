#include "irc.hpp"
#include <queue>

static void	handleJoinCreate(Client &creator, std::string name) {
	if (!Channel::verifyName(name)) {
		creator.addToResponse(ERR_BADCHANMASK(creator, name));
		return ;
	}
	Channel	&channel = Server::createChannel(creator, name);
	std::string response =	":"
							+ creator.getPrefix()
							+ " JOIN "
							+ name
							+ "\n";
	creator.addToResponse(response);
	response =	":localhost MODE "
				+ channel.getName()
				+ " +nt\n";
	creator.addToResponse(response);
	creator.addToResponse(RPL_NAMERPLY(creator, channel));
	creator.addToResponse(RPL_ENDOFNAMES(creator, channel));
}

static bool	runChecksJoinExisting(
	Client &sender,
	Channel *channel,
	std::string name,
	std::string key) {
	if (!Channel::verifyName(name)) {
		sender.addToResponse(ERR_BADCHANMASK(sender, name));
		return false;
	}
	if (!channel) {
		sender.addToResponse(ERR_NOSUCHCHANNEL(name));
		return false;
	}
	if (!channel->getKey().empty() && key != channel->getKey()) {
		sender.addToResponse(ERR_BADCHANNELKEY(sender, (*channel)));
		return false;
	}
	if (channel->isFull()) {
		sender.addToResponse(ERR_CHANNELISFULL(sender, (*channel)));
		return false;
	}
	if (channel->getInviteOnly() && !channel->isClientInvited(sender.getFd())) {
		sender.addToResponse(ERR_INVITEONLYCHAN(sender, (*channel)));
		return false;
	}
	return true;
}

static void	handleJoinExisting(Client &sender, std::string name, std::string key) {
	Channel	*channel = Server::getChannel(name);
	if (runChecksJoinExisting(sender, channel, name, key) == false)
		return ;

	if (channel->isClientInvited(sender.getFd()))
		channel->removeInvited(sender.getFd());

	channel->addMember(sender.getFd());

	std::string response =	":"
							+ sender.getPrefix()
							+ " JOIN "
							+ name
							+ "\n";
	channel->sendAll(response);
	if (!channel->getTopic().empty())
		sender.addToResponse(RPL_TOPIC(sender, (*channel)));
	sender.addToResponse(RPL_NAMERPLY(sender, (*channel)));
	sender.addToResponse(RPL_ENDOFNAMES(sender, (*channel)));
}

static bool	runChecksJoin(Client &sender, Command &command) {
	if (sender.getRegisterStatus() == false) {
		sender.setIsConnected(false);
		sender.addToResponse(ERROR_CLOSINGLINK("unauthorised"));
		return false ;
	}

	if (command.getArgs().size() < 2) {
		sender.addToResponse(ERR_NEEDMOREPARAMS(sender));
		return false ;
	}
	return true ;
}

void	handleJoin(Client &sender, Command &command) {
	if (runChecksJoin(sender, command) == false)
		return ;
	std::queue<std::string>	channels;
	std::queue<std::string>	keys;

	std::istringstream	namesSplit(command.getArgs()[1]);
	std::string			curName;
	while (std::getline(namesSplit, curName, ','))
		channels.push(curName);

	if (command.getArgs().size() > 2) {
		std::istringstream	keysSplit(command.getArgs()[2]);
		std::string			curKey;
		while (std::getline(keysSplit, curKey, ','))
			keys.push(curKey);
	}

	while (channels.size()) {
		std::string curChanName = channels.front();
		std::string	curKeyName = "";
		if (keys.size()) {
			curKeyName = keys.front();
			keys.pop();
		}
		channels.pop();
		Channel *curChan = Server::getChannel(curChanName);
		if (!curChan)
			handleJoinCreate(sender, curChanName);
		else
			handleJoinExisting(sender, curChanName, curKeyName);
	}
}
