#include "irc.hpp"

bool	modeChanl(
	Channel &channel,
	std::queue<std::string> &modeArgs,
	char mod
) {
	if (mod == '+') {
		if (modeArgs.size() == 0)
			return (false);
		std::istringstream	token(modeArgs.front());
		int			newLimit;

		modeArgs.pop();
		if (!(token >> newLimit))
			return (false);
		if (newLimit < 1)
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
