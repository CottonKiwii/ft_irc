#include "irc.hpp"
#include <queue>

void	handleJoinCreate(Client &creator, std::string name, std::string key) {
	if (!Channel::verifyName(name)) {
		creator.addToResponse(ERR_BADCHANMASK(creator, name));
		return ;
	}
	Channel	&channel = Server::createChannel(creator, name);
	if (!key.empty())
		channel.setKey(key);
	std::string response =	":"
							+ creator.getPrefix()
							+ " JOIN "
							+ name;
	creator.addToResponse(response);
	response =	":localhost MODE "
				+ channel.getName()
				+ " +nt\n";
	creator.addToResponse(response);
	creator.addToResponse(RPL_NAMERPLY(creator, channel));
	creator.addToResponse(RPL_ENDOFNAMES(creator, channel));
}

void	handleJoin(Client &sender, Command &command) {
	std::string				response;
	std::queue<std::string>	channels;
	std::queue<std::string>	keys;

	if (sender.getRegisterStatus() == false) {
		Server::disconnectClient(sender.getFd(), "Unauthorized");
		return ;
	}

	if (command.getArgs().size() < 2) {
		sender.addToResponse(ERR_NEEDMOREPARAMS(sender.getNick()));
		return ;
	}

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
		Channel *curChan = Server::getChannelByName(curChanName);
		if (!curChan)
			handleJoinCreate(sender, curChanName, curKeyName);
	}
}
