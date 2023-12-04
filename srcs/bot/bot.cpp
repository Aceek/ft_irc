/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:21:15 by rlouvrie          #+#    #+#             */
/*   Updated: 2023/12/04 01:01:17 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/bot/bot.hpp"

Bot::Bot(void) :
  _filename("config/forbidden_words.txt"),
  _name("channel-bot") {
  init();
}

Bot::Bot(const Bot &cp) : 
  _filename(cp.getFilename()),
  _name(cp._name),
  _forbiddenWords(cp._forbiddenWords) {
  init();
}

Bot &Bot::operator=(const Bot &rhs) {
  if (this != &rhs) {
    this->_forbiddenWords.clear();

    this->_filename = rhs._filename;
    this->_name = rhs._name;
    this->_forbiddenWords = rhs._forbiddenWords;
  }
  return (*this);
}

Bot::~Bot() {}

/* ************************************************************************** */

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
