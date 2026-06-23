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

void		Client::setRegisterStatus(bool status) {_registered = status;}
void		Client::setPassGiven(bool status) { _passGiven = status; }
void		Client::setNick(std::string nick) { _nick = nick; }
void		Client::setName(std::string name) { _name = name; }

void		Client::handleCommand(Command &command)
{
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

void	Client::addToResponse(std::string response)
{
	_response += response;
}

void	Client::flushResponse() {
	if (_response.size() == 0)
		return ;
	_response += "\r\n";
	if (send(_fd, _response.c_str(), _response.size(), 0) == -1)
		throw std::runtime_error("Error: An error occured while sending a message!");
	_response.clear();
}
