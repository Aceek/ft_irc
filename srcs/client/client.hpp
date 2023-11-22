/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:36:06 by ilinhard          #+#    #+#             */
/*   Updated: 2023/11/22 09:23:28 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../../include.hpp"

class Server;

#define BUFFER_SIZE 512

class Client {
	public:
		Client();
		Client(int fd, const struct sockaddr_in &addr);
		~Client();

		void	clearCommand();
		void	addToCommand(const std::string &buffer);
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
		void						setUserRegister();
		void						setNickRegister();
		std::string					getPrefix(void) const;

		/*client_utils*/
		bool	isUserRegister() const;
		bool	isNickRegister() const;
		bool	isPasswordSetUp() const;
		
	private:
		int					_clientFd;
		struct sockaddr_in	_clientAdress;
		std::string			_nickname;
		std::string			_command;
		std::string			_username;
		std::string			_realName;
		std::string			_hostname;
		bool				_passRegister;
		bool				_userRegister;
		bool				_nickRegister;
};

#endif  // CLIENT_HPP