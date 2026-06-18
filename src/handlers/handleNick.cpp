#include "Client.hpp"
#include "Command.hpp"

void handleNick(Client &sender, Command &command) {
	sender.setNick(command.getArgs()[1]);
}
