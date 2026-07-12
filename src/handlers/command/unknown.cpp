#include "irc.hpp"

void	handleUnknown(Client &sender, Command &command) {
	sender.addToResponse(ERR_UNKNOWNCOMMAND(command.getArgs()[0]));
}
