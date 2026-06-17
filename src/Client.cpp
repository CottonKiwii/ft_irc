#include "Client.hpp"

Client::Client(int fd, std::string ip): _fd(fd), _ip(ip) {}
Client::~Client() {}

std::string	Client::getIp() const { return _ip; }
int			Client::getFd() const { return _fd; }
