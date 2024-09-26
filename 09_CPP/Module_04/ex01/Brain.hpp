/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:15:25 by psimcak           #+#    #+#             */
/*   Updated: 2024/09/26 14:23:42 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
# define BRAIN_HPP

#include <iostream>

#define BG		"\033[1;32m"
#define BR		"\033[1;31m"
#define BW		"\033[1;37m"
#define RST		"\033[0m"

class Brain {

	public:
		std::string	ideas[100];

		Brain();
		Brain(Brain const &src);

		Brain	&operator=(Brain const &src);

		~Brain();

};

#endif
