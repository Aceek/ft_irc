/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 23:22:42 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/02 03:22:23 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "client.hpp"
#include "utils.hpp"

#include <string>
#include <vector>

class Command {
	public:
		Command(void);
		Command(std::string const &line, Client *user);
		Command(Command const &rhs);
		Command &operator=(Command const &rhs);
		~Command(void);
	
	    void printArguments(void) const;

	private:
		std::string					_prefix;
		std::string					_name;
		std::vector<std::string>	_args;
		std::string					_trailing;

		Client	*_client;
};

#endif