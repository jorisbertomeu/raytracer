/*
** items.c for items in /home/merran_g/work/c_igraph/rtv1
** 
** Made by Geoffrey Merran
** Login   <merran_g@epitech.net>
** 
** Started on  Sun Mar 16 01:54:50 2014 Geoffrey Merran
** Last update Mon May 19 23:21:49 2014 Geoffrey Merran
*/

#include "parser.h"

void		add_item(t_node **list, t_item new)
{
  t_node	*tmp;

  tmp = my_xmalloc(sizeof(*tmp));
  tmp->item.pos = new.pos;
  tmp->item.angle = new.angle;
  tmp->item.type = new.type;
  tmp->item.rayon = new.rayon;
  tmp->item.color = new.color;
  tmp->next = *list;
  *list = tmp;
}

void	init_item(t_item *new, t_vector pos, t_vector angle, t_type type)
{
  new->pos = pos;
  new->angle = angle;
  new->type = type;
}

void	init_item2(t_item *new, float rayon, t_rgb color)
{
  new->rayon = rayon;
  new->color = color;
}

void	init_rgb(t_rgb *color, int r, int g, int b)
{
  color->r = r;
  color->g = g;
  color->b = b;
}

t_node		*get_items()
{
  t_node	*items;
  t_vector	n_pos;
  t_vector	n_angle;
  t_rgb		n_color;
  t_item	new;

  items = NULL;
  init_vec(&n_pos, 0, 0, 0);
  init_vec(&n_angle, 0, 0, 0);
  init_rgb(&n_color, 255, 0, 0);
  init_item(&new, n_pos, n_angle, SPHERE);
  init_item2(&new, 100.0, n_color);
  add_item(&items, new);
  init_vec(&n_pos, 0, 0, 0);
  init_vec(&n_angle, 0, 0, 0);
  init_rgb(&n_color, 0, 0, 255);
  init_item(&new, n_pos, n_angle, PLANE);
  init_item2(&new, 0, n_color);
  add_item(&items, new);
  init_vec(&n_pos, 0, 0, 0);
  init_vec(&n_angle, 0, 0, 0);
  init_rgb(&n_color, 0, 255, 0);
  init_item(&new, n_pos, n_angle, CONE);
  init_item2(&new, 10.0, n_color);
  add_item(&items, new);
  return (items);
}
