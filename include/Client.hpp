#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "Command.hpp"
# include <string>

// TODO; make orthodox canonical (can shove unused into private)
class Client {
	private:
		int			_fd;
		std::string	_ip;
		std::string	_nick;
		std::string	_name;
		bool		_capabilitiesResolved;

	public:
		Client(int fd, std::string ip);
		~Client();

		std::string getIp() const;
		int			getFd() const;
		bool		getCapabilitiesResolved() const;
		std::string	getNick() const;
		std::string	getName() const;
		
		void		setCapabilitiesResolved(bool status);
		void		setNick(std::string nick);
		void		setName(std::string name);

		void		handleCommand(Command &command);
		void		sendMsg(std::string response);
};

#endif
