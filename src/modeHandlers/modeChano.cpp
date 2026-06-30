#include "modeHandlers.hpp"
#include "irc.hpp"

bool	modeChano(Channel &channel,
						Client &sender,
						std::queue<std::string> modeArgs,
						char mod) {
	if (mod == '+') {
		if (modeArgs.size() == 0) {
			sender.addToResponse(ERR_NEEDMOREPARAMS(sender));
			return (false);
		}
		std::string newOpNick = modeArgs.front();
		Client		*newOp = Server::getClientByNick(newOpNick);
		if (!newOp) {
			modeArgs.pop();
			sender.addToResponse(ERR_NOSUCHNICK(sender, newOpNick));
			return (false);
		}
		if (!channel.isClientMember(newOp->getFd())) {
			modeArgs.pop();
			sender.addToResponse(ERR_NOTONCHANNEL(channel));
			return (false);
		}
		if (newOp->getFd() == sender.getFd())
			return (false);
		channel.addOp(newOp->getFd());
		return (true);
	}
	if (mod == '-') {
		if (modeArgs.size() == 0) {
			sender.addToResponse(ERR_NEEDMOREPARAMS(sender));
			return (false);
		}
		std::string opNick = modeArgs.front();
		Client		*op = Server::getClientByNick(opNick);
		if (!op) {
			modeArgs.pop();
			sender.addToResponse(ERR_NOSUCHNICK(sender, opNick));
			return (false);
		}
		if (!channel.isClientMember(op->getFd())) {
			modeArgs.pop();
			sender.addToResponse(ERR_NOTONCHANNEL(channel));
			return (false);
		}
		channel.removeOp(op->getFd());
		return (true);
	}
	return (false);
}
