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
	
	if (types.size() != 13) {
		types["CAP"] = CAP;
		types["PASS"] = PASS;
		types["NICK"] = NICK;
		types["USER"] = USER;
		types["QUIT"] = QUIT;
		types["PING"] = PING;
		types["PONG"] = PONG;
		types["JOIN"] = JOIN;
		types["PART"] = PART;
		types["KICK"] = KICK;
		types["MODE"] = MODE;
		types["PRIVMSG"] = PRIVMSG;
		types["NOTICE"] = NOTICE;
	}

	std::map<std::string, e_command>::iterator it = types.find(rawType);
	if (it != types.end())
		return (it->second);
	return (UNKNOWN);
}
