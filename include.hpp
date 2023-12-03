/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 17:22:03 by ilinhard          #+#    #+#             */
/*   Updated: 2023/12/03 01:05:21 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_HPP_
#define INCLUDE_HPP_

enum ErrorCode {
  ERR_NONE = 0,
  ERR_NONICKNAMEGIVEN = 431,
  ERR_ERRONEUSNICKNAME = 432,
  ERR_NICKNAMEINUSE = 433,
  ERR_NEEDMOREPARAMS = 461,
  ERR_ALREADYREGISTERED = 462,
  ERR_PASSWDMISMATCH = 464,
  RPL_PONG = 611,
};

enum messageServer {
  SERVER_CLOSING,
  SERVER_DELCLIENT,
  ERR_SERVER_ACCEPTCLIENT,
  SERVER_NEWCLIENT,
  ERR_BIND,
  ERR_POLL,
  ERR_SEND,
  ERR_OPEN_FD
};

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>

#include <algorithm>
#include <cctype>
#include <cerrno>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "srcs/bot/bot.hpp"
#include "srcs/channel/channel.hpp"
#include "srcs/client/client.hpp"
#include "srcs/command/command.hpp"
#include "srcs/server/server.hpp"
#include "srcs/serverReply/serverReply.hpp"
#include "srcs/utils/utils.hpp"

#endif  // INCLUDE_HPP_
