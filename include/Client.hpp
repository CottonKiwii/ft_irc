#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <string>
# include "Command.hpp"

// TODO; make orthodox canonical (can shove unused into private)
class Client {
	private:
		int			_fd;
		std::string	_ip;

	public:
		Client(int fd, std::string ip);
		~Client();

		std::string getIp() const;
		int			getFd() const;
		
		void		handleCommand(Command &command);
};

#endif
