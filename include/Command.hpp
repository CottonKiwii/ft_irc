#ifndef COMMAND_HPP
# define COMMAND_HPP

#include <string>
#include <vector>

enum e_command {
	UNKNOWN,
	UNHANDLED,
	PASS,
	NICK,
	USER,
	QUIT,
	PING,
	PONG,
	JOIN,
	PART,
	KICK,
	TOPIC,
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
		
		int							getType() const;
		std::vector<std::string>	getArgs() const;

		static e_command			getType(std::string rawType);
};

#endif
