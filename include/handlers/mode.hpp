#ifndef HANDLERSMODE_HPP
# define HANDLERSMODE_HPP

# include "Client.hpp"
# include "Channel.hpp"

# include <queue>

/**
 * We ignore it, because client sends it automatically,
 * but actual functionality of it is not required by
 * the subject
 */
void	modeUseri(Client &sender, char mod, char mode);
void	modeUserUnknown(Client &sender);

bool	modeChani(Channel &channel, char mod);
bool	modeChant(Channel &channel, char mod);
bool	modeChank(Channel &channel, 
						Client &sender,
						std::queue<std::string> modeArgs,
						char mod);
bool	modeChano(Channel &channel,
						Client &sender,
						std::queue<std::string> modeArgs,
						char mod);
bool	modeChanl(Channel &channel,
						Client &sender,
						std::queue<std::string> modeArgs,
						char mod);
void			modeChanUnknown(Client &sender, char mode);

#endif
