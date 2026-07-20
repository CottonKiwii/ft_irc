#include "irc.hpp"

static bool	runChecksInvite(Client &sender, Command &command) {
	if (sender.getRegisterStatus() == false) {
		sender.setIsConnected(false);
		sender.addToResponse(ERROR_CLOSINGLINK("unauthorised"));
		return false;
	}
	if (command.getArgs().size() < 3) {
		sender.addToResponse(ERR_NEEDMOREPARAMS(sender));
		return false;
	}
	Channel	*chan = Server::getChannel(command.getArgs()[2]);
	if (!chan) {
		sender.addToResponse(ERR_NOSUCHCHANNEL(command.getArgs()[2]));
		return false;
	}
	if (chan->isClientMember(sender.getFd()) == false) {
		sender.addToResponse(ERR_NOTONCHANNEL((*chan)));
		return false;
	}
	if (chan->getInviteOnly() && chan->isClientOp(sender.getFd()) == false) {
		sender.addToResponse(ERR_CHANOPRIVSNEEDED(sender, (*chan)));
		return false;
	}
	Client	*invitedClient = Server::getClient(command.getArgs()[1]);
	if (!invitedClient) {
		sender.addToResponse(ERR_NOSUCHNICK(sender, command.getArgs()[1]));
		return false;
	}
	if (chan->isClientMember(invitedClient->getFd())) {
		sender.addToResponse(ERR_USERONCHANNEL((*invitedClient), (*chan)));
		return false;
	}
	return true;
}

void	handleInvite(Client &sender, Command &command) {
	if (!runChecksInvite(sender, command))
		return ;
	Client	*invited = Server::getClient(command.getArgs()[1]);
	Channel	*chan = Server::getChannel(command.getArgs()[2]);

	chan->addInvited(invited->getFd());

	sender.addToResponse(RPL_INVITING(sender, (*invited), (*chan)));
	std::string	response = ":";
	response += sender.getPrefix();
	response += " INVITE ";
	response += invited->getNick();
	response += " ";
	response += chan->getName();
	invited->addToResponse(response);
}
