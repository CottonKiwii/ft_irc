#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <ctime>
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
		time_t				_createdTimestamp;
		s_mode				_mode;
		size_t				_memberLimit;

		Channel();
	public:
		Channel(Client &creator, std::string name);
		Channel(const Channel &other);
		~Channel();
		
		Channel &operator=(const Channel &ohter);

		std::string	getName() const;
		std::string	getTopic() const;
		std::string	getKey() const;
		bool		getInviteOnly() const;

		void		setTopic(std::string topic);
		void		setKey(std::string key);
		void		setMemberLimit(size_t limit);

		std::string getNames() const;
		/**
		 * Will always have at least "+n" mode
		 * because according to subject only 
		 * channel members are allowed to send messages
		 * to the channel
		 */
		std::string getModestring() const;
		std::string	getModeArgs() const;
		std::string	getCreationTime() const;

		void		sendAll(std::string response);

		void		addMember(int fd);
		void		removeMember(int fd);
	
		bool		isFull() const;
		bool		isClientMember(int fd) const;
		bool		isClientOp(int fd) const;
		bool		hasMode(char mode) const;
		bool		hasModes() const;

		static bool	verifyName(std::string name);
};

#endif
