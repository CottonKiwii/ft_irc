#include "irc.hpp"
#include <queue>
#include "modeHandlers.hpp"

static void	handleModeChannel(Client &sender, Command &command) {
	Channel	*channel = Server::getChannelByName(command.getArgs()[1]);
	if (!channel) {
		sender.addToResponse(ERR_NOSUCHCHANNEL(sender, command.getArgs()[1]));
		return ;
	}
	if (command.getArgs().size() == 2) {
		sender.addToResponse(RPL_CHANNELMODEIS(sender, (*channel)));
		sender.addToResponse(RPL_CREATIONTIME(sender, (*channel)));
		return ;
	}
	if (channel->isClientOp(sender.getFd()) == false) {
		sender.addToResponse(ERR_CHANOPRIVSNEEDED(sender, (*channel)));
		return ;
	}


}

static void	handleModeClient(Client &sender, Command &command) {
	Client *client = Server::getClientByNick(command.getArgs()[1]);
	if (!client) {
		sender.addToResponse(ERR_NOSUCHNICK(sender, command.getArgs()[1]));
		return ;
	}
	if (client->getNick() != sender.getNick()) {
		sender.addToResponse(ERR_USERSDONTMATCH(sender));
		return ;
	}
	if (command.getArgs().size() == 2) {
		sender.addToResponse(RPL_UMODEIS(sender));
		return ;
	}
	
	std::string	modestring = command.getArgs()[2];
	char		mod = 0;
	for (size_t i = 0; i < modestring.size(); i++) {
		switch (modestring[i]) {
			case '-': mod = '-'; break ;
			case '+': mod = '+'; break ;
			case 'i': modeUseri(sender, mod, 'i'); break ;
			default:
				modeUserUnknown(sender);
		}
	}
	(void)mod;
}

void handleMode(Client &sender, Command &command) {
	if (command.getArgs().size() == 1) {
		sender.addToResponse(RPL_UMODEIS(sender));
		return ;
	}
	
	if (command.getArgs()[1][0] == '#')
		handleModeChannel(sender, command);
	else
		handleModeClient(sender, command);
}
