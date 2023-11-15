/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlouvrie <rlouvrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:19:43 by rlouvrie          #+#    #+#             */
/*   Updated: 2023/11/15 04:32:53 by rlouvrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
# define BOT_HPP
# include <iostream>
# include <set>
# include <fstream>
# include <stdexcept>
# include <string>
# include <sstream>
# include <algorithm>
# include <cctype>
# include <sys/stat.h>
# include "../utils/utils.hpp"

class Bot
{
	public:
		Bot(void);
		Bot(const Bot &cp);
		Bot	&operator=(const Bot &rhs);
		~Bot();
		std::string	getFilename(void)								const;
		bool		isDirectory(void)								const;
		bool		isValidWord(const std::string &word)			const;
		bool		isMessageForbidden(const std::string& message)	const;
		void		setFilename(std::string filename);
		void		loadFile(void);
		int			activate(void);
		class FileDoesNotExistException : public std::exception
		{
			const char* what() const throw()
			{
				return ("No such file or directory");
			}
		};
		class PermissionDeniedException : public std::exception
		{
			const char* what() const throw()
			{
				return ("Permission denied");
			}
		};
		class UnknownFileExecption : public std::exception
		{
			const char* what() const throw()
			{
				return ("Unknown");
			}
		};
		class DirectoryNotFileException : public std::exception
		{
			const char* what() const throw()
			{
				return ("Is a directory");
			}
		};
	private:
		std::set<std::string>	_forbiddenWords;
		std::string				_filename;
		bool					_isOn;
};
#endif