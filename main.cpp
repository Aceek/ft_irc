/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 15:04:29 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/02 03:23:04 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
// #include "command.hpp"
// #include "utils.hpp"

int	main() {
	
	try {
		Server test(6138);
		test.routine();
	} catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	
}

// int main() {
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
// // Command myCommand(":prefix COmMAND arg1 arg2 :This is trailing", NULL);

// // myCommand.printArguments();

// }