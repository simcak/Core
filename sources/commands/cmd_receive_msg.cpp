/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_receive_msg.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:53:35 by cberneri          #+#    #+#             */
/*   Updated: 2025/10/20 10:28:02 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_irc.hpp"
#include "../headers/Server.hpp" //full definition needed
#include "../headers/User.hpp"
#include "../headers/Channel.hpp"

/*
	Command: RECEIVE
	Parameters: <filename>
	
	RECEIVE command is used to get the sent file from the server storage.
*/

 