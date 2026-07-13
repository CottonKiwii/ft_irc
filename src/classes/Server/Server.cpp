#include "irc.hpp"
#include <unistd.h>
#include <signal.h>

short					Server::Config::_port = 0;
std::string				Server::Config::_pass;
std::vector<pollfd>		Server::_sockets;
std::vector<Client>		Server::_clients;
std::vector<Channel>	Server::_channels;
bool					Server::_signalReceived = false;

Server::Server() {}
Server::~Server() {
	for (std::vector<pollfd>::iterator it = _sockets.begin();
		it != _sockets.end();
		it++) {
		close(it->fd);
	}
}

void Server::init(char *args[3]) {
	std::istringstream	portToken(args[1]);

	if (!(portToken >> Server::Config::_port))
		throw (std::runtime_error(PORT_MSG));
	signal(SIGINT, Server::signalHandler);
	signal(SIGQUIT, Server::signalHandler);
	Server::Config::_pass = args[2];
};

void	Server::listenAndServe(void) {
	createServerSocket();

	while (Server::_signalReceived == false) {
		if (poll(&Server::_sockets[0], Server::_sockets.size(), -1) == -1
			&& Server::_signalReceived == false)
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
	socklen_t	newAddrSize = sizeof(newAddr);
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
	newClient.logConnect();
}

void	Server::handleNewData(int fd) {
	char	buff[4096];
	Client	*client = getClient(fd);

	memset(buff, 0, sizeof(buff));

	ssize_t bytesReceived = recv(fd, buff, sizeof(buff) - 1, 0);

	if (bytesReceived < 1) {
		Server::disconnectClient(fd);
		return ;
	}
	client->addToBuff(buff);
	if (client->commandsReady())
			getClient(fd)->handleCommands();
	Server::flushClients();
	Server::disconnectClients();
	Server::updateChannels();
}

void	Server::signalHandler(int signal) {
	(void)signal;
	std::cout << "[server: signal recieved]" << std::endl;
	_signalReceived = true;
}
