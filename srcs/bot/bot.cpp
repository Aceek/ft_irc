/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlouvrie <rlouvrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:21:15 by rlouvrie          #+#    #+#             */
/*   Updated: 2023/12/02 00:02:15 by rlouvrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/bot/bot.hpp"

Bot::Bot(void) : _filename("srcs/bot/forbidden_words.txt") {}

Bot::Bot(const Bot &cp) : _filename(cp.getFilename()) {}

Bot &Bot::operator=(const Bot &rhs) {
  if (this != &rhs) {
    this->setFilename(rhs.getFilename());
  }
  return (*this);
}

Bot::~Bot() {}

void Bot::loadFile(void) {
  std::ifstream file(this->_filename.c_str());
  std::string word;
  int line;

  if (!file.is_open()) {
    switch (errno) {
      case ENOENT:
        throw Bot::FileDoesNotExistException();
      case EACCES:
        throw Bot::PermissionDeniedException();
      default:
        throw Bot::UnknownFileExecption();
    }
  }
  if (isDirectory()) throw Bot::DirectoryNotFileException();
  line = 1;
  while (std::getline(file, word)) {
    if (!word.empty() && this->isValidWord(word)) {
      this->_forbiddenWords.insert(word);
    } else if (!word.empty()) {
      std::cerr << "Bot: Line " << line << ": '" << word
                << "' is not included in the list (typo error).\n";
    }
    line++;
  }
}

std::string Bot::getFilename(void) const { return (this->_filename); }

bool Bot::isDirectory(void) const {
  struct stat statbuf;

  if (stat(this->_filename.c_str(), &statbuf) != 0) return (false);
  return (S_ISDIR(statbuf.st_mode));
}

bool Bot::isValidWord(const std::string &word) const {
  if (word.empty()) return (false);
  for (std::string::const_iterator it = word.begin(); it != word.end(); ++it) {
    if (!std::isalnum(*it)) return (false);
  }
  return (true);
}

void Bot::setFilename(std::string filename) {
  this->_filename = filename;
  this->_forbiddenWords.clear();
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

void Bot::init(void) {
  try {
    this->loadFile();
  } catch (const std::exception &e) {
    std::cerr
      << "Bot: Exception caught: "
      << e.what()
      << "\n";
  }
}

std::string Bot::getForbiddenWord(const std::string& message) {
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