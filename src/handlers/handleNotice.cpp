
#include "irc.hpp"

/* only difference to privmsg is that automatic replies
are not allowed to be sent in response to a notice */
void handleNotice(Client &sender, Command &command) {
	std::string response;

	// == handle channel msg ==
	
	// CLIENT TO CLIENT NOTICE
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
