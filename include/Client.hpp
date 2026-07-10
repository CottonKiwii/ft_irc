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
		std::string _buff;

		std::string	_response;

		bool		_isConnected;
		bool		_registered;
		bool		_passGiven;

	public:
		Client(int fd, std::string ip);
		~Client();

		int			getFd() const;
		std::string getIp() const;
		std::string	getNick() const;
		std::string	getName() const;
		std::string	getHostname() const;
		bool		getIsConnected() const;
		bool		getRegisterStatus() const;
		bool		getPassGiven() const;
		
		void		setNick(std::string nick);
		void		setName(std::string name);
		void		setHostname(std::string host);
		void		setIsConnected(bool status);
		void		setRegisterStatus(bool status);
		void		setPassGiven(bool status);

		bool		commandsReady();
		void		handleCommands();
		void		handleCommand(Command &command);

		std::string	getPrefix() const;

		void		addToResponse(std::string response);
		void		addToBuff(std::string buff);
		void		flushResponse();

		void		connectLog();
		void		disconnectLog();
		void		logCommand(Command &command);
		void		logResponse();
};

#endif
