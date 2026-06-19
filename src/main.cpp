
#include "irc.hpp"

int main(int argc, char **argv)
{
	if (argc != 3)
		return (std::cerr << "Error: argument format should be ./ircserv <port> <password> !" << std::endl, 1);

	Server	s;
	int		exitStatus = 0;
	try {
		s.init(argv);
		s.listenAndServe();
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		exitStatus = 1;
	}
	return (exitStatus);
}
