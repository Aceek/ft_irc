/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 15:04:29 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/13 05:44:43 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.hpp"

bool serverShutdown = false;

void handleCtrlC(int signal) {
	(void)signal;

	serverShutdown = true;
}

int	main(int ac, char **av) {
	
	if (ac != 3 || !av[1] || !av[2]) {
		std::cerr <<
		"Error: format is : ./ft_irc [ports] [password]" << std::endl;
		return (-1); // erreur a definir
	}
	
	std::signal(SIGINT, handleCtrlC);
	try {
		Server test(atoi(av[1]), av[2]);
		test.routine();
	} catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
}
