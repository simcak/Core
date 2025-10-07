/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:38:32 by psimcak           #+#    #+#             */
/*   Updated: 2025/10/07 18:39:51 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Serializer.hpp"
#include "../inc/Macros.hpp"

int	main(void)
{
	Data		*dataPtr;
	uintptr_t	dataNum;
	Data		*dataPtrPost;	

	dataPtr = new Data;

	int	i = -1;
	while (++i < 30)
		dataPtr->word[i] = 'a' + i;
	dataPtr->word[i] = '\0';
	
	dataPtr->number = 42;

	/**************************************************************************/
	std::cout
		<< "STD::DEC/HEX/OCT EXAMPLES" << std::endl
		<< std::dec <<    "dec: " << dataPtr->number
		<< std::hex << "   hex: " << dataPtr->number
		<< std::oct << "   oct: " << dataPtr->number << std::dec
	<< std::endl << std::endl;

	/**************************************************************************/
	std::cout
		<< BB "ORIGINAL DATA:" RST << std::endl
		<< "Adress:       " << dataPtr << std::endl
		<< "Word:         " << dataPtr->word << std::endl
		<< "Number:       " << dataPtr->number
	<< std::endl << std::endl;

	/**************************************************************************/
	dataNum = Serializer::serialize(dataPtr);
	std::cout
		<< BR "RESULTS OF SERIALIZATION:" RST << std::endl
		<< "Adress-dec:   " << std::dec << dataNum << std::endl
		<< "Adress-hex:   " << std::hex << dataNum << std::dec << std::endl
		<< "Word:         ?" << std::endl
		<< "Number:       ?"
	<< std::endl << std::endl;

	/**************************************************************************/
	dataPtrPost = Serializer::deserialize(dataNum);
	std::cout
		<< BR "RESULTS OF deSERIALIZATION:" RST << std::endl
		<< "Adress:       " << dataPtrPost << std::endl
		<< "Word:         " << dataPtrPost->word << std::endl
		<< "Number:       " << dataPtrPost->number
	<< std::endl;
	/**************************************************************************/

	delete dataPtr;
	return 0;
}
