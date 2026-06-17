#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <string>

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
};

#endif
