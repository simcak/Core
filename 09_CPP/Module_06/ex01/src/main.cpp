/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:38:32 by psimcak           #+#    #+#             */
/*   Updated: 2025/10/07 15:07:18 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Serializer.hpp"
#include "../inc/Macros.hpp"

int	main(void)
{
	Data		*dataPtr;
	Data		*dataInterpreted;	
	uintptr_t	numPtr;

	dataPtr = new Data;
	dataPtr->number = 42;

	int	i = -1;
	while (++i < 30)
		dataPtr->word[i] = 'a' + i;
	dataPtr->word[i] = '\0';

	std::cout
	<< "Original data ptr: " << dataPtr << std::endl
	<< "Original word:     " << dataPtr->word << std::endl
	<< "Original num:      " << dataPtr->number << std::endl;

	numPtr = Serializer::serialize(dataPtr);
	std::cout << std::endl
	<< "Num pointer hexa:  " << std::hex << numPtr << std::endl;

	dataInterpreted = Serializer::deserialize(numPtr);
	std::cout << std::endl
	<< "Serialized  ptr:   " << std::dec << dataInterpreted << std::endl
	<< "Interpreted word:  " << dataInterpreted->word << std::endl
	<< "Interpreted num:   " << dataInterpreted->number << std::endl;

	delete dataPtr;
	return 0;
}
