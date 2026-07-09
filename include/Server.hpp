#ifndef SERVER_HPP
# define SERVER_HPP

# include <string>
# include <vector>
# include <poll.h>
#include "Channel.hpp"
#include "Client.hpp"

#define USAGE_MSG	"Usage: ./ircserv <port> <pass>\n"
#define PORT_MSG	"Port should be a number between 0 and 65535"

class Server {
	private:
		Server(const Server &other);
		Server		&operator=(const Server &other);

		class Config {
			public:
				static short			_port;
				static std::string		_pass;
		};

		static	std::vector<pollfd>		_sockets;
		static	std::vector<Client>		_clients;
		static	std::vector<Channel>	_channels;
		static	bool					_signalReceived;


		void			createServerSocket(void);
		void			acceptNewClient(void);
		void			handleNewData(int fd);

	public:
		Server();
		~Server();
	
		void				init(char *argv[3]);
		void				listenAndServe(void);
	
		
		static std::string	getPass();

		static Channel		&createChannel(Client &creator, std::string name);
		static Channel		*getChannelByName(std::string name);

		static Client		*getClientByNick(std::string nickname);
		static Client		*getClientByFd(int fd);
		static void			disconnectClient(int fd);
		static void			disconnectClient(int fd, std::string reason);

		static void			signalHandler(int signal);
};

#endif
