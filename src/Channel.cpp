#include "Channel.hpp"
#include "Server.hpp"
#include <algorithm>
#include <iostream>

Channel::Channel() {};
Channel::~Channel() {};

std::string	Channel::getName() const { return _name; }
std::string	Channel::getTopic() const { return _topic; }
std::string	Channel::getKey() const { return _key; }
bool		Channel::getPublic() const { return _public; }

void		Channel::setTopic(std::string topic) { _topic = topic; }
void		Channel::setKey(std::string key) { _key = key; }

Channel::Channel(Client &creator, std::string name):
	_name(name),
	_public(true)
{
	_members.push_back(creator.getFd());
	_operators.push_back(creator.getFd());
}

Channel::Channel(const Channel &other) {
	if (this != &other) {
		_members = other._members;
		_operators = other._operators;
		_name = other._name;
		_topic = other._topic;
		_key = other._key;
	}
}

std::string	Channel::getNames() const {
	std::string res;

	for (size_t i = 0; i < _members.size(); i++) {
		std::string name;
		std::vector<int>::const_iterator it =
			std::find(_operators.begin(), _operators.end(), _members[i]);
		if (it != _operators.end())
			name += "@";
		Client *client = Server::getClientByFd(_members[i]);
		name += client->getNick();
		res += name;
		res += " ";
	}
	res.erase(res.begin() + res.size() - 1);

	return (res);
}

bool	Channel::verifyName(std::string rawName) {
	if (rawName.size() < 2 || rawName.size() > 200)
		return (false);
	if (rawName[0] != '#')
		return (false);
	for (size_t i = 1; i < rawName.size(); i++) {
		if (rawName[i] == 7 || rawName[i] == ' ' || rawName[i] == ',')
			return (false);
	}
	return (true);
}
