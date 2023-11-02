/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:36:06 by ilinhard          #+#    #+#             */
/*   Updated: 2023/10/24 07:55:04 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "include.hpp"

class Server;

#define BUFFER_SIZE 512

class Client {
private:
	int							_clientFd;
	struct sockaddr_in			_clientAdress;
	std::string					_username;
	std::string					_command;

public:
	Client();
	Client(int fd, const struct sockaddr_in &addr);
	~Client();

	int							getClientFd() const;
	const struct sockaddr_in&	getClientAddress() const;
	const std::string			&getClientCommand() const;
	
	void						addToCommand(const char *buffer);
	void						printCommand(); // test function
	bool						handleCommand();
};

#endif  // CLIENT_HPP