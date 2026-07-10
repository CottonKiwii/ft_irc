#include "irc.hpp"

std::string	Client::getIp() const { return _ip; }
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
	return (_buff.find('\n') != std::string::npos);
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
	logResponse();
	_response += "\r\n";
	if (send(_fd, _response.c_str(), _response.size(), 0) == -1)
		throw std::runtime_error("Error: An error occured while sending a message!");
	_response.clear();
}

void	Client::logCommand(Command &command) {
	std::cout 
	<< "["
	<< (_nick.empty() ? "" : _nick)
	<< (_nick.empty() ? "" : " (")
	<< _fd
	<< (_nick.empty() ? "" : ")")
	<< ": in] ";
	for (size_t i = 0; i < command.getArgs().size(); i++)
		std::cout << " " << command.getArgs()[i];
	std::cout << std::endl;
}

void	Client::logResponse() {
	std::stringstream logPrefixStream;
	logPrefixStream
	<< "["
	<< (_nick.empty() ? "" : _nick)
	<< (_nick.empty() ? "" : " (")
	<< _fd
	<< (_nick.empty() ? "" : ")")
	<< ": out] ";
	std::string logPrefix = logPrefixStream.str();
	std::istringstream responseSplit(_response);
	std::string responseLine;
	while (std::getline(responseSplit, responseLine, '\n'))
		std::cout << logPrefix << responseLine << std::endl;
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
