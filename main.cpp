/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 15:04:29 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/02 01:18:13 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "utils.hpp"

int	main() {
	
	try {
		Server test(6138);
		test.routine();
	} catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	
}

// int main() {
//     std::string input = "This is a sample string";
//     std::vector<std::string> tokens;
//     std::string delimiter = " ";

//     tokens = ft_split(input, delimiter);

//     for (size_t i = 0; i < tokens.size(); ++i) {
//         std::cout << tokens[i] << std::endl;
//     }

//     return 0;
// }