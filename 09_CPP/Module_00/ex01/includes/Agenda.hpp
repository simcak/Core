/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Agenda.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 04:32:38 by psimcak           #+#    #+#             */
/*   Updated: 2024/08/01 09:03:14 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AGENDA_HPP
# define AGENDA_HPP

#include <iostream>
#include <iomanip>

#define SUCCESS 0
#define FAILURE 1

// Color codes
#define BWT		"\001\033[1;37m\002"
#define RED		"\001\033[1;31m\002"
#define GRN		"\001\033[1;32m\002"
#define BBB		"\001\033[1;34m\002"
#define RST		"\001\033[0;0m\002"

// Prototypes
void	safeGetline(std::string &dest, std::string mes, int index);

#endif