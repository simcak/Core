/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replace.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:43:44 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/13 13:30:54 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Replace.hpp"

static void	input_file_error(std::ifstream &file, std::string _inFile) {
	file.open(_inFile);
	if (!file.is_open()) {
		std::cout << BR << "Error: input file not found" << RST << std::endl;
		exit(EXIT_FAILURE);
	}
	return ;
}

static void	output_file_error(std::ofstream &file, std::string _outFile) {
	file.open(_outFile);
	if (!file.is_open()) {
		std::cout << BR << "Error: output file not found" << RST << std::endl;
		exit(EXIT_FAILURE);
	}
	return ;
}

/**
 */
void	Replace::myReplace (void) {
	std::ifstream		input;
	std::ofstream		output;
	std::string			line;
	std::string			newLine;
	size_t				pos;

	input_file_error(input, _inFile);
	output_file_error(output, _outFile);
	while (std::getline(input, line)) {
		pos = 0;
		while ((pos = line.find(_search, pos)) != std::string::npos) {
			line.replace(pos, _search.length(), _replace);
			pos += _replace.length();
		}
		output << line << std::endl;
	}
	input.close();
	output.close();
	return ;
}

Replace::Replace( std::string filename, std::string search, std::string replace ) {
	_inFile = filename;
	_outFile = filename + ".replace";
	_search = search;
	_replace = replace;
}

Replace::~Replace( void ) {}

/* ***************************************************************  Replace.cpp */