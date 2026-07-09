#include "irc.hpp"

Client::Client(int fd, std::string ip):
	_fd(fd),
	_ip(ip),
	_response(""),
	_registered(false),
	_passGiven(false)
{}
Client::~Client() {}

std::string	Client::getIp() const { return _ip; }
int			Client::getFd() const { return _fd; }
bool		Client::getRegisterStatus() const { return _registered; }
bool		Client::getPassGiven() const { return _passGiven; }
std::string	Client::getNick() const { return _nick; }
std::string	Client::getName() const { return _name; }
std::string	Client::getHostname() const { return _hostname; }

void		Client::setRegisterStatus(bool status) {_registered = status;}
void		Client::setPassGiven(bool status) { _passGiven = status; }
void		Client::setNick(std::string nick) { _nick = nick; }
void		Client::setName(std::string name) { _name = name; }
void		Client::setHostname(std::string host) { _name = host; }

bool		Client::commandsReady() {
	return (_buff.find('\n') != std::string::npos);
}

void		Client::handleCommands() {
	inLog();
	std::istringstream	commands(_buff);
	_buff.clear();
	std::string			rawCommand;
	while (std::getline(commands, rawCommand, '\n')) {
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
	switch (command.getType())
	{
		case CAP:
			handleCap(*this, command);	
			break ;
		case PING:
			handlePing(*this, command);	
			break ;
		case PONG:
			handlePong(*this, command);	
			break ;
		case NICK:
			handleNick(*this, command);	
			break ;
		case USER:
			handleUser(*this, command);	
			break ;
		case PASS:
			handlePass(*this, command);	
			break ;
		case JOIN:
			handleJoin(*this, command);	
			break ;
		case PART:
			handlePart(*this, command);	
			break ;
		case KICK:
			handleKick(*this, command);	
			break ;
		case QUIT:
			handleQuit(*this, command);	
			break ;
		case PRIVMSG:
			handlePrivmsg(*this, command);	
			break ;
		case NOTICE:
			handleNotice(*this, command);	
			break ;
		case TOPIC:
			handleTopic(*this, command);	
			break ;
		case MODE:
			handleMode(*this, command);	
			break ;
		default:
			handleUnknown(*this, command);	
			break ;
	}
}

std::string	Client::getPrefix() const {
	return _nick + "!" + _name + "@localhost";
}

void	Client::addToResponse(std::string response) {
	_response += response;
}

void	Client::addToBuff(std::string buff) {
	_buff += buff;
}

void	Client::flushResponse() {
	if (_response.size() == 0)
		return ;
	outLog();
	_response += "\r\n";
	if (send(_fd, _response.c_str(), _response.size(), 0) == -1)
		throw std::runtime_error("Error: An error occured while sending a message!");
	_response.clear();
}

void	Client::inLog() {
	std::cout
	<< "["
	<< (_nick.empty() ? "" : _nick)
	<< (_nick.empty() ? "" : " (")
	<< _fd
	<< (_nick.empty() ? "" : ")")
	<< ": in] "
	<< _buff;
}

void	 Client::outLog() {
	std::cout
	<< "["
	<< (_nick.empty() ? "" : _nick)
	<< (_nick.empty() ? "" : " (")
	<< _fd
	<< (_nick.empty() ? "" : ")")
	<< ": out] "
	<< _response;
}

void	Client::connectLog() {
	std::cout
	<< "["
	<< _fd
	<< ": connection established]"
	<< std::endl;
}

void	Client::disconnectLog() {
	std::cout
	<< "["
	<< (_nick.empty() ? "" : _nick)
	<< (_nick.empty() ? "" : " (")
	<< _fd
	<< (_nick.empty() ? "" : ")")
	<< ": disconnected] "
	<< std::endl;
}
