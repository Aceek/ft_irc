/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlouvrie <rlouvrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 01:16:57 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/15 04:15:53 by rlouvrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include "../../include.hpp"

std::vector<std::string>	ft_split(std::string const& str, std::string const& del);
void 						toUpperCase(std::string &str);
char						toLowerCase(char c);

#endif