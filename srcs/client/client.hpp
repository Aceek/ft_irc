/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:36:06 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/13 04:45:55 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../include.hpp"

class Server;

#define BUFFER_SIZE 512

class Client {
	public:
		Client();
		Client(int fd, const struct sockaddr_in &addr);
		~Client();

		void	clearCommand();
		void	addToCommand(const char *buffer);
		void	printCommand(); // test function
		bool	verifyCommand();

		/*client_accessors*/
		int							getClientFd() const;
		const struct sockaddr_in	&getClientAddress() const;
		const std::string			&getClientCommand() const;
		const std::string			&getNicknameOrUsername(bool useNickname) const;
		void						setNickname(std::string const &nickname);
		void						setUsername(std::string const &username);
		void						setRealName(std::string const &realName);
		void						setPassRegister();
		void						setRegister();
		
		/*client_utils*/
		bool	isRegister() const;
		bool	isPasswordSetUp() const;
		
	private:
		int					_clientFd;
		struct sockaddr_in	_clientAdress;
		std::string			_nickname;
		std::string			_command;
		std::string			_username;
		std::string			_realName;
		bool				_passRegister;
		bool				_register;
};

#endif  // CLIENT_HPP