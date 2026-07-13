# Specs for commands

## Auth commands

### [PASS](https://modern.ircdocs.horse/#pass-message)

- [x] 461 ERR_NEEDMODEPARAMS
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

- [x] 461 ERR_NEEDMODEPARAMS
- [x] 462 ERR_ALREADYREGISTERED
- [x] ERROR closing link if last password was wrong or if nick is not set
- [x] 001 RPL_WELCOME is sent if registration was valid

## Connection commands
