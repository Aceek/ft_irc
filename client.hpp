/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:36:06 by ilinhard          #+#    #+#             */
/*   Updated: 2023/10/14 17:26:23 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "include.hpp"

class Server;

class Client {
private:
	int							_clientFd;
	struct sockaddr_in			_clientAdress;
	std::string					_username;

public:
	Client();
	Client(int fd, const struct sockaddr_in &addr);
	~Client();

	int	getClientFd() const;
	const struct sockaddr_in& getClientAddress() const;
};

#endif  // CLIENT_HPP