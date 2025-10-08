/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:38:32 by psimcak           #+#    #+#             */
/*   Updated: 2025/10/08 11:35:46 by psimcak          ###   ########.fr       */
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

	dataPtr->name = "The Hitchhiker's Guide to the Galaxy.";
	dataPtr->answer = 42;

	/**************************************************************************/
	std::cout
		<< "STD::DEC/HEX/OCT EXAMPLES" << std::endl
		<< std::dec <<    "dec: " << dataPtr->answer
		<< std::hex << "   hex: " << dataPtr->answer
		<< std::oct << "   oct: " << dataPtr->answer << std::dec
	<< std::endl << std::endl;

	/**************************************************************************/
	std::cout
		<< BB "ORIGINAL DATA:" RST << std::endl
		<< "Adress:       " << dataPtr << std::endl
		<< "Name:         " << dataPtr->name << std::endl
		<< "Answer:       " << dataPtr->answer
	<< std::endl << std::endl;

	/**************************************************************************/
	dataNum = Serializer::serialize(dataPtr);
	std::cout
		<< BR "RESULTS OF SERIALIZATION:" RST << std::endl
		<< "Adress-dec:   " << std::dec << dataNum << std::endl
		<< "Adress-hex:   " << std::hex << dataNum << std::dec << std::endl
		<< "Name:         ?" << std::endl
		<< "Answer:       ?"
	<< std::endl << std::endl;

	/**************************************************************************/
	dataPtrPost = Serializer::deserialize(dataNum);
	std::cout
		<< BR "RESULTS OF deSERIALIZATION:" RST << std::endl
		<< "Adress:       " << dataPtrPost << std::endl
		<< "Name:         " << dataPtrPost->name << std::endl
		<< "Answer:       " << dataPtrPost->answer
	<< std::endl;
	/**************************************************************************/

	delete dataPtr;
	return 0;
}
