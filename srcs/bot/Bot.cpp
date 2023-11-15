/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlouvrie <rlouvrie@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:21:15 by rlouvrie          #+#    #+#             */
/*   Updated: 2023/11/13 19:24:33 by rlouvrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

Bot::Bot(void) : _filename("blacklist.txt") {}

Bot::Bot(const Bot &cp) : _filename(cp.getFilename()) {}

Bot &Bot::operator=(const Bot &rhs)
{
	if (this != &rhs)
		this->setFilename(rhs.getFilename());
	return (*this);
}

Bot::~Bot() {}

void	Bot::loadFile(void)
{
	std::ifstream	file(this->_filename.c_str());
	std::string		word;
	int				line;

	if (!file.is_open())
	{
		switch (errno) {
        	case ENOENT:
                throw Bot::FileDoesNotExistException();
            case EACCES:
				throw Bot::PermissionDeniedException();
            default:
				throw Bot::UnknownFileExecption();
		}
	}
	if (isDirectory())
		throw Bot::DirectoryNotFileException();
	line = 1;
    while (std::getline(file, word))
	{
    	if (!word.empty() && this->isValidWord(word))
        	this->_forbiddenWords.insert(word);
		else if (!word.empty())
		{
        	std::cerr
				<< "Bot: Line "
				<< line
				<< ": '"
				<< word
				<< "' is not included in the list (typo error).\n";
    	}
		line++;
	}
}

std::string	Bot::getFilename(void) const
{
	return (this->_filename);
}

bool Bot::isDirectory(void) const
{
	struct stat statbuf;

    if (stat(this->_filename.c_str(), &statbuf) != 0)
		return (false);
    return (S_ISDIR(statbuf.st_mode));
}

bool Bot::isValidWord(const std::string &word) const
{
    if (word.empty())
		return (false);
    for (std::string::const_iterator it = word.begin(); it != word.end(); ++it)
	{
		if (!std::isalnum(*it))
            	return (false);
    }
	return (true);
}

void Bot::setFilename(std::string filename)
{
	this->_filename = filename;
	this->_forbiddenWords.clear();
}
