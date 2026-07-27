#include "irc.hpp"

int			Client::getFd() const { return _fd; }
std::string	Client::getNick() const { return _nick; }
std::string	Client::getName() const { return _name; }
bool		Client::getIsConnected() const { return _isConnected; }
bool		Client::getRegisterStatus() const { return _registered; }
bool		Client::getPassGiven() const { return _passGiven; }
std::string	Client::getPrefix() const {
	return _nick + "!" + _name + "@localhost";
}

void		Client::setNick(std::string nick) { _nick = nick; }
void		Client::setName(std::string name) { _name = name; }
void		Client::setHostname(std::string host) { _name = host; }
void		Client::setIsConnected(bool status) { _isConnected = status; }
void		Client::setRegisterStatus(bool status) { _registered = status; }
void		Client::setPassGiven(bool status) { _passGiven = status; }

bool		Client::commandsReady() {
	if (_buff.find("\n") != std::string::npos
		|| _buff.find("\r\n") != std::string::npos)
		return true;
	return false;
}

void	Client::addToResponse(std::string response) {
	_response.push(response);
}

void	Client::addToBuff(std::string buff) {
	_buff += buff;
}

void	Client::flushResponse() {
	std::string	responseStr;
	if (_response.size() == 0)
		return ;
	while (_response.size()) {
		responseStr += _response.front();
		responseStr += "\r\n";
		logResponse(_response.front());
		_response.pop();
	}
	if (send(_fd, responseStr.c_str(), responseStr.size(), 0) < 0)
		_isConnected = false;
}

void	Client::logConnect() {
	std::cout
	<< "["
	<< _fd
	<< ": connection established]"
	<< std::endl;
}

void	Client::logDisconnect() {
	std::cout
	<< "["
	<< (_nick.empty() ? "" : _nick)
	<< (_nick.empty() ? "" : " (")
	<< _fd
	<< (_nick.empty() ? "" : ")")
	<< ": disconnected] "
	<< std::endl;
}

void	Client::logCommand(Command &command) {
	std::cout 
	<< "["
	<< (_nick.empty() ? "" : _nick)
	<< (_nick.empty() ? "" : " (")
	<< _fd
	<< (_nick.empty() ? "" : ")")
	<< ": in]";
	for (size_t i = 0; i < command.getArgs().size(); i++)
		std::cout << " " << command.getArgs()[i];
	std::cout << std::endl;
}

void	Client::logResponse(std::string response) {
	std::stringstream logStream;
	logStream
	<< "["
	<< (_nick.empty() ? "" : _nick)
	<< (_nick.empty() ? "" : " (")
	<< _fd
	<< (_nick.empty() ? "" : ")")
	<< ": out] "
	<< response;
	std::string log = logStream.str();
	std::cout << log  << std::endl;
}

void	Client::logUnhandledCommand() {
	std::cout 
	<< "["
	<< (_nick.empty() ? "" : _nick)
	<< (_nick.empty() ? "" : " (")
	<< _fd
	<< (_nick.empty() ? "" : ")")
	<< ": server] Command is recognized but unhandled"
	<< std::endl;
}

void	Client::logUnhandledMode() {
	std::cout 
	<< "["
	<< (_nick.empty() ? "" : _nick)
	<< (_nick.empty() ? "" : " (")
	<< _fd
	<< (_nick.empty() ? "" : ")")
	<< ": server] Mode is recognized but unhandled"
	<< std::endl;
}
