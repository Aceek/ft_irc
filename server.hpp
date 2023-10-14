/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 14:21:48 by ilinhard          #+#    #+#             */
/*   Updated: 2023/10/14 17:23:47 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "include.hpp"

class Client;

class Server {
private:
	int 						_port;
	int							_serverFd;
	struct sockaddr_in			_serverAdress;
	std::vector<struct pollfd>	_fds; // Stockez les FD et les evenements associés
	std::vector<Client>			_clients;
public:
	Server(int port);
	Server(/* args */);
	~Server();

	void	addToPoll(int fd, short events);
	void	routine();
	void	acceptClient();
};

#endif // SERVER_HPP
