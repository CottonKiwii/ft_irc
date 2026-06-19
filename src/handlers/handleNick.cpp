#include "irc.hpp"

void handleNick(Client &sender, Command &command) {
	std::string response;

	std::cout << "Handling NICK" << std::endl;

	// ERR_NONICKNAMEGIVEN
	if (command.getArgs().empty() || command.getArgs()[1].size() < 1) {
		response = ERR_NONICKNAMEGIVEN(sender.getNick());
		sender.sendMsg(response);
		return ;
	}

	// ERR_NICKNAMEINUSE
	if (sender.getRegisterStatus()) {
		Client	*compare = Server::getClientByNick(command.getArgs()[1]);
		if (compare) {
			response = ERR_NICKNAMEINUSE(sender.getNick(), command.getArgs()[1]);
			sender.sendMsg(response);
			return ;
		}
	}

	// ERR_ERRONEUSNICKNAME
	for (size_t i = 0; i < command.getArgs()[1].size() - 1; i++) {
		if (!std::isprint(command.getArgs()[1][i])) {
			response = ERR_ERRONEUSNICKNAME(sender.getNick(), command.getArgs()[1]);
			sender.sendMsg(response);
			return ;
		}
	}

	if (command.getArgs()[1][0] == '#'
		|| command.getArgs()[1][0] == ':'
		|| command.getArgs()[1][0] == ' ') {
		response = ERR_ERRONEUSNICKNAME(sender.getNick(), command.getArgs()[1]);
		sender.sendMsg(response);
		return ;
	}

	// RPL_NEWNICKNAME
	if (sender.getRegisterStatus()) {
		response = RPL_NEWNICKNAME
			+ sender.getNick()
			+ " changed his nickname to "
			+ command.getArgs()[1]
			+ "\r\n";
		sender.sendMsg(response);
	}
}
