#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>

int main(int argc, char **argv)
{
	if (argc != 3)
		return (std::cerr << "Error: argument format should be ./ircserv <port> <password> !" << std::endl, 1);

	int port = atoi(argv[1]);
	(void)argv;
	int			socketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketFd < 0)
		return (std::cerr << "Couldn't create a socket" << std::endl, 1);

	sockaddr_in	hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	hint.sin_addr.s_addr = INADDR_ANY;
	if (bind(socketFd, (struct sockaddr *)&hint, sizeof(hint)) < 0)
		return (std::cerr << "Couldn't bind a socket" << std::endl, 1);
	
	if (listen(socketFd, SOMAXCONN) < 0)
		return (std::cerr << "Couldn't start listening to connections" << std::endl, 1);
	
	sockaddr_in	client;
	socklen_t	clientSize;
	
	int clientFd = accept(socketFd, (sockaddr *)&client, &clientSize);
	if (clientFd < 0)
		return (std::cerr << "Couldn't accept a client connection" << std::endl, 1);

	close(socketFd);

	char buf[4096];
	while (true) {
		memset(buf, 0, sizeof(buf));
		int bytesRecieved = recv(clientFd, buf, sizeof(buf), 0);
		if (bytesRecieved < 0) {
			std::cerr << "Connection error" << std::endl;
			break ;
		}
		if (bytesRecieved == 0) {
			std::cerr << "Client disconnected" << std::endl;
			break ;
		}
		std::cout << buf << std::endl;
		send(clientFd, buf, bytesRecieved + 1, 0);
	}
	close(clientFd);

}
