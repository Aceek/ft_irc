/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 01:16:57 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/28 03:39:38 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SRCS_UTILS_UTILS_HPP_
#define SRCS_UTILS_UTILS_HPP_

#include <vector>
#include <string>
#include "../../include.hpp"

std::vector<std::string> ft_split(std::string const& str,
                                  std::string const& del);
void toUpperCase(std::string* str);
char toLowerCase(char c);
std::string joinWithSpace(const std::vector<std::string>& elements);

#endif  // SRCS_UTILS_UTILS_HPP_
