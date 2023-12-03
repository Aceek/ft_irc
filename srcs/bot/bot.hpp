/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:19:43 by rlouvrie          #+#    #+#             */
/*   Updated: 2023/12/03 05:13:47 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include.hpp"

#ifndef SRCS_BOT_BOT_HPP_
#define SRCS_BOT_BOT_HPP_

class Bot {
 public:
  Bot(void);
  Bot(const Bot& cp);
  Bot& operator=(const Bot& rhs);
  ~Bot();

  void init(void);
  void loadFile(void);
  
/*bot_accessors*/
  void setFilename(std::string filename);
  std::string getFilename(void) const;
  std::string getForbiddenWord(const std::string& message) const;
  void setName(const std::string& name);
  std::string const &getName(void) const;
  
/*bot_utils*/
  bool isDirectory(void) const;
  bool isValidWord(const std::string& word) const;
  bool isMessageForbidden(const std::string& message) const;


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
  std::string _filename;
  std::string _name;
  std::set<std::string> _forbiddenWords;
};
#endif  // SRCS_BOT_BOT_HPP_
