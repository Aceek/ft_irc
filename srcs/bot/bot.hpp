/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlouvrie <rlouvrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:19:43 by rlouvrie          #+#    #+#             */
/*   Updated: 2023/12/02 00:08:07 by rlouvrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SRCS_BOT_BOT_HPP_
#define SRCS_BOT_BOT_HPP_
#include <sys/stat.h>

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <cstring>

#include "../utils/utils.hpp"

class Bot {
 public:
  Bot(void);
  Bot(const Bot& cp);
  Bot& operator=(const Bot& rhs);
  ~Bot();
  std::string getFilename(void) const;
  bool isDirectory(void) const;
  bool isValidWord(const std::string& word) const;
  bool isMessageForbidden(const std::string& message) const;
  std::string getForbiddenWord(const std::string& message);
  void setFilename(std::string filename);
  void loadFile(void);
  void init(void);
  class FileDoesNotExistException : public std::exception {
    const char* what() const throw() { 
      return ("File 'forbidden_words.txt' does not exist."); }
  };
  class PermissionDeniedException : public std::exception {
    const char* what() const throw() { 
      return ("Permission denied to open file 'forbidden_words.txt'."); }
  };
  class UnknownFileExecption : public std::exception {
    const char* what() const throw() { return ("Unknown exception"); }
  };
  class DirectoryNotFileException : public std::exception {
    const char* what() const throw() { return ("Is a directory"); }
  };

 private:
  std::set<std::string> _forbiddenWords;
  std::string _filename;
};
#endif  // SRCS_BOT_BOT_HPP_
