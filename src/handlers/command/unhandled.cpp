#include "irc.hpp"

void handleUnhandled(Client &sender) {
	sender.logUnhandledCommand();
}
