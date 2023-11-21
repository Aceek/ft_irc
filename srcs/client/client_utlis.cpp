/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utlis.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 04:19:46 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/11/21 01:58:48 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

bool	Client::isPasswordSetUp() const {
	return (this->_passRegister);
}

bool	Client::isUserRegister() const {
	return (this->_userRegister);
}

bool	Client::isNickRegister() const {
	return (this->_nickRegister);
}
