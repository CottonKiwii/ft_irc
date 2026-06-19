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

// NICKNAME ERRORS
# define ERR_NONICKNAMEGIVEN(sender)		":localhost 431 " + sender + " :No nickname given\n"
# define ERR_ERRONEUSNICKNAME(sender, nick)	":localhost 432 " + sender + " " + nick + " :Erroneus nickname\n"
# define ERR_NICKNAMEINUSE(sender, nick)	":localhost 433 " + sender + " " + nick + " :Nickname is already in use\n"

// GENERAL ERRORS
# define ERR_NEEDMOREPARAMS(sender)			":localhost 461 " + sender + " :Not enough parameters\n"
# define ERR_ALREADYREGISTERED(sender)		":localhost 462 " + sender + " :You may not reregister\n"

// OFFICIAL IRC REPLIES
# define RPL_WELCOME						":localhost 001 :"

// CUSTOM IRC REPLIES
# define RPL_NEWNICKNAME					":localhost NICK :"
# define RPL_PING							":localhost PONG :"

#endif
