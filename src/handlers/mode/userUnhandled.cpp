#include "handlers/mode.hpp"

void	modeUserUnhandled(Client &sender) {
	sender.logUnhandledMode();
}
