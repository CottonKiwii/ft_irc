#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <vector>
# include "Client.hpp"

struct s_mode {
	bool	_inviteOnly;
	bool	_protectedTopic;
};

class Channel {
	private:
		std::vector<int>	_members;
		std::vector<int>	_operators;
		std::string			_name;
		std::string			_topic;
		std::string			_key;
		bool				_public;
		size_t				_memberLimit;
		s_mode				_mode;

		Channel();
	public:
		Channel(Client &creator, std::string name);
		Channel(const Channel &other);
		~Channel();
		
		Channel &operator=(const Channel &ohter);

		std::string	getName() const;
		std::string	getTopic() const;
		std::string	getKey() const;
		bool		getPublic() const;
		bool		getInviteOnly() const;

		void		setTopic(std::string topic);
		void		setKey(std::string key);

		std::string getNames() const;
		void		sendAll(std::string response);

		void		addMember(int fd);
		void		removeMember(int fd);
	
		bool		isFull() const;

		static bool	verifyName(std::string name);
};

#endif
