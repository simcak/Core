/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:14:53 by psimcak           #+#    #+#             */
/*   Updated: 2024/07/30 15:46:28 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cctype>

int	main(int argc, char **argv)
{
	int i = 0;

	if (argc == 1) {
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
	}
	else
	{
		while (++i < argc) {
			for (int j = 0; argv[i][j]; j++)
				std::cout << (char)toupper(argv[i][j]);
		}
		std::cout << std::endl;
	}
	return (0);
}
