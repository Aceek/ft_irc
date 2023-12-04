/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 15:04:29 by ilinhard          #+#    #+#             */
/*   Updated: 2023/12/04 20:36:49 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.hpp"

bool serverShutdown = false;

void handleCtrlC(int signal) {
  (void)signal;

  serverShutdown = true;
}

int main(int ac, char** av) {
  if (ac != 3 || !av[1] || !av[2]) {
    std::cerr << "Error: format is : ./ircserv <ports> <password>" << std::endl;
    return (-1);
  }
  
  int ports = convertToInt(av[1]);
  if (ports < 1 || ports > 65535) {
    std::cerr << "Error: format is : ./ircserv <0 - 65535> <password>" << std::endl;
    return (-1);
  }

  std::string passw = av[2];

  if (passw.empty() || passw.size() > 25) {
    std::cerr << "Error: format is : ./ircserv <ports> <pass between 1 and 25 char>" << std::endl;
	return (-1);
  }

  std::signal(SIGINT, handleCtrlC);
  try {
    Server test(ports, av[2]);
    test.routine();
  } catch (const std::exception& e) {
  }
}

