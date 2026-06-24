#include "irc.hpp"
#include "modeHandlers.hpp"

void	modeUserUnknown(Client &sender) {
	sender.addToResponse(ERR_UMODEUNKNOWNFLAG(sender));
}
