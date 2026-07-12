#include "irc.hpp"
#include <queue>
#include "modeHandlers.hpp"

static std::string buildResponse(Client &sender,
								 Channel &channel,
								 std::string add,
								 std::string remove,
								 std::vector<std::string> opsToAdd,
								 std::vector<std::string> opsToRemove) {
	std::string	res;
	std::stringstream responseStream;
	responseStream << ":";
	responseStream << sender.getPrefix();
	responseStream << " MODE ";
	responseStream << channel.getName();
	responseStream << " ";
	if (!remove.empty())
		remove.insert(remove.begin(), '-');
	responseStream << remove;
	if (!add.empty())
		add.insert(add.begin(), '+');
	responseStream << add;
	for (size_t i = 0; i < opsToRemove.size(); i++ ) {
		responseStream << " ";
		responseStream << opsToRemove[i];
	}
	for (size_t i = 1; i < add.size(); i++) {
		switch (add[i]) {
			case 'i': break;
			case 't': break;
			case 'k':
				responseStream << " ";
				responseStream << channel.getKey();
				break;
			case 'o':
				responseStream << " ";
				responseStream << opsToAdd.front();
				opsToAdd.erase(opsToAdd.begin());
				break;
			case 'l':
				responseStream << " ";
				responseStream << channel.getMemberLimit();
				break;
		}
	}
	responseStream << "\n";
	res = responseStream.str();
	return (res);
}

static void	handleModeChannel(Client &sender, Command &command) {
	Channel	*channel = Server::getChannel(command.getArgs()[1]);
	if (!channel) {
		sender.addToResponse(ERR_NOSUCHCHANNEL(command.getArgs()[1]));
		return ;
	}
	if (command.getArgs().size() == 2) {
		sender.addToResponse(RPL_CHANNELMODEIS(sender, (*channel)));
		sender.addToResponse(RPL_CREATIONTIME(sender, (*channel)));
		return ;
	}
	if (channel->isClientOp(sender.getFd()) == false) {
		sender.addToResponse(ERR_CHANOPRIVSNEEDED(sender, (*channel)));
		return ;
	}

	std::string				modestring = command.getArgs()[2];
	std::queue<std::string>	modeArgs;
	for (size_t i = 3; i < command.getArgs().size(); i++)
		modeArgs.push(command.getArgs()[i]);

	std::string					add;
	std::string					remove;
	std::vector<std::string>	opsToAdd;
	std::vector<std::string>	opsToRemove;
	char	mod = 0;
	for (size_t i = 0; i < modestring.size(); i++) {
		bool	outcome = false;
		switch (modestring[i]) {
			case '-': mod = '-'; break ;
			case '+': mod = '+'; break ;
			case 'i': outcome = modeChani(*channel, mod); break ;
			case 't': outcome = modeChant(*channel, mod); break ;
			case 'k': outcome = modeChank(*channel, sender, modeArgs, mod); break ;
			case 'o': outcome = modeChano(*channel, sender, modeArgs, mod); break ;
			case 'l': outcome = modeChanl(*channel, sender, modeArgs, mod); break ;
			default: modeChanUnknown(sender, modestring[i]);
		}
		if (outcome) {
			if (mod == '+') {
				add.push_back(modestring[i]);
				if (modestring[i] == 'o') {
					std::string	nick = modeArgs.front();
					opsToAdd.push_back(nick);
					modeArgs.pop();
				}
			}
			if (mod == '-') {
				remove.push_back(modestring[i]);
				if (modestring[i] == 'o') {
					std::string nick = modeArgs.front();
					opsToRemove.push_back(nick);
					modeArgs.pop();
				}
			}
		}
	}
	if (add.empty() && remove.empty())
		return ;
	std::string response = buildResponse(sender,
									  *channel,
									  add,
									  remove,
									  opsToAdd,
									  opsToRemove);
	channel->sendAll(response);
}

static void	handleModeClient(Client &sender, Command &command) {
	Client *client = Server::getClient(command.getArgs()[1]);
	if (!client) {
		sender.addToResponse(ERR_NOSUCHNICK(sender, command.getArgs()[1]));
		return ;
	}
	if (client->getNick() != sender.getNick()) {
		sender.addToResponse(ERR_USERSDONTMATCH(sender));
		return ;
	}
	if (command.getArgs().size() == 2) {
		sender.addToResponse(RPL_UMODEIS(sender));
		return ;
	}
	
	std::string	modestring = command.getArgs()[2];
	char		mod = 0;
	for (size_t i = 0; i < modestring.size(); i++) {
		switch (modestring[i]) {
			case '-': mod = '-'; break ;
			case '+': mod = '+'; break ;
			case 'i': modeUseri(sender, mod, 'i'); break ;
			default:
				modeUserUnknown(sender);
		}
	}
}

void handleMode(Client &sender, Command &command) {
	if (sender.getRegisterStatus() == false) {
		sender.setIsConnected(false);
		sender.addToResponse(ERROR_CLOSINGLINK("unauthorised"));
		return ;
	}
	if (command.getArgs().size() == 1) {
		sender.addToResponse(RPL_UMODEIS(sender));
		return ;
	}
	
	if (command.getArgs()[1][0] == '#')
		handleModeChannel(sender, command);
	else
		handleModeClient(sender, command);
}
