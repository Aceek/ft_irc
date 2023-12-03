/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot_utils.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 00:49:30 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/12/03 00:51:24 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/bot/bot.hpp"

bool Bot::isDirectory(void) const {
  struct stat statbuf;

  if (stat(this->_filename.c_str(), &statbuf) != 0) return (false);
  return (S_ISDIR(statbuf.st_mode));
}

bool Bot::isMessageForbidden(const std::string& message) const {
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
        return (true);
      }
    }
  }
  return (false);
}

bool Bot::isValidWord(const std::string &word) const {
  if (word.empty()) return (false);
  for (std::string::const_iterator it = word.begin(); it != word.end(); ++it) {
    if (!std::isalnum(*it)) return (false);
  }
  return (true);
}