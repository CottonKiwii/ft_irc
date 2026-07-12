#include "Channel.hpp"
#include "Server.hpp"

Channel::Channel() {};
Channel::~Channel() {};
Channel::Channel(Client &creator, std::string name):
	_name(name),
	_topic(""),
	_createdTimestamp(std::time(0)),
	_memberLimit(0)
{
	_members.push_back(creator.getFd());
	_operators.push_back(creator.getFd());
	_mode._inviteOnly = false;
	_mode._protectedTopic = true;
}
Channel::Channel(const Channel &other):
	_members(other._members),
	_operators(other._operators),
	_name(other._name),
	_topic(other._topic),
	_key(other._key),
	_createdTimestamp(other._createdTimestamp),
	_mode(other._mode),
	_memberLimit(other._memberLimit) {}

Channel	&Channel::operator=(const Channel &other) {
	if (this != &other) {
		_members = other._members;
		_operators = other._operators;
		_name = other._name;
		_topic = other._topic;
		_key = other._key;
		_createdTimestamp = other._createdTimestamp;
		_mode = other._mode;
		_memberLimit = other._memberLimit;
	}
	return (*this);
}

void	Channel::updateMembers() {
	for (
		std::vector<int>::iterator it = _members.begin();
		it != _members.end();
		it++) {
		Client	*client = Server::getClient(*it);
		if (!client)
			removeMember(*it);
	}
}
