/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:24:21 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/13 12:30:13 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLACE_HPP
# define REPLACE_HPP

#include <stdlib.h>
#include <string>
#include <iostream>																// std::cout, std::endl
#include <fstream>																// std::ifstream, std::ofstream

// COLOR CODES
#define BW			"\033[1;37m"
#define BR			"\033[1;31m"
#define BG			"\033[1;32m"
#define BY			"\033[1;33m"
#define RST			"\033[0m"

#define ERR_INPUT	"Error: wrong number of arguments"
#define USAGE		"Usage:\t./replace <file_name> <search> <replace>"

class Replace {

	private:
		std::string	_inFile;
		std::string	_outFile;
		std::string	_search;
		std::string	_replace;
		
	public:
		Replace( std::string filename, std::string search, std::string replace );
		int		myReplace( void );
		~Replace( void );
		
};

#endif