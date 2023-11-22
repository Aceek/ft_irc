/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 17:22:03 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/22 07:28:36 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_HPP
#define INCLUDE_HPP

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <fstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <poll.h>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <csignal>
#include <cstdlib>
#include <cstdio>
#include <deque>
#include <cerrno>
#include <algorithm>

#include "srcs/channel/channel.hpp"
#include "srcs/client/client.hpp"
#include "srcs/command/command.hpp"
#include "srcs/serverReply/serverReply.hpp"
#include "srcs/server/server.hpp"
#include "srcs/utils/utils.hpp"

enum ErrorCode {
	ERR_NONE = 0,
	ERR_PASSFORMAT = 2,      // variable perso
	ERR_PASSNEEDED = 3,      // variable perso
	ERR_PASSWRONG = 4,       // variable perso
	ERR_FILEINVALID = 5,
	ERR_NOSUCHNICK = 401,
	ERR_NOSUCHCHANNEL = 403,
	ERR_CANNOTSENDTOCHAN = 404,
	ERR_NOTEXTTOSEND = 412,
	ERR_UNKNOWNCOMMAND = 421,
	ERR_NONICKNAMEGIVEN = 431,
	ERR_ERRONEUSNICKNAME = 432,
	ERR_NICKNAMEINUSE = 433,
	ERR_NICKCOLLISION = 436,
	ERR_NOTONCHANNEL = 442,
	ERR_USERONCHANNEL = 443,
	ERR_NEEDMOREPARAMS = 461,
	ERR_ALREADYREGISTERED = 462,
	ERR_PASSWDMISMATCH = 464,
	ERR_CHANNELISFULL = 471,
	ERR_UNKNOWNMODE = 472,
	ERR_INVITEONLYCHAN = 473,
	ERR_BADCHANNELKEY = 475,
	ERR_BADCHANMASK = 476,
	ERR_CHANOPRIVSNEEDED = 482,
	ERR_UMODEUNKNOWNFLAG = 501,
};

enum messageServer {
	ERR_SERVER_SENDING = 600,
	ERR_SERVER_RECV = 601,
	SERVER_CLOSING = 602,
	SERVER_DELCLIENT = 603,
	ERR_SERVER_ACCEPTCLIENT = 604,
	SERVER_NEWCLIENT = 605,
	ERR_NOENDCARACT = 606,
	ERR_COMMAND_SIZE = 607,
	ERR_BUFFER_SIZE = 608,
	ERR_INVALIDFILEPATH = 609,
	NICK_CHANGE_SUCCESS = 610,
	RPL_PONG = 611,
	

};

#endif // INCLUDE_HPP