/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 14:21:48 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/22 09:57:03 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "../../include.hpp"

class Client;
class Channel;
class serverReply;

#define MAX_COMMAND_SIZE 512

extern bool	serverShutdown;
typedef std::map<const int, Client> ClientMap;
typedef std::map<std::string, Channel> ChannelMap;
typedef  std::map<int, std::deque<std::string> >	messages;


class Server {
	public:
		Server(int port, std::string password);
		Server(/* args */);
		~Server();

		void		addToPoll(int fd, short events);
		void		routine();
		bool		processCommand(const int &clientFd);
		void		tryCommand(Client &client);
		void		removeClient(const int clientFd);
		void		removeClients();
		void		addClientsToPoll();
		int			acceptClient();
		void		routinePOLLIN(std::vector<struct pollfd>::iterator &pollfdIt);



		/*server_accessors*/
		const std::string	&getPassword() const;
		serverReply			*getServerReply() const;
		Client 				*getClientByNickname(std::string const &nickname);
		const ClientMap		&getClients() const;
		Channel				*getChannel(std::string const &channelName);
		const ChannelMap	&getChannels();
		std::string			getChannelsNames() const;
		void				setClientToRemove(const int clientFd);

		/*server_channel*/
		void	addChannel(std::string const &channelName);
		void	delChannel(std::string const &channelName);
		void 	sendMessageToChannel(Channel const &channel, std::string const &message);

		/*server_utlis*/
		bool	isChannelPresent(std::string const &channelName);
		void	closingFdClients();

	private:
		int 									_port;
		std::string								_password;
		int										_serverFd;
		struct sockaddr_in						_serverAdress;
		std::vector<struct pollfd>				_fds;
		std::map<const int, Client> 			_clients;
		std::vector<int>						_clientsToRemove;
		std::vector<int>						_clientsToAdd;
		std::map<std::string, Channel>			_channels;
		serverReply								*_serverReply;
};

#endif // SERVER_HPP
