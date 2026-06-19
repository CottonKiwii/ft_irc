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

# define ERR_NEEDMOREPARAMS(sender)		":localhost 461 " + sender + " :Not enough parameters\n"
# define ERR_ALREADYREGISTERED(sender)	":localhost 462 " + sender + " :You may not reregister\n"

# define RPL_WELCOME					":localhost 001 "
# define RPL_PING						":localhost PONG "

#endif
