/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverReply.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 10:51:10 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/18 11:43:15 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serverReply.hpp"

serverReply::serverReply() {}
serverReply::serverReply(const Server *server) : _server(server) {}

serverReply::~serverReply() {}
