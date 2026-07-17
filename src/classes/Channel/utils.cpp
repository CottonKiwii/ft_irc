#include "irc.hpp"

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
		if (!client) {
			this->removeMember(_members[i]);
			continue ;
		}
		client->addToResponse(response);
	}
}

void	Channel::sendAll(std::string response, int fdToIgnore) {
	for (size_t i = 0; i < _members.size(); i++) {
		Client *client = Server::getClient(_members[i]);
		if (!client) {
			this->removeMember(_members[i]);
			continue ;
		}
		if (client->getFd() == fdToIgnore)
			continue ;
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

void	Channel::addInvited(int fd) {
	std::vector<int>::iterator it =
		std::find(_invited.begin(), _invited.end(), fd);
	if (it == _invited.end())
		_invited.push_back(fd);
}

void	Channel::removeInvited(int fd) {
	std::vector<int>::iterator it = 
		std::find(_invited.begin(), _invited.end(), fd);
	if (it != _invited.end())
		_invited.erase(it);
}

bool	Channel::isEmpty() const {
	return (_members.size() == 0);
}

bool	Channel::isFull() const {
	return (_memberLimit ? _members.size() >= _memberLimit : false);
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

bool	Channel::isClientInvited(int fd) const {
	std::vector<int>::const_iterator it =
		std::find(_invited.begin(), _invited.end(), fd);
	if (it != _invited.end())
		return (true);
	return (false);
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
