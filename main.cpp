/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 15:04:29 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/09 17:34:44 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "command.hpp"
#include "utils.hpp"

int	main(int ac, char **av) {
	
	if (ac != 3 || !av[1] || !av[2]) {
		std::cerr <<
		"Error: format is : ./ft_irc [ports] [password]" << std::endl;
		return (-1); // erreur a definir
	}
	
	try {
		Server test(atoi(av[1]), av[2]);
		test.routine();
	} catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
}


// int main() {
// 	try {
// 		Client client;
// 		Server server(6138);

// /*******TEST SPLIT**********/
// //     std::string input = "This is a sample string";
// //     std::vector<std::string> tokens;
// //     std::string delimiter = " ";

// //     tokens = ft_split(input, delimiter);

// //     for (size_t i = 0; i < tokens.size(); ++i) {
// //         std::cout << tokens[i] << std::endl;
// //     }

// //     return 0;

// /*******TEST CMD**********/
// 	// Command myCommand(":prefix TofPIC arg1 arg2 :This is trailing", client);

// 	// myCommand.exec();

// /*******TEST JOIN**********/
// 	Command myCommand(":WiZ JOIN #foo,#bar fubar,foobar", client, server);
// 	Command myCommand2(":WiZ JOIN #zooooo,#bar fubar ", client, server);
// 	// Command myCommand3(":WiZ JOIN #zooooo,&bar fubar ", client, server);
// 	// myCommand.printArgs();
// 	myCommand2.printArgs();
// 	myCommand.exec();
// 	myCommand2.exec();
// 	// myCommand3.exec();

// 	server.printAllChannels();

// 	} catch(const std::exception& e) {
// 		std::cerr << e.what() << '\n';
// 	}
// }