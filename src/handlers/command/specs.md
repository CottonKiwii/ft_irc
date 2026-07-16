# Specs for commands

## Auth commands

### [PASS](https://modern.ircdocs.horse/#pass-message)

- [x] 461 ERR_NEEDMOREPARAMS
- [x] 462 ERR_ALREADYREGISTERED
- [x] 463 ERR_PASSWDMISMATCH
    - [x] ERROR closing link after USER is sent but last password was wrong
- [x] Silent if valid

### [NICK](https://modern.ircdocs.horse/#nick-message)

- [x] 431 ERR_NONICKNAMEGIVEN
- [x] 432 ERR_ERRONEUSNICKNAME
- [x] 433 ERR_NICKNAMEINUSE
- [x] 436 ERR_NICKCOLLISION we don't imlement
- [x] Silent if valid during registration
- [x] sends ":<prefix> NICK <newnick>" if valid after registration

### [USER](https://modern.ircdocs.horse/#user-message)

- [x] 461 ERR_NEEDMOREPARAMS
- [x] 462 ERR_ALREADYREGISTERED
- [x] ERROR closing link if last password was wrong or if nick is not set
- [x] 001 RPL_WELCOME is sent if registration was valid

## Connection commands

### [PING](https://modern.ircdocs.horse/#ping-message)

- [x] 461 ERR_NEEDMOREPARAMS
- [x] PONG reply

### [PONG](https://modern.ircdocs.horse/#pong-message)

- [x] Doesn't need a reply or any handling really

### [QUIT](https://modern.ircdocs.horse/#quit-message)

- [x] ":<prefix> QUIT :Quit: <reason>"

## Channel commands

### [JOIN](https://modern.ircdocs.horse/#join-message)

- [x] 403 ERR_NOSUCHCHANNEL (channel either exists or will be created, don't know in which situation this one will be sent)
- [x] 405 ERR_TOOMANYCHANNELS (we don't have a channel amount restriction)
- [x] 461 ERR_NEEDMODEPARAMS
- [x] 471 ERR_CHANNELISFULL
- [x] 473 ERR_INVITEONLYCHAN
- [x] 474 ERR_BANNEDFROMCHAN (we don't implement bans)
- [x] 475 ERR_BADCHANNELKEY
- [x] 476 ERR_BADCHANMASK
- [x] 332 RPL_TOPIC
- [x] 333 RPL_TOPICWHOTIME (we don't implement this one)
- [x] 353 RPL_NAMEREPLY
- [x] 366 RPL_ENDOFNAMES
- [x] joining several channels (create all)
- [x] joining several channels (join all)
- [x] joining several channels (join all with passwords)
- [x] joining several channels (mixed)

### [INVITE](https://modern.ircdocs.horse/#invite-message)

- [x] 461 ERR_NEEDMOREPARAMS
- [x] 401 ERR_NOSUCHNICK
- [x] 403 ERR_NOSUCHCHANNEL
- [x] 442 ERR_NOTONCHANNEL
- [x] 443 ERR_USERONCHANNEL
- [x] 482 ERR_CHANOPRIVSNEEDED
- [x] 341 RPL_INVITING
- [x] ":<prefix> INVITE <nick> <channel>" to invitee

### [PART](https://modern.ircdocs.horse/#part-message)

- []

### [KICK](https://modern.ircdocs.horse/#kick-message)

- []

### [MODE](https://modern.ircdocs.horse/#mode-message)

- []

### [TOPIC](https://modern.ircdocs.horse/#topic-message)

- [x] 403 ERR_NOSUCHCHANNEL
- [x] 442 ERR_NOTONCHANNEL
- [x] 461 ERR_NEEDMOREPARAMS (if no params, just returns topic, don't know in which situaton this one will be sent)
- [x] 482 ERR_CHANOPRIVSNEEDED
- [x] 331 RPL_NOTOPIC (irssi doesn't actually send anything in case if it knows that there is no topic, but we handle notopic)
- [x] 332 RPL_TOPIC
- [x] 333 RPL_TOPICWHOTIME (we don't implement this one)


## Messaging commands

### [PRIVMSG](https://modern.ircdocs.horse/#privmsg-message)

- []

### [NOTICE](https://modern.ircdocs.horse/#notice-message)

- []

