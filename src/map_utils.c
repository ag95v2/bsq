/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgian <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 22:46:09 by bgian             #+#    #+#             */
/*   Updated: 2019/07/25 05:59:44 by bgian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "our_lib.h"

#define MAX_HEADER_LENGTH 20
#define REASONABLE_HEADER_LEN 15

t_map_psum	*init_map()
{
	t_map_psum *map;

	map = (t_map_psum *)malloc(sizeof(t_map_psum));
	map->is_valid = 1;
	return (map);
}

t_map_psum	*parse_map_header(char *filename)
{
	t_map_psum	*map;
	int			fd;
	char		map_header[MAX_HEADER_LENGTH];
	int			len;

	map = init_map();
	if (!filename)
		fd = 0;		
	else 
		fd = open(filename, O_RDONLY);
	len = readline(fd, map_header, MAX_HEADER_LENGTH);
	if (len > REASONABLE_HEADER_LEN)
		map->is_valid = 0;
	map_header[len] = 0;
	map->full_char = map_header[len - 1];
	map->obs_char = map_header[len - 2];
	map->empty_char = map_header[len - 3];
	map_header[len - 3] = 0;
	if (!only_digits(map_header))
		map->is_valid = 0;
	map->height = atou(map_header);
	map->fd = fd;
	return (map);
}

t_first_line	*read_first_line(t_map_psum *map)
{
	t_first_line	*start;
	t_first_line	*cur;
	unsigned int 	width;
	char			c;

	start = (t_first_line *)malloc(sizeof(t_first_line));
	start->next = 0;
	cur = start;
	width = 0;
	while ((c = ft_getchar(map->fd)) != '\n')
	{
		cur->text[width % EXP_WID] = c;
		width++;
		if (width % EXP_WID == 0)
		{
			cur->text[EXP_WID] = 0;
			cur->next = (t_first_line *)malloc(sizeof(t_first_line));
			cur = cur->next;
			cur->next = 0;
		}
	}
	#ifdef DEBUG_READ
	ft_putstr("\nDEBUG_READ: start of the first line:\n", 1);
	ft_putstr(start->text, 1);
	ft_putstr("\n\n", 1);
	#endif
	start->text[width] = 0;
	map->width = width;
	return (start);
}

int				process_symbol(char c, t_map_psum *map, int pos, int r_cusum)
{
	int	add;

	if (c == map->empty_char || c == map->full_char)
		add = 0;
	else if (c == map->obs_char)
		add = 1;
	else
	{
		map->is_valid = 0;
		#ifdef DEBUG_READ
		printf("\nDEBUG_READ: map became invalid while processing symbol ");
		printf("'%c' at %d! \n",c, pos);
		#endif
		return (-1);
	}
	if (pos / map->width == 0)
		map->start[pos] = r_cusum + add;
	else
		map->start[pos] = r_cusum + add + map->start[pos - map->width]; 
	return (add);
}

void			parse_line(t_map_psum *map, unsigned int pos)
{
	char			*buf;
	unsigned int	b_read;
	char			*tmp;
	int				r_cusum;

	r_cusum = 0;
	buf = (char *)malloc(map->width + 1);
	tmp = buf;
	b_read = read(map->fd, buf, map->width + 1);
	if (buf[map->width] != '\n' || b_read < map->width + 1)
	{
		map->is_valid = 0;
		#ifdef DEBUG_READ
		ft_putstr("\nDEBUG_READ: map is invalid! \n", 1);
		#endif
		return ;
	}
	buf[map->width] = 0;
	while (*buf)
	{
		r_cusum += process_symbol(*(buf++), map, pos++, r_cusum);
	}
	#ifdef DEBUG_READ
	ft_putstr("\nDEBUG_READ: next line:\n", 1);
	ft_putstr(tmp, 1);
	ft_putstr("\n", 1);
	#endif
	free(tmp);
}

void			parse_first_line(t_first_line *f_line, t_map_psum *map)
{
	int		count;
	char	*pos;
	int		r_cusum;

	r_cusum = 0;
	count = 0;
	while (f_line)
	{
		pos = f_line->text;
		while (*pos)
		{
			r_cusum += process_symbol(*(pos++), map, count, r_cusum);
			count++;
		}
		f_line = f_line->next;
	}
}

void			read_map(t_map_psum *map)
{
	t_first_line	*f_line;
	unsigned int	l_num;

	f_line = read_first_line(map);
	map->start = (unsigned int *)malloc(map->width*map->height*sizeof(int));
	parse_first_line(f_line, map);
	l_num = 1;
	while (l_num < map->height && map->is_valid)
		parse_line(map, l_num++ * map->width);
	close(map->fd);
}

char			psum_to_char(t_map_psum *map, unsigned int pos, t_solution *s)
{
	unsigned int	right;
	unsigned int	up;
	unsigned int	diag;

	if (s && pos / map->width <= s->y + s->side - 1 
		&& pos / map->width >= s->y 
		&& pos % map->width >= s->x
		&& pos % map->width <= s->x + s->side - 1)
		return (map->full_char);
	right = pos % map->width ? map->start[pos - 1] : 0;
	up = pos / map->width ? map->start[pos - map->width] : 0;
	diag = (pos % map->width && pos / map->width) ?
		map->start[pos - map->width - 1] : 0;
	return ((map->start[pos] - right - up + diag > 0) ?
	   	map->obs_char : map->empty_char);
}

void			print_map(t_map_psum *map, t_solution *res)
{
	unsigned int	pos;

	printf("\nMap :\n");
	pos = 0;
	while (pos < (map->width * map->height))
	{
		ft_putchar(psum_to_char(map, pos, res), 1);
		pos++;
		if (pos % map->width == 0 && pos > 0)
			printf("\n");
	}

	#ifdef PSUM_REPR
	printf("\nPartial sum representation:\n");
	pos = 0;
	while (pos < map->width * map->height)
	{
		printf("%4u ", map->start[pos]);
		pos++;
		if (pos % map->width == 0)
			printf("\n");
	}
	printf("\n\n");
	#endif
}
