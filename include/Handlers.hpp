#ifndef HANDLERS_HPP
# define HANDLERS_HPP

# include "Client.hpp"
# include "Command.hpp"

void	handleCap(Client &sender, Command &command);

void	handlePing(Client &sender, Command &command);
void	handlePong(Client &sender, Command &command);

void	handleNick(Client &sender, Command &command);
void	handleUser(Client &sender, Command &command);
void	handlePass(Client &sender, Command &command);

void	handleJoin(Client &sender, Command &command);
void	handlePart(Client &sender, Command &command);
void	handleKick(Client &sender, Command &command);
void	handleQuit(Client &sender, Command &command);

void	handlePrivmsg(Client &sender, Command &command);
void	handleNotice(Client &sender, Command &command);
void	handleTopic(Client &sender, Command &command);
void	handleMode(Client &sender, Command &command);

void	handleUnknown(Client &sender, Command &command);

#endif
