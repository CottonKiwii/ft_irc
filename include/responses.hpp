#ifndef RESPONSES_HPP
# define RESPONSES_HPP

# include "Client.hpp"
# include "Command.hpp"

void	errNeedMoreParamsResponse(Client &sender, Command &command, std::string reason);
void	errAlreadyRegistered(Client &sender, std::string reason);
void	errPasswdMismatch(Client &sender, std::string reason);

#endif
