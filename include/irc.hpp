#ifndef IRC_HPP 
# define IRC_HPP 

# include <iostream>

# include <sstream>
# include <string>

# include <algorithm>
# include <map>

# include <signal.h>
# include <unistd.h>
# include <string.h>

# include <sys/socket.h>
# include <sys/types.h>
# include <sys/poll.h>

# include <arpa/inet.h>
# include <netinet/in.h>
# include <asm-generic/socket.h>

# include "Server.hpp"
# include "Client.hpp"
# include "Command.hpp"
# include "Channel.hpp"
# include "handlers/command.hpp"
# include "handlers/mode.hpp"
# include "privmsgHandlers.hpp"

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
# define RPL_NOTOPIC(client, channel)			":localhost 331 " \
												+ client.getNick() \
												+ " " \
												+ channel.getName() \
												+ " :No topic is set\n"
# define RPL_TOPIC(client, channel)				":localhost 332 " \
												+ client.getNick() \
												+ " " \
												+ channel.getName() \
												+ " :" \
												+ channel.getTopic() \
												+ "\n"
# define RPL_INVITING(s, i, channel)			":localhost 341 " \
												+ s.getNick() \
												+ " "\
												+ i.getNick() \
												+ " "\
												+ channel.getName() \
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
# define ERR_UNKNOWNCOMMAND(commandName)		":localhost 421 " \
												+ commandName \
												+ " :Unknown command\n"
# define ERR_NEEDMOREPARAMS(client)				":localhost 461 " + client.getNick() \
												+ " :Not enough parameters\n"
# define ERR_ALREADYREGISTERED(client)			":localhost 462 " + client.getNick() \
												+ " :You may not reregister\n"
# define ERR_PASSWDMISMATCH(client)				":localhost 464 " + client.getNick() \
												+ " :Password is incorrect\n"
// PRIVMSG ERRORS
# define ERR_NOSUCHNICK(client, nick)			":localhost 401 " \
												+ nick \
												+ " :No such nick/channel"
# define ERR_NOSUCHCHANNEL(chanName)			":localhost 403 " \
												+ chanName \
												+ " :No such channel\n"

# define ERR_CANNOTSENDTOCHAN(channel)			":localhost 404 " \
												+ channel.getName() \
												+ " :Cannot send to channel\n"
# define ERR_NOTEXTTOSEND(client)				":localhost 412 " + client.getNick() \
												+ " :No text to send"

// NICKNAME ERRORS
# define ERR_NONICKNAMEGIVEN(client)			":localhost 431 " + client.getNick() \
												+ " :No nickname given\n"
# define ERR_ERRONEUSNICKNAME(nick)				":localhost 432 " \
												+ nick \
												+ " :Erroneus nickname\n"
# define ERR_NICKNAMEINUSE(nick)				":localhost 433 " \
												+ nick \
												+ " :Nickname is already in use\n"

// CHANNEL ERRORS
# define ERR_USERNOTINCHANNEL(nick, channel)	":localhost 441 " \
												+ nick \
												+ " " \
												+ channel.getName() \
												+ " :User is not on channel\n"
# define ERR_NOTONCHANNEL(channel)				":localhost 442 " \
												+ channel.getName() \
												+ " :You are not on channel\n"
# define ERR_USERONCHANNEL(client, channel)		":localhost 443 " \
												+ client.getNick() \
												+ " "\
												+ channel.getName() \
												+ " :User is already on channel\n"
# define ERR_KEYSET(channel)					":localhost 467 " \
												+ channel.getName() \
												+ " :Channel key is already set\n"
# define ERR_CHANNELISFULL(client, channel)		":localhost 471 " \
												+ client.getNick() \
												+ " " \
												+ channel.getName() \
												+ " :Cannot join channel (+l)\n"
# define ERR_UNKNOWNMODE(client, modeChar)		":localhost 472 " \
												+ client.getNick() \
												+ " " \
												+ modeChar \
												+ " :Unknown mode char\n"
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
												+ " :Invalid channel name)\n"
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

# define ERROR_CLOSINGLINK(reason)				"ERROR :Closing Link: localhost (" \
												reason \
												")\n"
// OFFICIAL IRC REPLIES
# define RPL_WELCOME							":localhost 001 "

// CUSTOM IRC REPLIES
# define CMD_PING								":localhost PING "
# define CMD_PONG								":localhost PONG "
# define CMD_QUIT(source)						":" \
												+source \
												+ " QUIT :Quit"
# define CMD_TOPIC(source)						":" \
												+ source \
												+ " TOPIC "
# define RPL_PRIVMSG							":localhost PRIVMSG :"

#endif
