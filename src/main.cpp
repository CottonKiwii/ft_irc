
#include <iostream>

int main(int argc, char **argv)
{
	if (argc != 3)
		return (std::cerr << "Error: argument format should be ./ircserv <port> <password> !" << std::endl, 1);

	(void)argv;
}
