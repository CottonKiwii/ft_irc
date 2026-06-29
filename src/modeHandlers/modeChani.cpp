#include "modeHandlers.hpp"

bool	modeChani(Channel &channel, char mod) {
	if (mod == '+')
		channel.setInviteOnly(true);
	if (mod == '-')
		channel.setInviteOnly(false);
	return (true);
}
