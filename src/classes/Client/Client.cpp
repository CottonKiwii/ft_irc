#include "irc.hpp"

Client::Client(int fd):
	_fd(fd),
	_nick(""),
	_name(""),
	_buff(""),
	_response(""),
	_commands(),
	_isConnected(true),
	_registered(false),
	_passGiven(false) {}
Client::Client(const Client &other):
	_fd(other._fd),
	_nick(other._nick),
	_name(other._name),
	_buff(other._buff),
	_response(other._response),
	_commands(other._commands),
	_isConnected(other._isConnected),
	_registered(other._registered),
	_passGiven(other._passGiven) {}
Client::~Client() {}

void	Client::createCommands() {
	std::istringstream	commands(_buff);
	std::string			rawCommand;

	_buff.clear();
	while (std::getline(commands, rawCommand)) {
		if (rawCommand[rawCommand.size() - 1] == '\r')
			rawCommand.erase(rawCommand.begin() + rawCommand.size() - 1);
		if (commands.eof()
			&& _buff[_buff.size() - 1] != '\n'
			&& _buff[_buff.size() - 1] != '\r') {
			_buff += rawCommand;
			break ;
		}
		Command newCommand(rawCommand);
		_commands.push(newCommand);
	}
}

void	Client::handleCommands() {
	createCommands();
	while (_commands.size() && _isConnected) {
		Command command = _commands.front();
		handleCommand(command);
		_commands.pop();
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
		case INVITE: handleInvite(*this, command); break ;
		case NOTICE: handleNotice(*this, command); break ;
		case PRIVMSG: handlePrivmsg(*this, command); break ;
		case UNHANDLED: handleUnhandled(*this); break ;
		default: handleUnknown(*this, command); break ;
	}
}
