
#ifndef PRIVMSGHANDLERS_HPP
# define PRIVMSGHANDLERS_HPP

# include "Client.hpp"
# include "Channel.hpp"
# include "Command.hpp"

void	handleClientToClient(Client &sender, Client &receiver, Command &command);
void	handleClientToChannel(Client &sender, Channel &receiver, Command &command);

#endif
