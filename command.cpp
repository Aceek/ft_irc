/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 23:22:45 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/12 07:27:54 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

// Command::Command(void) {} (pas de constructeur par default pour ref client)

Command::Command(std::string const &line, Client &client, Server &server) : 
	_client(client),
	_server(server) {
	initCommandsMap();
	
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

void Command::initCommandsMap(void) {
    this->_commands["NICK"] = CommandInfo(&Command::NICK, "<nickname>");
    this->_commands["USER"] = CommandInfo(&Command::USER, "<username> <hostname> <servername> <realname>");
    this->_commands["PASS"] = CommandInfo(&Command::PASS, "<password>");
    this->_commands["INVITE"] = CommandInfo(&Command::INVITE, "<nickname> <channel>");
    this->_commands["JOIN"] = CommandInfo(&Command::JOIN, "<channel>{,<channel>} [<key>{,<key>}]");
    this->_commands["KICK"] = CommandInfo(&Command::KICK, "<channel> <user> [<comment>]");
    this->_commands["MODE"] = CommandInfo(&Command::MODE, "<channel> <+/-modes> [parameters]");
    this->_commands["OPER"] = CommandInfo(&Command::OPER, "<user> <password>");
    this->_commands["PART"] = CommandInfo(&Command::PART, "<channel>{,<channel>}");
    this->_commands["PONG"] = CommandInfo(&Command::PONG, "<server>");
    this->_commands["PRIVMSG"] = CommandInfo(&Command::PRIVMSG, "<receiver>{,<receiver>} <text to be sent>");
    this->_commands["TOPIC"] = CommandInfo(&Command::TOPIC, "<channel> [<topic>]");
    this->_commands["NAMES"] = CommandInfo(&Command::NAMES, "[<channel>{,<channel>}]");
    this->_commands["HELP"] = CommandInfo(&Command::HELP, "none");
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
    CommandMap::iterator it = _commands.find(this->_name);
    if (it != _commands.end()) {
        return ((this->*(it->second).func)());
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
    if (this->_args.size() < 2) {
        return ERR_NEEDMOREPARAMS;
    }

    std::string nickname = getArgs()[0];
    std::string channelName = getArgs()[1];

    Channel *channel = this->_server.getChannel(channelName);
    if (!channel) {
        return ERR_NOSUCHCHANNEL;
    }

    if (!channel->isOperator(getClient())) {
        return ERR_CHANOPRIVSNEEDED;
    }

	Client *client = this->_server.getClientByNickname(nickname);
	if (!client) {
    	return ERR_NOSUCHNICK;
    }

	if (channel->isClientPresent(*client)) {
        return ERR_USERONCHANNEL;
    }

	channel->inviteUser(*client);
	
    std::string inviteMessage =	":" + this->_client.getNicknameOrUsername(true) +
                        		" " + this->_name +
								" " + nickname +
								" " + channelName;
								
	channel->sendMessageToAll(inviteMessage);
	this->_server.sendMessage(*client, inviteMessage);

    return ERR_NONE;
}

int Command::JOIN() {
/*   Parameters: <channel>{,<channel>} [<key>{,<key>}]	*/
    if (this->_args.size() < 1) {
        return ERR_NEEDMOREPARAMS;
    }

    std::vector<std::string> channels = ft_split(this->_args[0], ",");
    std::vector<std::string> keys;

    if (this->_args.size() > 1) {
        keys = ft_split(this->_args[1], ",");
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

        Channel *channel = this->_server.getChannel(channelName);
        if (!channel) {
            this->_server.addChannel(channelName);
            channel = this->_server.getChannel(channelName);

            if (!key.empty()) {
                channel->setKey(key);
            }
        } else if (!key.empty() && key != channel->getKey()) {
        	return ERR_BADCHANNELKEY;
        }

		///!!!logique du mdp a implementer

		if (channel->getInviteOnly() && !channel->isClientInvited(this->_client)) {
			return ERR_INVITEONLYCHAN;
		}

		if (channel->getCount() >= channel->getUserLimit() &&
			channel->getUserLimit() >= 0) {
			return ERR_CHANNELISFULL;
		}
		
		channel->addUser(this->_client, 
			this->_server.isOperator(this->_client.getClientFd()));
		
		
		std::string joinMessage =	":" + this->_client.getNicknameOrUsername(true) +
									" " + this->_name + 
									" " + channelName;
								
		channel->sendMessageToAll(joinMessage);
		
		channel->RPL_TOPIC(this->_client);
		channel->RPL_NAMREPLY(this->_client);
		channel->RPL_ENDOFNAMES(this->_client);
    }
	
	return ERR_NONE;
}

int Command::KICK() {
/*   Parameters: <channel> <user> [<comment>]	*/
    if (this->_args.size() < 2) {
        return ERR_NEEDMOREPARAMS;
    }

    std::string channelName = this->_args[0];
    std::string nickname = this->_args[1];
    std::string comment = this->_trailor;

    Channel *channel = this->_server.getChannel(channelName);
    if (!channel) {
        return ERR_NOSUCHCHANNEL;
    }

    if (!channel->isOperator(this->_client)) {
        return ERR_CHANOPRIVSNEEDED;
    }
	
	Client *client = this->_server.getClientByNickname(nickname);
	if (!client) {
    	return ERR_NOSUCHNICK;
    }
	
    if (!channel->isClientPresent(*client)) {
        return ERR_NOTONCHANNEL;
    }

    std::string kickMessage =	":" + this->_client.getNicknameOrUsername(true) +
								" " + this->_name +
								" " + channelName + 
								" " + nickname;

	if (!comment.empty()) {
    	kickMessage += " :" + comment;
	}
								
    channel->sendMessageToAll(kickMessage);
    
	channel->delUser(*client);

    return ERR_NONE;
}

///!!!revoir parsing des modes et parametre???? : atm -> MODE +t +i -k =/= +ti -k
int Command::MODE() {
    /* Parameters: <channel> <+/-modes> [parameters] */
    if (this->_args.size() < 2) {
        return ERR_NEEDMOREPARAMS;
    }

    std::string channelName = this->_args[0];
    Channel* channel = this->_server.getChannel(channelName);

    if (!channel) {
        return ERR_NOSUCHCHANNEL;
    }

    if (!channel->isOperator(this->_client)) {
        return ERR_CHANOPRIVSNEEDED;
    }

	for (std::vector<std::string>::const_iterator it = this->_args.begin() + 1;
		it != this->_args.end(); ++it) {
		char s = (*it)[0];
		char c = (*it)[1];
					std::cout << "s:" << s << std::endl;
					std::cout << "c:" << c << std::endl;

        switch (c) {
            case 'i':
				// Set/unset the channel on invitation only
                if (s == '+') {
					channel->setInviteOnly(true);
					std::cout << "coucou" << std::endl;
				} else if (s == '-') {
					channel->setInviteOnly(false);
				}
                break;
            case 't':
                // Set/unset restrictions on the TOPIC command for channel operators
				if (s == '+') {
					channel->setTopicRestricted(true);
				} else if (s == '-') {
					channel->setTopicRestricted(false);
				}
                break;
            case 'k':
                // Set/unset the channel key (password)
                if (s == '+') {
					if ((++it != this->_args.end())) {
						channel->setKey(*it);
					} else {
						return ERR_NEEDMOREPARAMS;
					}
				} else if (s == '-') {
					channel->setKey("");
				} 
                break;
            case 'o':
                // Give/take operator privilege from a user
				if ((++it != this->_args.end())) {
					Client *client = this->_server.getClientByNickname(*it);
					if (!client) {
						return ERR_NOSUCHNICK;
					}
					if (s == '+') {
						channel->addUser(*client, true);
					}  else if (s == '-') {
						channel->addUser(*client, false);
					}
				} else {
					return ERR_NEEDMOREPARAMS;
				}
                break;
            case 'l':
                // Set/unset the limit of users for the channel
                if (s == '+') {
					if (++it != this->_args.end()) {
						 channel->setUserLimit(atoi((*it).c_str()));
					}  else {
						return ERR_NEEDMOREPARAMS;
					}
				} else if (s == '-') {
					channel->setUserLimit(-1);
				}
                break;
            default:
                return ERR_UNKNOWNMODE;
		}
		
    std::string modeMessage = ":" + this->_client.getNicknameOrUsername(true) +
                              " " + this->_name +
                              " " + channelName +
                              " " + s + c;

    channel->sendMessageToAll(modeMessage);
    }
	
    return ERR_NONE;
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
    /* Parameters: <user> <password> */
    if (this->_args.size() < 2) {
        return ERR_NEEDMOREPARAMS;
    }

    std::string nickname = this->_args[0];
    std::string password = this->_args[1];

    ///!!! should we use nickname or username ???
	Client *client = this->_server.getClientByNickname(nickname);
    if (!client) {
        return ERR_NOSUCHNICK;
    }

    if (password != this->_server.getPassword()) {
        return ERR_PASSWDMISMATCH;
	}

	this->_server.grantOperatorStatus(client->getClientFd());

    this->_server.sendMessage(*client, "You are now an operator");

    return ERR_NONE;
}

int Command::PART() {
/*   Parameters: <channel>{,<channel>}	*/
    if (this->_args.size() < 1) {
        return ERR_NEEDMOREPARAMS;
    }

    std::vector<std::string> channels = ft_split(this->_args[0], ",");    
	
    for (size_t i = 0; i < channels.size(); ++i) {
        std::string const &channelName = channels[i];
		
      	Channel *channel = this->_server.getChannel(channelName);
		
		if (!channel) {
        	return ERR_NOSUCHCHANNEL;
        } else if (!channel->isClientPresent(this->_client)) {
        	return ERR_NOTONCHANNEL;
        }

		channel->delUser(this->_client);
		
		if (channel->getCount() < 1) {
			this->_server.delChannel((channelName));
		}
		
		std::string partMessage =	":" + this->_client.getNicknameOrUsername(true) +
									" " + this->_name + 
									" " + channelName;
								
		channel->sendMessageToAll(partMessage);
	}
	
	return ERR_NONE;
}

int Command::PONG() {
	return(ERR_NONE);
}

int Command::PRIVMSG() {
/*	Parameters: <receiver>{,<receiver>} <text to be sent> */
    if ((this->_args.size() < 2 && this->_trailor.empty()) ||
		(this->_args.size() < 1 )) {
        return ERR_NEEDMOREPARAMS;
    }

    std::vector<std::string> receivers = ft_split(this->_args[0], ",");
    std::string message;
	
	if (this->_args.size() >= 2 && !this->_args[1].empty()) {
		message = this->_args[1];
	}
	if (!this->_trailor.empty()) {
		message += " " + this->_trailor;
	}
	if (message.empty()) {
		return ERR_NOTEXTTOSEND;
	}

	//!!! is it possible to send a message to ourselve ? if so check double output msg
	for (std::vector<std::string>::iterator it = receivers.begin();
		it != receivers.end(); ++it) {
			std::string privmsgMessage = ":" + this->_client.getNicknameOrUsername(true) +
								" " + this->_name +
								" " + *it +
								" :" + message;
			
			if ((*it)[0] == '#') {
				Channel *channel = this->_server.getChannel(*it);
					if (!channel) {
						return ERR_NOSUCHCHANNEL;
					} else if (!channel->isClientPresent(this->_client)) {
						return ERR_CANNOTSENDTOCHAN;
					} else {
						channel->sendMessageToAll(privmsgMessage);
						//!!! not sur if the message should be send back for each receiver
						this->_server.sendMessage(this->_client, privmsgMessage);
					}
			} else {
    			Client *client = this->_server.getClientByNickname(*it);
    				if (!client) {
        				return ERR_NOSUCHNICK;
   					} else {
						this->_server.sendMessage(*client, privmsgMessage);
						//!!! not sur if the message should be send back for each receiver
						this->_server.sendMessage(this->_client, privmsgMessage);
					}
			}
		}
		
    return ERR_NONE;
}

int Command::TOPIC() {
    /* Parameters: <channel> [<topic>] */
    if (this->_args.size() < 1) {
        return ERR_NEEDMOREPARAMS;
    }

    std::string channelName = this->_args[0];
    Channel *channel = this->_server.getChannel(channelName);

    if (!channel) {
        return ERR_NOSUCHCHANNEL;
    }

    if (!channel->isClientPresent(this->_client)) {
        return ERR_NOTONCHANNEL;
    }

	if (channel->getTopicRestricted() && !channel->isOperator(this->_client)) {
		return ERR_CHANOPRIVSNEEDED;
	}

	if (this->_trailor.empty()) {
		if (channel->getTopic().empty()) {
			channel->RPL_NOTOPIC(this->_client);
		} else {
			channel->RPL_TOPIC(this->_client);
		}
	} else {
        std::string newTopic = this->_trailor;
        channel->setTopic(newTopic);

        std::string topicMessage = ":" + this->_client.getNicknameOrUsername(true) +
                                   " " + this->_name +
								   " " + channelName + 
								   " :" + newTopic;
       
	    channel->sendMessageToAll(topicMessage);
    }

    return ERR_NONE;
}

int Command::NAMES() {
/*	Parameters: [<channel>{,<channel>}]	*/
    if (this->_args.empty()) {
        for (std::map<std::string, Channel>::const_iterator it = this->_server.getChannels().begin();
		 	it != this->_server.getChannels().end(); ++it) {
            Channel const &channel = it->second;

            if (channel.isClientPresent(this->_client)) {
                channel.RPL_NAMREPLY(this->_client);
            }
        }
        return ERR_NONE;
    }

    for (size_t i = 0; i < this->_args.size(); ++i) {
        std::string const &channelName = this->_args[i];
        Channel* channel = this->_server.getChannel(channelName);

        if (!channel) {
            return ERR_NOSUCHCHANNEL;
        }

        if (channel->isClientPresent(this->_client)) {
            channel->RPL_NAMREPLY(this->_client);
        }
    }

    return ERR_NONE;
}

int Command::HELP() {
    std::string helpMessage = "Available commands:\r\n";

    for (CommandMap::const_iterator it = _commands.begin(); it != _commands.end(); ++it) {
        helpMessage += it->first + " - Parameters: " + it->second.params + "\r\n";
    }

    this->_server.sendMessage(this->_client, helpMessage);

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