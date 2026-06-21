
#include "irc.hpp"

void handlePrivmsg(Client &sender, Command &command) {
	std::string response;

	// == handle channel msg ==
	
	// CLIENT TO CLIENT MESSAGE
	Client	*receiver = Server::getClientByNick(command.getArgs()[1]);

	// ERR_NOSUCHNICK
	if (!receiver) {
		response = ERR_NOSUCHNICK(sender.getNick(), command.getArgs()[1]);
		sender.sendMsg(response);
		return ;
	}
	
	response = RPL_PRIVMSG
		+ sender.getNick()
		+ " :"
		+ command.getArgs()[1]
		+ "\r\n";
	receiver->sendMsg(response);
}
