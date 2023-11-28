/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 01:03:06 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/28 06:04:35 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <string>
#include "srcs/utils/utils.hpp"

std::vector<std::string> ft_split(std::string const &str,
                                  std::string const &del) {
  size_t start = 0;
  size_t end = str.find(del);
  std::vector<std::string> tab;

  while (end != std::string::npos) {
    tab.push_back(str.substr(start, end - start));
    start = end + del.size();
    end = str.find(del, start);
  }

  tab.push_back(str.substr(start));

  return tab;
}

void toUpperCase(std::string *str) {
  for (std::string::iterator it = str->begin(); it != str->end(); ++it) {
    *it = std::toupper(*it);
  }
}

char toLowerCase(char c) { return std::tolower(static_cast<unsigned char>(c)); }

std::string joinWithSpace(const std::vector<std::string>& elements) {
  std::ostringstream oss;
  for (std::vector<std::string>::const_iterator it = elements.begin();
       it != elements.end(); ++it) {
    if (it != elements.begin()) {
      oss << ' ';
    }
    oss << *it;
  }
  return oss.str();
}

std::string joinWithSpace(const std::map<char, std::string>& elements) {
  std::ostringstream oss;
  for (std::map<char, std::string>::const_iterator it = elements.begin();
       it != elements.end(); ++it) {
    if (it != elements.begin()) {
      oss << ' ';
    }
    oss << it->first << ':' << it->second;
  }
  return oss.str();
}

int convertToInt(const std::string& str) {
    char* endPtr;
    long result = strtol(str.c_str(), &endPtr, 10);
    return (*endPtr == '\0') ? static_cast<int>(result) : -1;
}