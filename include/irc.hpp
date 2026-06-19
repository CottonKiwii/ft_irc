#ifndef IRC_HPP 
# define IRC_HPP 

# include <iostream>
# include <unistd.h>
# include <string.h>
# include <sstream>

# include <string>
# include <map>

# include <sys/socket.h>
# include <sys/types.h>
# include <sys/poll.h>

# include <arpa/inet.h>
# include <netinet/in.h>
# include <asm-generic/socket.h>

# include "Client.hpp"
# include "Command.hpp"
# include "Server.hpp"
# include "Handlers.hpp"

# define ERR_NEEDMOREPARAMS	":localhost 461 "

# define RPL_WELCOME		":localhost 001 "

# define RPL_PING			":localhost PONG "

#endif
