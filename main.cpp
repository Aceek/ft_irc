/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 15:04:29 by ilinhard          #+#    #+#             */
/*   Updated: 2023/10/14 17:27:04 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

int	main() {
	
	try {
		Server test(6138);
		test.routine();
	} catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	
}