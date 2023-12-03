/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerReply.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 21:25:19 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/12/03 21:25:35 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/serverReply/serverReply.hpp"

serverReply::serverReply(Server *server) : _server(*server) {}

serverReply::~serverReply() {}