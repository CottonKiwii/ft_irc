#include "Command.hpp"
#include <cstddef>

Command::Command(const Command &other):
	_raw(other._raw)
{}

Command::~Command() {};

int	Command::getType() const { return _type; }

int	Command::getType(std::string rawType) {
	std::string	types[] = {
		"CAP", "PASS", "NICK", "USER", "QUIT", "PING", "PONG",
		"JOIN", "PART", "KICK", "MODE",
		"PRIVMSG", "NOTICE"
	};

	for (size_t i = 0; i < 13; i++)
	  if (types[i] == rawType)
	   return (i);

	return (UNKNOWN);
}

