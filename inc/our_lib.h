/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_lib.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgian <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 22:19:34 by bgian             #+#    #+#             */
/*   Updated: 2019/07/25 01:13:57 by bgian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OUR_LIB_H

# define OUR_LIB_H
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# define EXP_WID 200


#include <stdio.h> // DO NOT FORGET TO REMOVE THIS LINE


typedef struct	map_psum
{
	unsigned int	*start;
	unsigned int	width;
	unsigned int	height;
	char			obs_char;
	char			empty_char;
	char			full_char;
	int				is_valid;
	int				fd;
}				t_map_psum;

typedef struct	s_first_line
{
	char					text[EXP_WID + 1];
	struct s_first_line		*next;
}				t_first_line;

typedef struct	s_solution
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	side;
}				t_solution;

unsigned int    atou(char *str);
char			ft_getchar(int fd);
int     		readline(int fd, char *s, int max_len);
void    		ft_putstr(char *s, int fd);
void    		ft_putchar(char c, int fd);
t_map_psum  	*parse_map_header(char *filename);
int				only_digits(char *s); 
void            print_map(t_map_psum *map, t_solution *res);
void            read_map(t_map_psum *map);
t_solution		*bin_search(t_map_psum *map);


#endif
