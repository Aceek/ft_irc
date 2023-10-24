/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 14:21:48 by ilinhard          #+#    #+#             */
/*   Updated: 2023/10/24 05:27:00 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "include.hpp"

class Client;

#define MAX_COMMAND_SIZE 512

class Server {
private:
	int 						_port;
	int							_serverFd;
	struct sockaddr_in			_serverAdress;
	std::vector<struct pollfd>	_fds; // Stockez les FD et les evenements associés
	std::map<const int, Client> _clients;
public:
	Server(int port);
	Server(/* args */);
	~Server();

	void	addToPoll(int fd, short events);
	void	routine();
	int		acceptClient();
	void	processComand(const int &clientFd);
};

#endif // SERVER_HPP
