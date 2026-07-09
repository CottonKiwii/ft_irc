
#include "irc.hpp"

void handleKick(Client &sender, Command &command) {
	if (sender.getRegisterStatus() == false) {
		Server::disconnectClient(sender.getFd(), "unauthorised");
		return ;
	}
	(void)sender;
	(void)command;
}
