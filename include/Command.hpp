#ifndef COMMAND_HPP
# define COMMAND_HPP

#include <string>
#include <vector>

enum e_command {
	UNKNOWN,
	CAP,
	PASS,
	NICK,
	USER,
	QUIT,
	PING,
	PONG,
	JOIN,
	PART,
	KICK,
	MODE,
	PRIVMSG,
	NOTICE,
};

class Command {
	private:
		Command();
		Command	&operator=(const Command &other);

		e_command					_type;
		std::vector<std::string>	_args;

	public:
		Command(std::string rawCommand);
		Command(const Command &other);
		~Command();
		
		static e_command	getType(std::string rawType);
};

#endif
