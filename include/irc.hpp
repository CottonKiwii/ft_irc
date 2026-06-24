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

// REPLIES
# define RPL_UMODEIS(client)					":localhost 221 " \
												+ client.getNick() \
												+ " +r\n"
# define RPL_CHANNELMODEIS(client, channel)		":localhost 324 " \
												+ client.getNick() \
												+ " " \
												+ channel.getName() \
												+ " "\
												+ channel.getModestring() \
												+ " "\
												+ channel.getModeArgs() \
												+ "\n"
# define RPL_CREATIONTIME(client, channel)		":localhost 329 " \
												+ client.getNick() \
												+ " " \
												+ channel.getName() \
												+ " " \
												+ channel.getCreationTime() \
												+ "\n"
# define RPL_TOPIC(client, channel)				":localhost 332 " \
												+ client.getNick() \
												+ " "\
												+ channel.getName() \
												+ " :"\
												+ channel.getTopic() \
												+ "\n"
/**
 * No @ or * options for privacy of the channel
 * because according to subject all the channels
 * are public (keys and invites are not affected
 * by how private a channel is, only the commands
 * that we are not supposed to implement are)
 */
# define RPL_NAMERPLY(client, channel)			":localhost 353 " \
												+ client.getNick() \
												+ " = " \
												+ channel.getName() \
												+ " :" \
												+ channel.getNames() \
												+ "\n"
# define RPL_ENDOFNAMES(client, channel)		":localhost 366 " \
												+ client.getNick() \
												+ " " \
												+ channel.getName() \
												+ " :End of /NAMES list.\n"


// GENERAL ERRORS
# define ERR_NEEDMOREPARAMS(sender)				":localhost 461 " + sender \
												+ " :Not enough parameters\r\n"
# define ERR_ALREADYREGISTERED(sender)			":localhost 462 " + sender \
												+ " :You may not reregister\r\n"
# define ERR_PASSWDMISMATCH(sender)				":localhost 464 " + sender \
												+ " :Password is incorrect\r\n"

// PRIVMSG ERRORS
# define ERR_NOSUCHNICK(client, nick)			":localhost 401 " \
												+ nick \
												+ " :No such nick/channel"
# define ERR_NOSUCHCHANNEL(client, name)		":localhost 403 " \
												+ client.getNick() \
												+ " " \
												+ name \
												+ " :No such channel\n"
# define ERR_CANNOTSENDTOCHAN(sender, chan)		":localhost 403 " + sender + " " + chan \
												+ " :Cannot send to channel\r\n"

// NICKNAME ERRORS
# define ERR_NONICKNAMEGIVEN(sender)			":localhost 431 " + sender \
												+ " :No nickname given\r\n"
# define ERR_ERRONEUSNICKNAME(sender, nick)		":localhost 432 " + sender + " " + nick \
												+ " :Erroneus nickname\r\n"
# define ERR_NICKNAMEINUSE(sender, nick)		":localhost 433 " + sender + " " + nick \
												+ " :Nickname is already in use\r\n"

// CHANNEL ERRORS
# define ERR_CHANNELISFULL(client, channel)		":localhost 471 " \
												+ client.getNick() \
												+ " " \
												+ channel.getName() \
												+ " :Cannot join channel (+l)\n"
# define ERR_INVITEONLYCHAN(client, channel)	":localhost 473 " \
												+ client.getNick() \
												+ " " \
												+ channel.getName() \
												+ " :Cannot join channel (+i)\n"
# define ERR_BADCHANNELKEY(client, channel)		":localhost 475 " \
												+ client.getNick() \
												+ " " \
												+ channel.getName() \
												+ " :Cannot join channel (+k) - bad key\n"
# define ERR_BADCHANMASK(client, name)			":localhost 476 " \
												+ client.getNick() \
												+ " " \
												+ name \
												+ " :Invalid channel name\n"
# define ERR_CHANOPRIVSNEEDED(client, channel)	":localhost 482 " \
												+ client.getNick() \
												+ " " \
												+ channel.getName() \
												+ " :You're not channel operator\n"
// MODE ERRORS
# define ERR_UMODEUNKNOWNFLAG(client)			":localhost 501 " \
												+ client.getNick() \
												+ " :Unknown MODE flag\n"
# define ERR_USERSDONTMATCH(client)				":localhost 502 " \
												+ client.getNick() \
												+ " :Can't access mode of other users\n"


// OFFICIAL IRC REPLIES
# define RPL_WELCOME							":localhost 001 "

// CUSTOM IRC REPLIES
# define RPL_PING								":localhost PONG :"
# define RPL_QUIT								":localhost QUIT :"
# define RPL_PRIVMSG							":localhost PRIVMSG :"

#endif
