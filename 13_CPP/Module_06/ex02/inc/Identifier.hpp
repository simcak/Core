/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Identifier.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:38:06 by psimcak           #+#    #+#             */
/*   Updated: 2025/10/08 13:07:18 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IDENTIFIER_HPP
# define IDENTIFIER_HPP

#include <iostream>
#include <stdlib.h>

/***********************************CLASSES************************************/
class Base { public: virtual ~Base(); };
class A : public Base {};
class B : public Base {};
class C : public Base {};

/**********************************FUNCTIONS***********************************/
Base*	generate(void);
void	identifyFromPtr(Base* base);
void	identifyFromRef(Base& base);

#endif
