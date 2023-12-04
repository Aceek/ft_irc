/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utlis.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 04:13:48 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/12/04 06:28:15 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/command/command.hpp"

bool Command::isValidNicknameorUsername() const {
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
    if (!(isalnum(ch) || strchr("-.", ch) != 0 ||
          strchr("[\\]^_{|}", ch) != 0)) {
      return false;
    }
  }

  return (true);
}

bool Command::isNicknameAvailable(bool useNickname) const {
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

bool Command::isValidPassword(std::string const &key) const {
  std::string password = key;
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

bool Command::isValidChannelName(std::string const &channelName) const {
  return !channelName.empty() && channelName[0] == '#';
}
bool Command::isValidChannelKey(Channel const *channel,
                                std::string const &key) const {
  if (channel->getKey().empty()) {
    return true;
  }
  return key == channel->getKey();
}

bool Command::checkInviteOnlyAndNotInvited(Channel const *channel) const {
  return channel->getInviteOnly() && !channel->isClientInvited(&this->_client);
}

bool Command::checkInviteOnlyAndNotOperator(Channel const *channel) const {
  return channel->getInviteOnly() && !channel->isOperator(&this->_client);
}

bool Command::checkChannelFull(Channel const *channel) const {
  return channel->getCount() >= channel->getUserLimit() &&
         channel->getUserLimit() >= 0;
}

bool Command::checkTopicRestriction(Channel const *channel) const {
  if (channel->getTopicRestricted() && !channel->isOperator(&this->_client)) {
    return false;
  }
  return true;
}

void Command::addUserToChannel(Channel *channel) const {
  channel->addUser(&this->_client, channel->isOperator(&this->_client));
}

Channel *Command::getOrCreateChannel(std::string const &channelName,
                                     std::string const &key) {
  Channel *channel = this->_server.getChannel(channelName);
  if (!channel) {
    this->_server.addChannel(channelName);
    channel = this->_server.getChannel(channelName);
    if (!key.empty()) {
      channel->setKey(key);
    }
  }
  return channel;
}

bool Command::isValidMode(const std::string &str) {
  if (str.empty() || (str[0] != '+' && str[0] != '-')) {
    return false;
  }
  for (size_t i = 1; i < str.length(); ++i) {
    if (!(std::isalpha(str[i]))) {
      return false;
    }
  }
  return true;
}

bool Command::isRecognizedMode(const std::string &str) {
  if (str.empty() || (str[0] != '+' && str[0] != '-')) {
    return false;
  }

  const char validModes[] = {'i', 't', 'k', 'o', 'l'};
  for (size_t i = 1; i < str.length(); ++i) {
    if (std::find(validModes, validModes + sizeof(validModes), str[i]) ==
        validModes + sizeof(validModes)) {
      return false;
    }
  }
  return true;
}

bool Command::botMessageCheck(Command &cmd) {	
  Bot *bot = cmd.getTargetChannel()->getBot();
  std::string const &msg = cmd.getTrailor();
  if (bot->isMessageForbidden(msg)) {
    
    std::string const &forbiddenWord = bot->getForbiddenWord(msg);
    cmd.setForbiddenWord(forbiddenWord);
    cmd.setTargetClient(&cmd.getClient());

    cmd.getServer().getServerReply()->KICKBOT(cmd, cmd.getClient());
    cmd.getServer().getServerReply()->KICKBOT(cmd, *cmd.getTargetChannel());
    
    cmd.getTargetChannel()->delUser(cmd.getTargetClient());
	
    return true;
  }

  return false;
}
