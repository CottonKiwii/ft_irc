#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <vector>
# include "Client.hpp"

class Channel {
	private:
		std::vector<int>	_members;
		std::vector<int>	_operators;
		std::string			_name;
		std::string			_topic;
		std::string			_key;
		bool				_public;

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

		void		setTopic(std::string topic);
		void		setKey(std::string key);

		std::string getNames() const;

		static bool	verifyName(std::string name);
};

#endif
