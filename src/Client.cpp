#include "Client.hpp"
#include "Handlers.hpp"

Client::Client(int fd, std::string ip):
	_fd(fd),
	_ip(ip),
	_capabilitiesResolved(true)
{}
Client::~Client() {}

std::string	Client::getIp() const { return _ip; }
int			Client::getFd() const { return _fd; }
bool		Client::getCapabilitiesResolved() const { return _capabilitiesResolved; }
std::string	Client::getNick() const { return _nick; }
std::string	Client::getName() const { return _name; }

void		Client::setCapabilitiesResolved(bool status) {_capabilitiesResolved = status;}
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
