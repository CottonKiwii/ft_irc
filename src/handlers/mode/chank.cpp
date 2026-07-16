#include "irc.hpp"

bool	modeChank(
	Channel &channel,
	Client &sender,
	std::queue<std::string> &modeArgs,
	char mod
) {
	if (mod == '+') {
		if (!channel.getKey().empty()) {
			sender.addToResponse(ERR_KEYSET(channel));
			return (false);
		}
		if (modeArgs.size() == 0)
			return (false);
		std::string newKey = modeArgs.front();
		channel.setKey(newKey);
		modeArgs.pop();
		return (true);
	}
	if (mod == '-') {
		channel.setKey("");
		return (true);
	}
	return (false);
}
