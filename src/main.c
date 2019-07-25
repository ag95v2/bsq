/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgian <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 22:05:44 by bgian             #+#    #+#             */
/*   Updated: 2019/07/25 08:35:59 by bgian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "our_lib.h"

int main(int argc, char **argv)
{
	int			i;
	t_map_psum	*map;
	t_solution	*res;

	i = 1;
	if (argc < 2)
	{
		map = parse_map_header(0);
		read_map(map);
		res = bin_search(map);
		print_map(map, res);
	}
	else
		while (i < argc)
		{
			map = parse_map_header(argv[i++]);
			read_map(map);
			#ifdef DEBUG
			print_map(map, res);
			#endif
			if (!map->is_valid)
				ft_putstr("map error\n", 2);
			res = bin_search(map);
			print_map(map, res);
		}
	return (0);
}
