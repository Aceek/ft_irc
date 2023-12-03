/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot_accessors.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 00:47:55 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/12/03 01:34:03 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/bot/bot.hpp"

std::string Bot::getFilename(void) const { return (this->_filename); }

void Bot::setFilename(std::string filename) {
  this->_filename = filename;
  this->_forbiddenWords.clear();
}

std::string Bot::getForbiddenWord(const std::string& message) const {
  std::istringstream iss(message);
  std::string word;

  while (iss >> word) {
    std::transform(word.begin(), word.end(), word.begin(), toLowerCase);
    for (std::set<std::string>::const_iterator it = this->_forbiddenWords.begin();
      it != this->_forbiddenWords.end(); it++) {
      std::string lowerForbiddenWord = *it;
      std::transform(lowerForbiddenWord.begin(), lowerForbiddenWord.end(),
        lowerForbiddenWord.begin(), toLowerCase);
      if (strcmp(lowerForbiddenWord.c_str(), word.c_str()) == 0) {
        if (word.length() == 1) {
          return ("*");
        } else if (word.length() == 2) {
          return (word.substr(0, 1) + "*");
        } else {
          return word.substr(0, 1)
            + std::string(word.length() - 2, '*')
            + word.substr(word.length() - 1, 1);
        }
      }
    }
  }
  return ("");
}

void Bot::setName(const std::string& name) { this->_name = name; }

std::string const &Bot::getName(void) const { return this->_name; }