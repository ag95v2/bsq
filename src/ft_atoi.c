/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgian <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 19:18:07 by bgian             #+#    #+#             */
/*   Updated: 2019/07/23 09:34:36 by bgian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "our_lib.h"

/* 
 * This is not typical atoi.
 * We need only unsigned output here .
 * Also we do not skip garbage of any sort.
 * TODO: add check for overflows
 */

unsigned int	atou(char *str)
{
	unsigned int	result;
	int				digit;

	result = 0;
	while (*str)
	{
		digit = *str - '0';
		result = 10 * result + digit;
		str++;
	}
	return (result);
}
