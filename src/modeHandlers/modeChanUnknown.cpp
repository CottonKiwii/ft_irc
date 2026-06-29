#include "modeHandlers.hpp"
#include "irc.hpp"

void	modeChanUnknown(Client &sender, char mode) {
	std::string modeStr;
	modeStr += mode;

	sender.addToResponse(ERR_UNKNOWNMODE(sender, modeStr));
}
