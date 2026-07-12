#include "irc.hpp"

std::string	Server::getPass() { return Server::Config::_pass; }

Client	*Server::getClient(int fd) {
	for (size_t res = 0; res < Server::_clients.size(); res++)
		if (Server::_clients[res].getFd() == fd) 
			return (&Server::_clients[res]);
	return (NULL);
}

Client *Server::getClient(std::string nickname)
{
	for (size_t res = 0; res < Server::_clients.size(); res++)
		if (Server::_clients[res].getNick() == nickname) 
			return (&Server::_clients[res]);
	return (NULL);
}

void	Server::disconnectClient(int fd) {
	size_t	socketIdx = 0;
	Client	*client = Server::getClient(fd);
	client->logDisconnect();
	
	for (; Server::_sockets[socketIdx].fd != fd; socketIdx++) {}
	
	close(Server::_sockets[socketIdx].fd);
	Server::_sockets.erase(Server::_sockets.begin() + socketIdx);
	Server::_clients.erase(Server::_clients.begin() + socketIdx - 1);
}

Channel	&Server::createChannel(Client &creator, std::string name) {
	_channels.push_back(Channel(creator, name));
	return (_channels.back());
}

Channel	*Server::getChannel(std::string name) {
	for (size_t res = 0; res < Server::_channels.size(); res++)
		if (Server::_channels[res].getName() == name)
			return (&Server::_channels[res]);
	return (NULL);
}
