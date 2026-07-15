#include "Command.hpp"
#include <sstream>
#include <string>
#include <map>

Command::Command(std::string rawCommand) {
	std::istringstream	split(rawCommand);
	std::string			arg;
	
	while(std::getline(split, arg, ' ')) {
		_args.push_back(arg);
	}

	_type = Command::getType(_args[0]);
}

Command::Command(const Command &other):
	_type(other._type),
	_args(other._args)
{}

Command::~Command() {}

int							Command::getType() const { return _type; }
std::vector<std::string>	Command::getArgs() const { return _args;}

e_command	Command::getType(std::string rawType) {
	static std::map<std::string, e_command> types;
	
	if (types.size() != 39) {
		types["PASS"] = PASS;
		types["NICK"] = NICK;
		types["USER"] = USER;
		types["PING"] = PING;
		types["PONG"] = PONG;
		types["QUIT"] = QUIT;
		types["JOIN"] = JOIN;
		types["PART"] = PART;
		types["KICK"] = KICK;
		types["MODE"] = MODE;
		types["TOPIC"] = TOPIC;
		types["INVITE"] = INVITE;
		types["PRIVMSG"] = PRIVMSG;
		types["NOTICE"] = NOTICE;
		types["CAP"] = UNHANDLED;
		types["AUTHENTICATE"] = UNHANDLED;
		types["OPER"] = UNHANDLED;
		types["ERROR"] = UNHANDLED;
		types["NAMES"] = UNHANDLED;
		types["MOTD"] = UNHANDLED;
		types["VERSION"] = UNHANDLED;
		types["ADMIN"] = UNHANDLED;
		types["CONNECT"] = UNHANDLED;
		types["LUSERS"] = UNHANDLED;
		types["TIME"] = UNHANDLED;
		types["STATS"] = UNHANDLED;
		types["HELP"] = UNHANDLED;
		types["INFO"] = UNHANDLED;
		types["WHO"] = UNHANDLED;
		types["WHOIS"] = UNHANDLED;
		types["WHOWAS"] = UNHANDLED;
		types["KILL"] = UNHANDLED;
		types["REHASH"] = UNHANDLED;
		types["RESTART"] = UNHANDLED;
		types["SQUIT"] = UNHANDLED;
		types["AWAY"] = UNHANDLED;
		types["LINKS"] = UNHANDLED;
		types["USERHOST"] = UNHANDLED;
		types["WALLOPS"] = UNHANDLED;
	}

	std::map<std::string, e_command>::iterator it = types.find(rawType);
	if (it != types.end())
		return (it->second);
	return (UNKNOWN);
}
