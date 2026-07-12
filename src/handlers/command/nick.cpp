#include "irc.hpp"

void handleNick(Client &sender, Command &command) {
	// ERR_NONICKNAMEGIVEN
	if (command.getArgs().empty() || command.getArgs()[1].size() < 1) {
		sender.addToResponse(ERR_NONICKNAMEGIVEN(sender));
		return ;
	}

	// ERR_NICKNAMEINUSE
	if (sender.getRegisterStatus()) {
		Client	*compare = Server::getClient(command.getArgs()[1]);
		if (compare) {
			sender.addToResponse(ERR_NICKNAMEINUSE(sender, command.getArgs()[1]));
			return ;
		}
	}

	// ERR_ERRONEUSNICKNAME
	for (size_t i = 0; i < command.getArgs()[1].size() - 1; i++) {
		if (!std::isprint(command.getArgs()[1][i])) {
			sender.addToResponse(ERR_ERRONEUSNICKNAME(sender, command.getArgs()[1]));
			return ;
		}
	}

	if (command.getArgs()[1][0] == '#'
		|| command.getArgs()[1][0] == ':'
		|| command.getArgs()[1][0] == ' ') {
		sender.addToResponse(ERR_ERRONEUSNICKNAME(sender, command.getArgs()[1]));
		return ;
	}

	// RPL_NEWNICKNAME
	if (sender.getRegisterStatus()) {
		std::string response =	":"
								+ sender.getPrefix()
								+ " NICK "
								+ command.getArgs()[1]
								+ "\n";
		sender.addToResponse(response);
	}

	sender.setNick(command.getArgs()[1]);
}
