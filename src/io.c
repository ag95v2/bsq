/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgian <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 23:15:31 by bgian             #+#    #+#             */
/*   Updated: 2019/07/23 04:26:23 by bgian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "our_lib.h"

void	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr(char *s, int fd)
{
	while (*s)
		ft_putchar(*(s++), fd);
}

char	ft_getchar(int fd)
{
	int c;

	read(fd, &c, 1);
	return (c);
}

int		readline(int fd, char *s, int max_len)
{
	char	c;
	int		n_symbols;

	n_symbols = 0;
	while ((c = ft_getchar(fd)) != '\n' && c && n_symbols++ < max_len)
		*(s++) = c;
	return (n_symbols);
}
