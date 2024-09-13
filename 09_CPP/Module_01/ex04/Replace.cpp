/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replace.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:43:44 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/13 14:22:00 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Replace.hpp"

static void	safe_input_open(std::ifstream &file, std::string _inFile) {
	file.open(_inFile);
	if (!file.is_open()) {
		std::cout << BR << "Error: input file not found" << RST << std::endl;
		exit(EXIT_FAILURE);
	}
	return ;
}

static void	safe_output_open(std::ofstream &file, std::string _outFile) {
	file.open(_outFile);
	if (!file.is_open()) {
		std::cout << BR << "Error: output file not found" << RST << std::endl;
		exit(EXIT_FAILURE);
	}
	return ;
}
/**
 * - find() func searches substring _search in the current line
 * - pos is actualized to the line position of the first char in _search
 */
static bool	match_found(std::string &line, std::string _search, size_t &pos) {
	pos = line.find(_search, pos);
	if (pos == std::string::npos)
		return false;
	return true;
}

/**
 * 1. ERASE
 * - erase() func removes the characters in the range [pos, pos+len)
 * 2. INSERT
 * - insert() func inserts the characters of the string _replace into the current string
 */
static void	accual_replace(std::string &line, size_t pos, size_t len, std::string _replace) {
	line.erase(pos, len);
	line.insert(pos, _replace);
	return ;
}

/**
 * 1. SAFE GUARDS
 * - those functions OPEN the files and check their existence
 * 2. OUTER WHILE LOOP
 * - getline() func reads the file line by line
 * - after inner while loop, the line is written to the output file
 * 3. INNER WHILE LOOP
 *   - if it does't find a match, it returns std::string::npos
 *   - if it match, the line is modified by accual_replace() func
 */
void	Replace::myReplace (void) {
	std::ifstream		input;
	std::ofstream		output;
	std::string			line;
	std::string			newLine;
	size_t				pos;

	safe_input_open(input, _inFile);
	safe_output_open(output, _outFile);
	while (std::getline(input, line)) {
		pos = 0;
		while(match_found(line, _search, pos)) {
			accual_replace(line, pos, _search.length(), _replace);
			pos += _replace.length();
		}
		output << line << std::endl;
	}
	input.close();
	output.close();
	return ;
}

// Constructor
Replace::Replace( std::string filename, std::string search, std::string replace ) {
	_inFile = filename;
	_outFile = filename + ".replace";
	_search = search;
	_replace = replace;
}

// Destructor
Replace::~Replace( void ) {}

/* ***************************************************************  Replace.cpp */