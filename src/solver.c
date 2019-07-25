/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgian <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 13:01:06 by bgian             #+#    #+#             */
/*   Updated: 2019/07/25 10:55:04 by bgian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "our_lib.h"

t_solution	*init_solution(unsigned int x, unsigned int y, int side)
{
	t_solution	*s;

	s = (t_solution *)malloc(sizeof(t_solution));
	s->x = x;
	s->y = y;
	s->side = side;
	return (s);
}

/* 
 * Square inside filled psum map with upper left corner at pos and side side
 * Return >0 if square is NOT empty
 */
int			check_square(t_map_psum *map, unsigned int pos, unsigned int side)
{
	unsigned int	tmp_res;

	if (side > (map->height - (pos / map->width) ))
		return (1);
	if (side > map->width - pos % map->width)
		return (1);
	#ifdef DBG_SOLVER
	printf("Checking!\n");
	#endif
	tmp_res = map->start[pos + map->width * (side - 1) + side - 1];
	#ifdef DBG_SOLVER
	printf("N at right diagonal: %d\n", tmp_res);
	#endif
	if (pos % map->width > 0)
		tmp_res -= map->start[pos - 1 + map->width * (side - 1)];
	if (pos / map->width > 0)
		tmp_res -= map->start[pos + (side - 1) - map->width];
	if ((pos % map->width) && (pos / map->width))
		tmp_res += map->start[pos - map->width - 1];
	#ifdef DBG_SOLVER
	printf("Obstackles inside small square: %d\n", tmp_res);
	#endif
	return (tmp_res);
}

t_solution	*check_size(t_map_psum *map, unsigned int side)
{
	unsigned int	pos;
	t_solution		*res;

	pos = 0;

	while (pos < (map->height * map->width))
	{
		#ifdef DBG_SOLVER
		printf("Searching for square of size %d at pos (%d, %d)\n",
			   	side, pos % map->width, pos / map->width);
		#endif
		if (!check_square(map, pos, side))
		{
			res = init_solution(pos % map->width, pos / map->width, side);
			#ifdef DBG_SOLVER
			printf("Found square of size %d at (%d, %d)\n", 
					side, res->x, res->y);
			print_map(map, res);
			#endif
			return (res);
		}
		pos++;
	}
	return (0);
}

unsigned int	min(unsigned int a, unsigned int b)
{
	return (a > b ? b : a);
}

t_solution	*bin_search(t_map_psum *map)
{
	t_solution				*res;
	t_solution				*best;
	unsigned int			from;
	unsigned int			to;

	res = 0;
	from = 0;
	to = min(map->width, map->height);
	while (to - from > 1)
	{
		res = check_size(map, (from + to) / 2);
		if (res)
		{
			best = res;
			from = (from + to) / 2;
		}
		else
			to = (from + to) / 2;
		#ifdef DBG_SOLVER
		printf("Best size: %d at (%d, %d)\n", best->side, best->x, best->y);
		#endif
	}
	return (best);
}
