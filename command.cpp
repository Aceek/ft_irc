/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 23:22:45 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/11 08:29:34 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"
#include "include.hpp"

#include <string>
#include <vector>
#include <map>

// Command::Command(void) {} (pas de constructeur par default pour ref client)

Command::Command(std::string const &line, Client &client, Server &server) : 
	_client(client),
	_server(server) {
	initCmdMap();
	
	std::istringstream	iss(line);
	if (line[0] == ':') {
		iss >> this->_prefix; // extract prefix
		this->_prefix = this->_prefix.substr(1);
	}
	iss >> this->_name; // extract command
	toUpperCase(this->_name);

	std::string arg;
	while (iss >> arg) {
		if (!arg.empty() && arg[0] == ':') { // Trailing detected
			arg = arg.substr(1);
			std::getline(iss, this->_trailor);
			this->_trailor = arg + this->_trailor;
			break;
		}
		this->_args.push_back(arg);
	}
	if (this->_name != "PASS" && !this->_client.isPasswordSetUp()) {
		throw std::runtime_error("Error : Password required");
	}
}

Command::Command(Command const &rhs) :
	_prefix(rhs._prefix),
	_name(rhs._name),
	_args(rhs._args),
	_trailor(rhs._trailor),
	_client(rhs._client),
	_server(rhs._server) {}

Command &Command::operator=(Command const &rhs) {
    if (this == &rhs) {
        return *this;
    }

	this->_prefix = rhs._prefix;
	this->_name = rhs._name;
	this->_args = rhs._args;
	this->_trailor = rhs._trailor;
	this->_client = rhs._client;
	this->_server = rhs._server;

    return *this;
}

Command::~Command(void) {}

/* ************************************************************************** */

void Command::initCmdMap(void) {
    _map["NICK"] = &Command::NICK;
    _map["USER"] = &Command::USER;
    _map["PASS"] = &Command::PASS;
    _map["INVITE"] = &Command::INVITE;
    _map["JOIN"] = &Command::JOIN;
    _map["KICK"] = &Command::KICK;
    _map["MODE"] = &Command::MODE;
    _map["OPER"] = &Command::OPER;
    _map["PART"] = &Command::PART;
    _map["PONG"] = &Command::PONG;
    _map["PRIVMSG"] = &Command::PRIVMSG;
    _map["TOPIC"] = &Command::TOPIC;
    _map["NAMES"] = &Command::NAMES;
}

void Command::printArgs(void) const {
    std::cout << "Prefix: " << this->_prefix << std::endl;
    std::cout << "Name: " << this->_name << std::endl;

    std::cout << "Arguments:";
    for (size_t i = 0; i < this->_args.size(); ++i) {
        std::cout << " " << this->_args[i];
    }
    std::cout << std::endl;

    if (!this->_trailor.empty()) {
        std::cout << "Trailing: " << this->_trailor << std::endl;
    }
}

int Command::exec(void) {
    std::map<std::string, cmdFt>::iterator it = _map.find(this->_name);
    if (it != _map.end()) {
        return ((this->*(it->second))());
    } else {
		// throw std::runtime_error("Error: Unkown command");
		std::cout << "Error unknow command" << std::endl;
		return (-1);
	}
	return (0);
}

/* ************************************************************************** */

std::string const &Command::getPrefix(void) const {
    return this->_prefix;
}

std::string const &Command::getName(void) const {
    return this->_name;
}

std::vector<std::string> const &Command::getArgs(void) const {
    return this->_args;
}

std::string const &Command::getTrailor(void) const {
    return this->_trailor;
}

Client &Command::getClient(void) const {
    return this->_client;
}

Server &Command::getServer(void) const {
    return this->_server;
}

/* ************************************************************************** */

int Command::INVITE() {
/*   Parameters: <nickname> <channel>	*/
    if (this->getArgs().size() < 2) {
        return ERR_NEEDMOREPARAMS;
    }

    std::string nickname = this->getArgs()[0];
    std::string channelName = this->getArgs()[1];

    Channel *channel = this->getServer().getChannel(channelName);
    if (!channel) {
        return ERR_NOSUCHCHANNEL;
    }

    if (!channel->isOperator(getClient())) {
        return ERR_CHANOPRIVSNEEDED;
    }

	Client *client = this->getServer().getClientByNickname(nickname);
	if (!client) {
    	return ERR_NOSUCHNICK;
    }

	if (channel->isClientPresent(*client)) {
        return ERR_USERONCHANNEL;
    }

    std::string inviteMessage =	":" + this->getClient().getNicknameOrUsername(true) +
                        		" " + this->getName() +
								" " + nickname +
								" " + channelName;
								
	channel->sendMessageToAll(inviteMessage);
	this->getServer().sendMessage(*client, inviteMessage);

    return ERR_NONE;
}

int Command::JOIN() {
/*   Parameters: <channel>{,<channel>} [<key>{,<key>}]	*/
    if (this->getArgs().size() < 1) {
        return ERR_NEEDMOREPARAMS;
    }

    std::vector<std::string> channels = ft_split(this->getArgs()[0], ",");
    std::vector<std::string> keys;

    if (this->getArgs().size() > 1) {
        keys = ft_split(this->getArgs()[1], ",");
    }

    for (size_t i = 0; i < channels.size(); ++i) {
        std::string const &channelName = channels[i];
        std::string key;

        if (i < keys.size()) {
            key = keys[i];
        }

        if (channelName[0] != '#') {
            return ERR_BADCHANMASK;
        }

        Channel *channel = this->getServer().getChannel(channelName);
        Client &client = this->getClient();

        if (!channel) {
            this->getServer().addChannel(channelName);
            channel = this->getServer().getChannel(channelName);

            if (!key.empty()) {
                channel->setKey(key);
            }
        } else if (!key.empty() && key != channel->getKey()) {
        	return ERR_BADCHANNELKEY;
        }

        channel->addUser(client, false);
		
		std::string joinMessage =	":" + this->getClient().getNicknameOrUsername(true) +
									" " + this->getName() + 
									" " + channelName;
								
		channel->sendMessageToAll(joinMessage);
		
		channel->RPL_TOPIC(client);
		channel->RPL_NAMREPLY(client);
		channel->RPL_ENDOFNAMES(client);
    }
	
	return ERR_NONE;
}

int Command::KICK() {
/*   Parameters: <channel> <user> [<comment>]	*/
    if (this->getArgs().size() < 2) {
        return ERR_NEEDMOREPARAMS;
    }

    std::string channelName = this->getArgs()[0];
    std::string nickname = this->getArgs()[1];
    std::string comment = this->getTrailor();

    Channel *channel = this->getServer().getChannel(channelName);
    if (!channel) {
        return ERR_NOSUCHCHANNEL;
    }

    if (!channel->isOperator(this->getClient())) {
        return ERR_CHANOPRIVSNEEDED;
    }
	
	Client *client = this->getServer().getClientByNickname(nickname);
	if (!client) {
    	return ERR_NOSUCHNICK;
    }
	
    if (!channel->isClientPresent(*client)) {
        return ERR_NOTONCHANNEL;
    }

    std::string kickMessage =	":" + this->getClient().getNicknameOrUsername(true) +
								" " + this->getName() +
								" " + channelName + 
								" " + nickname;

	if (!this->_trailor.empty()) {
    	kickMessage += " :" + this->_trailor;
	}
								
    channel->sendMessageToAll(kickMessage);
    
	channel->delUser(*client);

    return ERR_NONE;
}

int Command::MODE() {
	return(ERR_NONE);

}

int	Command::NICK() {
	bool useNickname = true;
	if (this->_args.empty() || this->_args[0].empty()) {
		return (ERR_NONICKNAMEGIVEN);
	} else if (!isValidNickname()) {
		return (ERR_ERRONEUSNICKNAME);
	} else if (!isNicknameOrUsernameAvailable(useNickname)) {
		return (ERR_NICKNAMEINUSE);
	}
	this->_client.setNickname(this->_args[0]);
	this->_server.sendMessage(this->_client,
	"NICK updated successfully: " + this->_args[0]);
	return(ERR_NONE);
}

int Command::USER() {
	bool useNickname = false;
	if (this->_client.isRegister()) {
		return (ERR_ALREADYREGISTRED);
	}
	if (this->_args.empty() || this->_args[0].empty() || this->_trailor.empty()) {
		return (ERR_NEEDMOREPARAMS);
	} else if (!isValidNickname()) {
		return (ERR_ERRONEUSNICKNAME);
	} else if (!isNicknameOrUsernameAvailable(useNickname)) {
		return (ERR_NICKNAMEINUSE);
	} else if (!isValidRealName()) {
		return (ERR_REALNAME);
	}
	this->_client.setRealName(this->_trailor);
	this->_client.setUsername(this->_args[0]);
	this->_client.setRegister();
	this->_server.sendMessage(this->_client,
	"User successfully register: " + this->_args[0]);
	
	return(ERR_NONE);
}

int	Command::PASS() {
	if (this->_args.empty() || this->_args[0].empty()) {
		return (ERR_NEEDMOREPARAMS);
	}
	if (!isValidPassword()) {
		return (ERR_PASSFORMAT);
	}
	if (this->_args[0] == this->_server.getPassword()) {
		this->_client.setPassRegister();
	} else {
		return (ERR_PASSWRONG);
	}
	this->_server.sendMessage(this->_client, "Password match, Welcome to irc server");
	return (ERR_NONE);
}

int Command::OPER() {
	return(ERR_NONE);

}

int Command::PART() {
/*   Parameters: <channel>{,<channel>}	*/
    if (this->getArgs().size() < 1) {
        return ERR_NEEDMOREPARAMS;
    }

    std::vector<std::string> channels = ft_split(this->getArgs()[0], ",");    
	
    for (size_t i = 0; i < channels.size(); ++i) {
        std::string const &channelName = channels[i];
		
      	Channel *channel = this->getServer().getChannel(channelName);
		Client &client = this->getClient();
		
		if (!channel) {
        	return ERR_NOSUCHCHANNEL;
        } else if (!channel->isClientPresent(client)) {
        	return ERR_NOTONCHANNEL;
        }

		channel->delUser(client);
		
		if (channel->getCount() < 1) {
			this->getServer().delChannel((channelName));
		}
		
		std::string partMessage =	":" + this->getClient().getNicknameOrUsername(true) +
									" " + this->getName() + 
									" " + channelName;
								
		channel->sendMessageToAll(partMessage);
	}
	
	return ERR_NONE;
}

int Command::PONG() {
	return(ERR_NONE);
}

int Command::PRIVMSG() {
	return(ERR_NONE);

}

int Command::TOPIC() {
    /* Parameters: <channel> [<topic>] */
    if (this->getArgs().size() < 1) {
        return ERR_NEEDMOREPARAMS;
    }

    std::string channelName = this->getArgs()[0];
    Channel *channel = this->getServer().getChannel(channelName);

    if (!channel) {
        return ERR_NOTONCHANNEL;
    }

	if (this->getTrailor().empty()) {
		if (channel->getTopic().empty()) {
			channel->RPL_NOTOPIC(this->getClient());
		} else {
			channel->RPL_TOPIC(this->getClient());
		}
	} else {
		if (!channel->isOperator(this->getClient())) {
			return ERR_CHANOPRIVSNEEDED;
		}
		
        std::string newTopic = this->getTrailor();
        channel->setTopic(newTopic);

        std::string topicMessage = ":" + this->getClient().getNicknameOrUsername(true) +
                                   " " + this->getName() +
								   " " + channelName + 
								   " :" + newTopic;
       
	    channel->sendMessageToAll(topicMessage);
    }

    return ERR_NONE;
}

int Command::NAMES() {
/*	Parameters: [<channel>{,<channel>}]	*/
    if (this->getArgs().empty()) {
        for (std::map<std::string, Channel>::const_iterator it = this->getServer().getChannels().begin();
		 	it != this->getServer().getChannels().end(); ++it) {
            Channel const &channel = it->second;

            if (channel.isClientPresent(this->getClient())) {
                channel.RPL_NAMREPLY(this->getClient());
            }
        }
        return ERR_NONE;
    }

    for (size_t i = 0; i < this->getArgs().size(); ++i) {
        std::string const &channelName = this->getArgs()[i];
        Channel* channel = this->getServer().getChannel(channelName);

        if (!channel) {
            return ERR_NOSUCHCHANNEL;
        }

        if (channel->isClientPresent(this->getClient())) {
            channel->RPL_NAMREPLY(this->getClient());
        }
    }

    return ERR_NONE;
}

/* ************************************************************************** */

bool Command::isValidNickname() const {
	std::string nickname = this->_args[0];
	char firstChar = nickname[0];
	if (this->_args[0].size() > 9) {
		return (false);
	}
	
	// Vérifie que le pseudonyme commence par une lettre ou un caractère spécial
	if (!(isalpha(firstChar) || strchr("[\\]^_{|}", firstChar) != 0)) {
		return false;
	}

    // Vérifie que le reste du pseudonyme est composé de caractères valides
    for (size_t i = 1; i < nickname.length(); ++i) {
        char ch = nickname[i];
        if (!(isalnum(ch) || strchr("-.", ch) != 0 || strchr("[\\]^_{|}", ch) != 0)) {
            return false;
        }
    }

	return (true);
}

bool	Command::isNicknameOrUsernameAvailable(bool useNickname) const {
	// Vérifie que le pseudonyme n'est pas deja utilisé par un autre utilisateur
	// pour le moment un client ne peut pas se reatribuer le meme username
	std::string name = this->_args[0];

	std::map<const int, Client> clients = this->_server.getClients();
	for (std::map<const int, Client>::iterator it = clients.begin();
		it != clients.end(); it++) {
		if (!it->second.getNicknameOrUsername(useNickname).empty() &&
		it->second.getNicknameOrUsername(useNickname) == name) {
			return (false);
		}
	}
	return (true);
}

bool	Command::isValidRealName() const {
	if (this->_trailor.size() > 25) {
		return (false);
	}
	for (size_t i = 0; i < this->_trailor.size(); i++) {
		if (!isalnum(this->_trailor[i]) && !std::isspace(this->_trailor[i])) {
			return (false);
		}
	}
	return (true);
	
}

bool Command::isValidPassword() const {
	std::string password = this->_args[0];
	if (password.size() > 25) {
		return (false);
	}
	for (size_t i = 0; i < password.size(); i++) {
		if (!isalnum(password[i])) {
			return (false);
		}
	}
	return (true);
}