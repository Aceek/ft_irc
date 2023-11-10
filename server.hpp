/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 14:21:48 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/10 04:29:39 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "include.hpp"

class Client;
class Channel;

#define MAX_COMMAND_SIZE 512

typedef std::map<const int, Client> ClientMap;

class Server {
private:
	int 						_port;
	std::string					_password;
	int							_serverFd;
	struct sockaddr_in			_serverAdress;
	std::vector<struct pollfd>	_fds; // Stockez les FD et les evenements associés
	std::map<const int, Client> _clients;

	std::map<std::string, Channel> _channels;
	
public:
						Server(int port, std::string password);
						Server(/* args */);
						~Server();
		
	void				addToPoll(int fd, short events);
	void				routine();
	void				processComand(const int &clientFd);
	void				addChannel(std::string const &channelName);
	void				delChannel(std::string const &channelName);
	void 				printAllChannels(void);
	void				sendMessage(const Client &client,
						const std::string &message) const;
	int					acceptClient();

	Channel				*getChannel(std::string const &channelName);
	const ClientMap		&getClients() const;
	const std::string	&getPassword() const;
	std::string			getErrorMessage(int errorCode);



};

#endif // SERVER_HPP
