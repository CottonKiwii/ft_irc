#include "irc.hpp"
#include <cstdlib>

bool	modeChanl(
	Channel &channel,
	Client &sender,
	std::queue<std::string> &modeArgs,
	char mod
) {
	if (mod == '+') {
		if (modeArgs.size() == 0) {
			sender.addToResponse(ERR_NEEDMOREPARAMS(sender));
			return (false);
		}
		size_t	newLimit = std::atoi(modeArgs.front().c_str());
		if (!newLimit) {
			modeArgs.pop();
			return (false);
		}
		channel.setMemberLimit(newLimit);
		modeArgs.pop();
		return (true);
	}
	if (mod == '-') {
		channel.setMemberLimit(0);
		return (true);
	}
	return (false);
}
