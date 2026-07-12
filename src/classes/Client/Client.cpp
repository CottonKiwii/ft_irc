#include "irc.hpp"

Client::Client(int fd, std::string ip):
	_fd(fd),
	_ip(ip),
	_isConnected(true),
	_registered(false)
{}
Client::~Client() {}

void		Client::handleCommands() {
	std::istringstream	commands(_buff);
	_buff.clear();
	std::string			rawCommand;
	while (std::getline(commands, rawCommand, '\n') && _isConnected) {
		while (rawCommand[rawCommand.size() - 1] == '\r'
			|| rawCommand[rawCommand.size() - 1] == '\n')
			rawCommand.erase(rawCommand.end() - 1);
		if (rawCommand.size() == 0)
			continue ;
		Command command(rawCommand);
		handleCommand(command);
	}
}

void		Client::handleCommand(Command &command) {
	logCommand(command);
	switch (command.getType()) {
		case PING: handlePing(*this, command); break ;
		case PONG: handlePong(*this, command); break ;
		case NICK: handleNick(*this, command); break ;
		case USER: handleUser(*this, command); break ;
		case PASS: handlePass(*this, command); break ;
		case JOIN: handleJoin(*this, command); break ;
		case PART: handlePart(*this, command); break ;
		case KICK: handleKick(*this, command); break ;
		case QUIT: handleQuit(*this, command); break ;
		case MODE: handleMode(*this, command); break ;
		case TOPIC: handleTopic(*this, command); break ;
		case NOTICE: handleNotice(*this, command); break ;
		case PRIVMSG: handlePrivmsg(*this, command); break ;
		case UNHANDLED: handleUnhandled(*this); break ;
		default: handleUnknown(*this, command); break ;
	}
}
