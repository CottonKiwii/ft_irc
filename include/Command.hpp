#ifndef COMMAND_HPP
# define COMMAND_HPP

#include <string>

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

		std::string	_raw;
		e_command	_type;

	public:
		Command(const Command &other);
		~Command();
		
		static int	getType(std::string rawType);
};

#endif
