#include "irc.hpp"

void	modeChanUnhandled(Client &sender) {
	sender.logUnhandledMode();
}
