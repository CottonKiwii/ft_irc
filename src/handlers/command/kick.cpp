#include "irc.hpp"

void handleKick(Client &sender, Command &command) {
	if (sender.getRegisterStatus() == false) {
		sender.setIsConnected(false);
		sender.addToResponse(ERROR_CLOSINGLINK("unauthorised"));
		return ;
	}
	if (command.getArgs().size() < 3) {
		sender.addToResponse(ERR_NEEDMOREPARAMS(sender));
		return ;
	}
	
	Channel	*channel = Server::getChannel(command.getArgs()[1]);
	if (!channel) {
		sender.addToResponse(ERR_NOSUCHCHANNEL(command.getArgs()[1]));
		return ;
	}
	Client	*reciever = Server::getClient(command.getArgs()[2]);
	if (!reciever || channel->isClientMember(reciever->getFd())) {
		sender.addToResponse(ERR_USERNOTINCHANNEL(command.getArgs()[2], (*channel)));
		return ;
	}
	if (channel->isClientMember(sender.getFd())) {
		sender.addToResponse(ERR_NOTONCHANNEL((*channel)));
		return ;
	}
	if (channel->isClientOp(sender.getFd())) {
		sender.addToResponse(ERR_CHANOPRIVSNEEDED(sender, (*channel)));
		return ;
	}
	std::string response = ":"
		+ sender.getPrefix()
		+ " KICK "
		+ channel->getName()
		+ " "
		+ reciever->getNick();
	if (command.getArgs().size() < 4)
		response += " :User was kicked out from channel";
	else {
		for (size_t i = 3; i < command.getArgs().size(); i++) {
			response += " ";
			response += command.getArgs()[i];
		}
	}
	response += "\n";
	channel->sendAll(response);
	channel->removeMember(reciever->getFd());
}
