/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 01:03:06 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/21 15:04:34 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

std::vector<std::string>	ft_split(std::string const &str, std::string const &del) {
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

void toUpperCase(std::string &str) {
	for (std::string::iterator it = str.begin(); it != str.end(); ++it) {
		*it = std::toupper(*it);
	}
}

char toLowerCase(char c) {
	return std::tolower(static_cast<unsigned char>(c));
}
