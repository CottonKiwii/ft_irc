#ifndef MODEHANDLERS_HPP
# define MODEHANDLERS_HPP

# include "Client.hpp"

/**
 * We ignore it, because client sends it automatically,
 * but actual functionality of it is not required by
 * the subject
 */
void	modeUseri(Client &sender, char mod, char mode);
void	modeUserUnknown(Client &sender);

#endif
