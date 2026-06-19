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
		bool		_registered;

	public:
		Client(int fd, std::string ip);
		~Client();

		int			getFd() const;
		std::string getIp() const;
		std::string	getNick() const;
		std::string	getName() const;
		bool		getRegisterStatus() const;
		
		void		setNick(std::string nick);
		void		setName(std::string name);
		void		setRegisterStatus(bool status);

		void		handleCommand(Command &command);
		void		sendMsg(std::string response);
};

#endif
