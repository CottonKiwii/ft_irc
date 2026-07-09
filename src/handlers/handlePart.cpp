
#include "irc.hpp"

void handlePart(Client &sender, Command &command) {
	if (sender.getRegisterStatus() == false) {
		Server::disconnectClient(sender.getFd(), "unauthorised");
		return ;
	}
	(void)sender;
	(void)command;
}
