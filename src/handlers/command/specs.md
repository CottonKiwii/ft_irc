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

- []

### [PART](https://modern.ircdocs.horse/#part-message)

- []

### [KICK](https://modern.ircdocs.horse/#kick-message)

- []

### [MODE](https://modern.ircdocs.horse/#mode-message)

- []

### [TOPIC](https://modern.ircdocs.horse/#topic-message)

- []


## Messaging commands

### [PRIVMSG](https://modern.ircdocs.horse/#privmsg-message)

- []

### [NOTICE](https://modern.ircdocs.horse/#notice-message)

- []

