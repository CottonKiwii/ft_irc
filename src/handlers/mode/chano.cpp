#include "irc.hpp"

bool	modeChano(
	Channel &channel,
	Client &sender,
	std::queue<std::string> &modeArgs,
	char mod
) {
	if (mod == '+') {
		if (modeArgs.size() == 0)
			return (false);

		Client		*newOp = Server::getClient(modeArgs.front());
		if (!newOp) {
			sender.addToResponse(ERR_NOSUCHNICK(sender, modeArgs.front()));
			modeArgs.pop();
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
		if (modeArgs.size() == 0)
			return (false);

		Client		*op = Server::getClient(modeArgs.front());
		if (!op) {
			sender.addToResponse(ERR_NOSUCHNICK(sender, modeArgs.front()));
			modeArgs.pop();
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
