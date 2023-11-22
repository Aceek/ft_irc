/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveroutput.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 08:55:40 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/22 09:12:03 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serverReply.hpp"


void	serverReply::printServerInput(const std::string &message) const {
	std::cout << message << std::endl;
}


void serverReply::displayClientCommand(const std::string& command, const Client& client) const {
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string RESET = "\033[0m";
	std::string nickName = client.getNicknameOrUsername(true);
	if (nickName.empty()) {
		std::ostringstream ss;
		ss << client.getClientFd();
		nickName = ss.str();
	}

    std::cout << GREEN << "Command from [" << nickName << "]: " 
              << RED << command << RESET << std::endl;
}