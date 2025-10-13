/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 18:58:27 by psimcak           #+#    #+#             */
/*   Updated: 2025/10/13 13:35:19 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"

int main(int, char**)
{
	Array<int>	numbers(MAX_VAL);
	int*		a_mirror = new int[MAX_VAL];

	srand(time(NULL));
	for (unsigned int i = 0; i < MAX_VAL; i++)
	{
		const int value = rand() / 10000000;
		numbers[i] = value;
		a_mirror[i] = value;
	}
	std::cout << "NUMBERS" << std::endl;
	numbers.putArr();

	std::cout << "\nMIRROR" << std::endl;
	for (unsigned int i = 0; i < MAX_VAL; i++)
		i+1 < MAX_VAL	? std::cout << a_mirror[i] << ", "
						: std::cout << a_mirror[i] << "\n" ;

	// Scope
	std::cout << "\nArray<int> tmp = numbers" << std::endl;
	Array<int> tmp = numbers;
	std::cout << "\nArray<int> test(tmp)" << std::endl;
	Array<int> test(tmp);

	for (unsigned int i = 0; i < MAX_VAL; i++)
	{
		if (a_mirror[i] != numbers[i])
		{
			std::cout << "didn't save the same value!!" << std::endl;
			return 1;
		}
	}

	try
	{
		std::cout << "\nnumbers[-2] = 0" << std::endl;
		numbers[-2] = 0;
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	try
	{
		std::cout << "\nnumbers[MAX_VAL] = 0" << std::endl;
		numbers[MAX_VAL] = 0;
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	for (unsigned int i = 0; i < MAX_VAL; i++)
	{
		numbers[i] = rand() / 10000000;
	}
	std::cout << "\nNUMBERS" << std::endl;
	numbers.putArr();

	delete [] a_mirror;
	return 0;
}

// int main(int, char**)
// {
// 	Array<int> numbers(MAX_VAL);
// 	int* mirror = new int[MAX_VAL];
// 	srand(time(NULL));
// 	for (int i = 0; i < MAX_VAL; i++)
// 	{
// 		const int value = rand();
// 		numbers[i] = value;
// 		mirror[i] = value;
// 	}
// 	//SCOPE
// 	{
// 		Array<int> tmp = numbers;
// 		Array<int> test(tmp);
// 	}

// 	for (int i = 0; i < MAX_VAL; i++)
// 	{
// 		if (mirror[i] != numbers[i])
// 		{
// 			std::cerr << "didn't save the same value!!" << std::endl;
// 			return 1;
// 		}
// 	}
// 	try
// 	{
// 		numbers[-2] = 0;
// 	}
// 	catch(const std::exception& e)
// 	{
// 		std::cerr << e.what() << '\n';
// 	}
// 	try
// 	{
// 		numbers[MAX_VAL] = 0;
// 	}
// 	catch(const std::exception& e)
// 	{
// 		std::cerr << e.what() << '\n';
// 	}

// 	for (int i = 0; i < MAX_VAL; i++)
// 	{
// 		numbers[i] = rand();
// 	}
// 	delete [] mirror;//
// 	return 0;
// }