/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:19:43 by rlouvrie          #+#    #+#             */
/*   Updated: 2023/11/27 20:27:42 by ilinhard         ###   ########.fr       */
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
  void setFilename(std::string filename);
  void loadFile(void);
  int activate(void);
  class FileDoesNotExistException : public std::exception {
    const char* what() const throw() { return ("No such file or directory"); }
  };
  class PermissionDeniedException : public std::exception {
    const char* what() const throw() { return ("Permission denied"); }
  };
  class UnknownFileExecption : public std::exception {
    const char* what() const throw() { return ("Unknown"); }
  };
  class DirectoryNotFileException : public std::exception {
    const char* what() const throw() { return ("Is a directory"); }
  };

 private:
  std::set<std::string> _forbiddenWords;
  std::string _filename;
  bool _isOn;
};
#endif  // SRCS_BOT_BOT_HPP_
