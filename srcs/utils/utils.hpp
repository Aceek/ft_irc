/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 01:16:57 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/28 06:04:45 by pbeheyt          ###   ########.fr       */
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
std::string joinWithSpace(const std::map<char, std::string>& elements);
int convertToInt(const std::string& str);

#endif  // SRCS_UTILS_UTILS_HPP_
