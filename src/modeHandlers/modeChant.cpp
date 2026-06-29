#include "modeHandlers.hpp"

bool	modeChant(Channel &channel, char mod) {
	if (mod == '+')
		channel.setProtectedTopic(true);
	if (mod == '-')
		channel.setProtectedTopic(false);
	return (false);
}
