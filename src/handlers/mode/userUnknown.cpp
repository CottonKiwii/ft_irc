#include "irc.hpp"

void	modeUserUnknown(Client &sender) {
	sender.addToResponse(ERR_UMODEUNKNOWNFLAG(sender));
}
