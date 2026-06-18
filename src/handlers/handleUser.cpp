#include "Client.hpp"
#include "Command.hpp"
#include <sys/socket.h>

void handleUser(Client &sender, Command &command) {
	sender.setName(command.getArgs()[1]);
	std::string response = ":huh.huh 001 " + sender.getNick() + ":welcome lol";
	send(sender.getFd(), response.c_str(), response.size(), 0);
}
