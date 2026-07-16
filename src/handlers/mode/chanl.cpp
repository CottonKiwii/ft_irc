#include "irc.hpp"
#include <cstdlib>

bool	modeChanl(
	Channel &channel,
	std::queue<std::string> &modeArgs,
	char mod
) {
	if (mod == '+') {
		if (modeArgs.size() == 0)
			return (false);

		size_t	newLimit = std::atoi(modeArgs.front().c_str());
		modeArgs.pop();
		if (!newLimit)
			return (false);
		channel.setMemberLimit(newLimit);
		return (true);
	}
	if (mod == '-') {
		channel.setMemberLimit(0);
		return (true);
	}
	return (false);
}
