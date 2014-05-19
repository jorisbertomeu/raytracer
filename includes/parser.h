/*
** parser.h for parser in /home/merran_g/work/c_elem/raytracer/includes
** 
** Made by Geoffrey Merran
** Login   <merran_g@epitech.net>
** 
** Started on  Mon May 19 23:05:46 2014 Geoffrey Merran
** Last update Mon May 19 23:27:50 2014 Geoffrey Merran
*/

#ifndef PARSER_
# define PARSER_
# include <stdlib.h>
# include "my.h"
# include "my_mlx.h"
# include "rtv1.h"

/*
** Old
*/

void   	add_item(t_node **list, t_item new);
void	init_item(t_item *new, t_vector pos, t_vector angle, t_type type);
void	init_item2(t_item *new, float rayon, t_rgb color);
void	init_rgb(t_rgb *color, int r, int g, int b);
t_node 	*get_items();

/*
** Get Scene (To Do)
*/

t_scene	*get_scene();

#endif /* PARSER_ */
