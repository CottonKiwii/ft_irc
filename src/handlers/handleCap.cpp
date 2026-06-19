
#include "irc.hpp"

void	handleCap(Client &sender, Command &command) {
	std::cout << "Ignoring CAP" << std::endl;
	(void)sender;
	(void)command;
}
