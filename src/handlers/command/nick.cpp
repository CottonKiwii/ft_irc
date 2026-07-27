#include "irc.hpp"

static bool	runChecksNick(Client &sender, Command &command) {
	// ERR_NONICKNAMEGIVEN
	if (command.getArgs().size() < 2) {
		sender.addToResponse(ERR_NONICKNAMEGIVEN(sender));
		return false;
	}
	// ERR_NICKNAMEINUSE
	if (sender.getRegisterStatus()) {
		Client	*compare = Server::getClient(command.getArgs()[1]);
		if (compare) {
			sender.addToResponse(ERR_NICKNAMEINUSE(command.getArgs()[1]));
			return false;
		}
	}
	// ERR_ERRONEUSNICKNAME
	if (command.getArgs()[1][0] == '#' || command.getArgs()[1][0] == ':') {
		sender.addToResponse(ERR_ERRONEUSNICKNAME(command.getArgs()[1]));
		return false;
	}
	for (size_t i = 0; i < command.getArgs()[1].size() - 1; i++) {
		if (!std::isprint(command.getArgs()[1][i])) {
			sender.addToResponse(ERR_ERRONEUSNICKNAME(command.getArgs()[1]));
			return false;
		}
	}
	return true;
}

void handleNick(Client &sender, Command &command) {
	if (runChecksNick(sender, command) == false)
		return ;

	// RPL_NEWNICKNAME
	if (sender.getRegisterStatus()) {
		std::string response =	":"
								+ sender.getPrefix()
								+ " NICK "
								+ command.getArgs()[1];
		sender.addToResponse(response);
	}

	sender.setNick(command.getArgs()[1]);
}
