/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 04:13:48 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/13 04:14:14 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

bool Command::isValidNickname() const {
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
        if (!(isalnum(ch) || strchr("-.", ch) != 0 || strchr("[\\]^_{|}", ch) != 0)) {
            return false;
        }
    }

	return (true);
}

bool	Command::isNicknameOrUsernameAvailable(bool useNickname) const {
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

bool	Command::isValidRealName() const {
	if (this->_trailor.size() > 25) {
		return (false);
	}
	for (size_t i = 0; i < this->_trailor.size(); i++) {
		if (!isalnum(this->_trailor[i]) && !std::isspace(this->_trailor[i])) {
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