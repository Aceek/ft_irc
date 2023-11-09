/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 17:22:03 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/09 18:18:15 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_HPP
#define INCLUDE_HPP

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <poll.h>
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include <client.hpp>
#include <channel.hpp>
#include <command.hpp>


enum		ErrorCode {
	ERR_NONE = 0,
	ERR_NONICKNAMEGIVEN = 431,
	ERR_ERRONEUSNICKNAME = 432,
	ERR_NICKNAMEINUSE = 433,
	ERR_NICKCOLLISION = 436,
	ERR_NEEDMOREPARAMS = 461,
	ERR_REALNAME = 1, // variable perso
	ERR_PASSFORMAT = 2, // variable perso
	ERR_PASSNEEDED = 3, // variable perso
	ERR_PASSWRONG = 4, // variable perso
	ERR_ALREADYREGISTRED = 462,

};

#endif // INCLUDE_HPP