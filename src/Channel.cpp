#include "Channel.hpp"
#include "Server.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>

Channel::Channel() {};
Channel::~Channel() {};

std::string	Channel::getName() const { return _name; }
std::string	Channel::getTopic() const { return _topic; }
std::string	Channel::getKey() const { return _key; }
bool		Channel::getInviteOnly() const { return _mode._inviteOnly; }
size_t		Channel::getMemberLimit() const { return _memberLimit; }

void		Channel::setTopic(std::string topic) { _topic = topic; }
void		Channel::setKey(std::string key) { _key = key; }
void		Channel::setMemberLimit(size_t limit) { _memberLimit = limit; }
void		Channel::setInviteOnly(bool status) { _mode._inviteOnly = status; }
void		Channel::setProtectedTopic(bool status) { _mode._protectedTopic = status ;}

Channel::Channel(Client &creator, std::string name):
	_name(name),
	_topic(""),
	_createdTimestamp(std::time(0)),
	_memberLimit(0)
{
	_members.push_back(creator.getFd());
	_operators.push_back(creator.getFd());
	_mode._protectedTopic = true;
}

Channel::Channel(const Channel &other) {
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
}

std::string	Channel::getNames() const {
	std::string res;

	for (size_t i = 0; i < _members.size(); i++) {
		std::string name;
		std::vector<int>::const_iterator it =
			std::find(_operators.begin(), _operators.end(), _members[i]);
		if (it != _operators.end())
			name += "@";
		Client *client = Server::getClient(_members[i]);
		name += client->getNick();
		res += name;
		res += " ";
	}
	res.erase(res.begin() + res.size() - 1);
	return (res);
}

std::string	Channel::getModestring() const {
	std::string res = "+n";
	
	if (_mode._inviteOnly)
		res += "i";
	if (_mode._protectedTopic)
		res += "t";
	if (!_key.empty())
		res += "k";
	if (_memberLimit)
		res += "l";
	return (res);
}

std::string Channel::getModeArgs() const {
	std::string res = "";
	std::stringstream tokens;
	tokens << _memberLimit;
	tokens >> res;
	if (res == "0")
		return ("");
	return (res);
}
std::string Channel::getCreationTime() const {
	std::string res;
	std::stringstream tokens;
	tokens << _createdTimestamp;
	tokens >> res;
	return (res);
}

void	Channel::sendAll(std::string response) {
	for (size_t i = 0; i < _members.size(); i++) {
		Client *client = Server::getClient(_members[i]);
		client->addToResponse(response);
	}
}

void	Channel::addMember(int fd) {
	std::vector<int>::iterator it =
		std::find(_members.begin(), _members.end(), fd);
	if (it == _members.end())
		_members.push_back(fd);
}

void	Channel::removeMember(int fd) {
	std::vector<int>::iterator it = 
		std::find(_members.begin(), _members.end(), fd);
	if (it != _members.end())
		_members.erase(it);
	it = std::find(_operators.begin(), _operators.end(), fd);
	if (it != _operators.end())
		_operators.erase(it);
}

void	Channel::addOp(int fd) {
	std::vector<int>::iterator it =
		std::find(_operators.begin(), _operators.end(), fd);
	if (it == _operators.end())
		_operators.push_back(fd);
}

void	Channel::removeOp(int fd) {
	std::vector<int>::iterator it = 
		std::find(_operators.begin(), _operators.end(), fd);
	if (it != _operators.end())
		_operators.erase(it);
}

bool	Channel::isFull() const {
	return (_members.size() == _memberLimit);
}

bool	Channel::isClientMember(int fd) const {
	std::vector<int>::const_iterator	it =
		std::find(_members.begin(), _members.end(), fd);
	if (it != _members.end())
		return (true);
	return (false);
}

bool	Channel::isClientOp(int fd) const {
	std::vector<int>::const_iterator it =
		std::find(_operators.begin(), _operators.end(), fd);
	if (it != _operators.end())
		return (true);
	return (false);
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

bool	Channel::hasMode(char mode) const
{
	std::string modestr = getModestring();

	for (size_t i = 0; i < modestr.size(); i++) {
		if (modestr[i] == mode)
			return (true);
	}
	return (false);
}
