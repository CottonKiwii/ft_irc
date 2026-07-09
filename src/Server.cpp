#include "irc.hpp"

short					Server::Config::_port = 0;
std::string				Server::Config::_pass;
std::vector<pollfd>		Server::_sockets;
std::vector<Client>		Server::_clients;
std::vector<Channel>	Server::_channels;
bool					Server::_signalReceived = false;

Server::Server() {}
Server::~Server() {}

void Server::init(char *args[3]) {
	std::istringstream	portToken(args[1]);

	if (!(portToken >> Server::Config::_port)) {
		throw (std::runtime_error(PORT_MSG));
}
	Server::Config::_pass = args[2];
};

void	Server::createServerSocket(void) {
	pollfd		res;
	sockaddr_in	addr;

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(Server::Config::_port);

	res.fd = socket(AF_INET, SOCK_STREAM, 0);
	if (res.fd == -1)
		throw std::runtime_error("Socket creation failed");

	int optval = 1;
	if (setsockopt(res.fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
		throw (close(res.fd), std::runtime_error("Setting of socket options failed"));
	if (bind(res.fd, (sockaddr *)&addr, sizeof(addr)) == -1)
		throw (close(res.fd), std::runtime_error("Socket binding failed"));
	if (listen(res.fd, SOMAXCONN) == -1)
		throw (close(res.fd), std::runtime_error("Listen initialization failed"));

	res.events = POLLIN;
	res.revents = 0;

	Server::_sockets.push_back(res);
}

void	Server::acceptNewClient(void) {
	sockaddr_in	newAddr;
	socklen_t	newAddrSize;
	pollfd		newSocket;

	newSocket.fd = accept(
		Server::_sockets[0].fd,
		(sockaddr *)&newAddr,
		&newAddrSize
	);

	if (newSocket.fd == -1)
		std::cout << "Couldn't accept new connection" << std::endl;

	newSocket.events = POLLIN;
	newSocket.revents = 0;
	Server::_sockets.push_back(newSocket);
	Client newClient(newSocket.fd, inet_ntoa(newAddr.sin_addr));
	Server::_clients.push_back(newClient);
	std::cout << "Accepted new client from " << newClient.getIp() << std::endl;
}

void	Server::disconnectClient(int fd) {
	size_t	socketIdx = 0;
	Client	*client = Server::getClientByFd(fd);
	client->flushResponse();
	
	for (; Server::_sockets[socketIdx].fd != fd; socketIdx++) {}
	
	close(Server::_sockets[socketIdx].fd);
	Server::_sockets.erase(Server::_sockets.begin() + socketIdx);
	Server::_clients.erase(Server::_clients.begin() + socketIdx - 1);
	std::cout << "Client disconnected" << std::endl;
}

void	Server::disconnectClient(int fd, std::string reason) {
	size_t	socketIdx = 0;
	std::string	response = "ERROR :Closing Link: localhost (" + reason + ")\n" ;
	Client	*client = Server::getClientByFd(fd);
	client->addToResponse(response);
	client->flushResponse();
	
	for (; Server::_sockets[socketIdx].fd != fd; socketIdx++) {}
	
	close(Server::_sockets[socketIdx].fd);
	Server::_sockets.erase(Server::_sockets.begin() + socketIdx);
	Server::_clients.erase(Server::_clients.begin() + socketIdx - 1);
	std::cout << "Client disconnected" << std::endl;
}

void	Server::handleNewData(int fd) {
	char buff[4096];

	memset(buff, 0, sizeof(buff));

	ssize_t bytesReceived = recv(fd, buff, sizeof(buff) - 1, 0);

	// TODO: clean up client on disconnect
	if (bytesReceived < 1) {
		Server::disconnectClient(fd);
		return ;
	}
	std::cout << "["<< fd << ": in]" << buff << std::endl;
	std::istringstream	commands(buff);
	std::string			rawCommand;
	while (std::getline(commands, rawCommand, '\n')) {
		while (rawCommand[rawCommand.size() - 1] == '\r'
			|| rawCommand[rawCommand.size() - 1] == '\n')
			rawCommand.erase(rawCommand.end() - 1);
		if (rawCommand.size() == 0)
			continue ;

		Command command(rawCommand);
		getClientByFd(fd)->handleCommand(command);
	}
	for (
		std::vector<Client>::iterator client = Server::_clients.begin();
		client != Server::_clients.end();
		client++)
		client->flushResponse();
}

void	Server::listenAndServe(void) {
	createServerSocket();

	while (Server::_signalReceived == false) {
		if (poll(&Server::_sockets[0], Server::_sockets.size(), -1) == -1)
			throw std::runtime_error("Poll failed");

		for (size_t i = 0; i < Server::_sockets.size(); i++) {
			if (Server::_sockets[i].revents & POLLIN) {
				if (i == 0)
					acceptNewClient();
				else
					handleNewData(Server::_sockets[i].fd);
			}
		}
	}
}

std::string	Server::getPass() { return Server::Config::_pass; }

Channel	&Server::createChannel(Client &creator, std::string name) {
	_channels.push_back(Channel(creator, name));
	return (_channels.back());
}

Channel	*Server::getChannelByName(std::string name) {
	size_t	res = 0;
	for (; res < Server::_channels.size(); res++) {
		if (Server::_channels[res].getName() == name) {
			return (&Server::_channels[res]);
		}
	}
	return (NULL);
}

Client	*Server::getClientByFd(int fd) {
	size_t	res = 0;
	for (; res < Server::_clients.size(); res++)
		if (Server::_clients[res].getFd() == fd) 
			return (&Server::_clients[res]);
	
	return (NULL);
}

Client *Server::getClientByNick(std::string nickname)
{
	for (size_t res = 0; res < Server::_clients.size(); res++)
		if (Server::_clients[res].getNick() == nickname) 
			return (&Server::_clients[res]);
	return (NULL);
}
