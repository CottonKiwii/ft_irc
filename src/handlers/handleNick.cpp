
#include "irc.hpp"

void handleNick(Client &sender, Command &command) {
	std::cout << "Handling NICK" << std::endl;
	sender.setNick(command.getArgs()[1]);
}
