
#include "irc.hpp"

void handleUser(Client &sender, Command &command) {
	std::cout << "Handling USER" << std::endl;

	sender.setName(command.getArgs()[1]);

	// RPL_WELCOME
	std::string response = RPL_WELCOME
		+ sender.getNick()
		+ " :Welcome to the Internet Relay Network, "
		+ sender.getNick()
		+ "! "
		+ sender.getName()
		+ "@localhost\n";

	sender.sendMsg(response);
}
