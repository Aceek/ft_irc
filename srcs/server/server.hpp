/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 14:21:48 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/13 23:25:12 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "../../include.hpp"

class Client;
class Channel;

#define MAX_COMMAND_SIZE 512

extern bool	serverShutdown;
typedef std::map<const int, Client> ClientMap;
typedef std::map<std::string, Channel> ChannelMap;

class Server {
	public:
		Server(int port, std::string password);
		Server(/* args */);
		~Server();
			
		void	addToPoll(int fd, short events);
		void	routine();
		bool	processCommand(const int &clientFd);
		void	removeClient(const int clientFd);
		void	removeClients();
		void	addClientsToPoll();
		int		acceptClient();
		void	verifyMessageSend(const int clientfd);
		void	routinePOLLIN(std::vector<struct pollfd>::iterator &pollfdIt);

		void	sendMessage(const int clientFd,
				const std::string &message) const;

		/*server_accessors*/
		std::string			getErrorMessage(int errorCode);
		const std::string	&getPassword() const;
		Client 				*getClientByNickname(std::string const &nickname);
		const ClientMap		&getClients() const;
		Channel				*getChannel(std::string const &channelName);
		const ChannelMap	&getChannels();
		void				setClientToRemove(const int clientFd);
		void				setMessageQueue(const int clientfd,
							const std::string &message);

		/*server_operator*/
		void	grantOperatorStatus(int clientFd);
		void 	revokeOperatorStatus(int clientFd);
		bool 	isOperator(int clientFd) const;

		/*server_channel*/
		void	addChannel(std::string const &channelName);
		void	delChannel(std::string const &channelName);
		void 	printAllChannels(void);
		
		/*server_utlis*/
		
	private:
		int 									_port;
		std::string								_password;
		int										_serverFd;
		struct sockaddr_in						_serverAdress;
		std::vector<struct pollfd>				_fds; // Stockez les FD et les evenements associés
		std::map<const int, Client> 			_clients;
		std::vector<int>						_clientsToRemove;
		std::vector<int>						_clientsToAdd;
		std::set<int> 							_operatorClients;
		std::map<std::string, Channel>			_channels;
		std::map<int, std::deque<std::string> >	_messageQueue;

		
};

#endif // SERVER_HPP
