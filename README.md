*This project has been created as part of the 42 curriculum by svereten, jwolfram.*

# ❤️ ft_irc ❤️
Create your own IRC server in C++98, compatible with a standard IRC client for the required features.
## Overview
- [Description](#description)
- [Instructions](#instructions)
- [Resources](#resources)
## Description
The Internet Relay Chat, or IRC for short, was first created in 1988 by Jarkko Oikarinen and revolutionized text-based instant messaging for both private and group communication. \
The goal of this project is to **create our own working IRC server in C++(98)** with the help of a standard IRC client as reference.

For our implementation, the things required by the subject are the following:
### Client based requirements
- Communication between client and server must be TCP or IP (both v4 or v6 are allowed)
- Set a nickname and a username
- Send and receive private messages
- Join a channel, send and receive messages in it
### Channel based requirements
- Be able to have operators and regular clients in a channel
- Kick a client from a channel
- Invite a client to a channel
- Change/View the channel topic
- Change the channel's mode
## Instructions
❗ **If Irssi (our client) is not installed on your device, install it based on your system requirements on [their website](https://irssi.org/download/).**

To run this program, you need to first run our ft_irc program, \
then open the Irssi client and connect to our programs port and password.
### For ft_irc compilation:
- `make run` - run this project with default port and password
- `make run ARGS="<port> <password>"` - run this project with specified port and password

### For Irssi compilation:
- `irssi` - run Irssi
- `make client` - run Irssi with a default profile
- `make client PROFILE="<profile name>"` - run Irssi with a selected profile

### Other:
- `nc -C 127.0.0.1 <port>` - run netcat (cat command but for a TCP connection)
## Resources
🚫 **No AI was used in the making of this project** 🚫

Since IRC has a lot of different clients and servers, their protocols started to deviate more and more from the numeric protocols \
that were originally set by IRC. While some of the protocols on these websites stayed the same and worked with our chosen client, \
others didn't, so we had to find a source that suits the Irssi client.
### Most Reliable Source:
https://www.alien.net.au/irc/irc2numerics.html
### Other Sources:
- https://modern.ircdocs.horse
- https://www.rfc-editor.org/info/rfc1459/
- https://dd.ircdocs.horse
- https://en.wikipedia.org/wiki/IRC
