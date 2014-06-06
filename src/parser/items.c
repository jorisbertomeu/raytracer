/*
** items.c for items in /home/merran_g/work/c_igraph/rtv1
** 
** Made by Geoffrey Merran
** Login   <merran_g@epitech.net>
** 
** Started on  Sun Mar 16 01:54:50 2014 Geoffrey Merran
** Last update Fri Jun  6 05:00:44 2014 Geoffrey Merran
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
  tmp->item.brillance = new.brillance;
  tmp->item.reflexion = new.reflexion;
  tmp->next = *list;
  *list = tmp;
}

void	init_item(t_item *new, t_vector pos, t_vector angle, t_type type)
{
  new->pos = pos;
  new->angle = angle;
  new->type = type;
}

void	init_item2(t_item *new, float rayon, t_rgb color, float brillance, float reflexion)
{
  new->rayon = rayon;
  new->color = color;
  new->brillance = brillance;
  new->reflexion = reflexion;
}

void	init_rgb(t_rgb *color, int r, int g, int b)
{
  color->r = r;
  color->g = g;
  color->b = b;
}

void		add_spot(t_spot **spots, t_vector pos, t_rgb color)
{
  t_spot	*new;

  new = my_xmalloc(sizeof(*new));
  new->pos = pos;
  new->color = color;
  new->next = *spots;
  *spots = new;
}

t_spot		*get_spots()
{
  t_spot	*spots;
  t_vector	n_pos;
  t_rgb		n_color;

  spots = NULL;
  init_vec(&n_pos, -300, 800, 300);
  init_rgb(&n_color, 161, 40, 48);
  add_spot(&spots, n_pos, n_color);
  init_vec(&n_pos, -300, -800, 300);
  init_rgb(&n_color, 244, 41, 61);
  add_spot(&spots, n_pos, n_color);
  /* init_vec(&n_pos, -300, 0, 300); */
  /* init_rgb(&n_color, 45, 255, 156); */
  /* add_spot(&spots, n_pos, n_color); */
  return (spots);
}

t_node		*get_items()
{
  t_node	*items;
  t_vector	n_pos;
  t_vector	n_angle;
  t_rgb		n_color;
  t_item	new;

  items = NULL;
  init_vec(&n_pos, 0, 0, 300);
  init_vec(&n_angle, 0, 0, 0);
  init_rgb(&n_color, 202, 0, 42);
  init_item(&new, n_pos, n_angle, SPHERE);
  init_item2(&new, 100.0, n_color, 0.5, 0.5);
  add_item(&items, new);
  init_vec(&n_pos, 0, 0, 0);
  init_vec(&n_angle, 0, 0, 0);
  init_rgb(&n_color, 255, 17, 0);
  init_item(&new, n_pos, n_angle, PLANE);
  init_item2(&new, 0, n_color, 0.5, 0.5);
  add_item(&items, new);
  init_vec(&n_pos, 0, 0, 200);
  init_vec(&n_angle, 0, 0, 0);
  init_rgb(&n_color, 255, 66, 0);
  init_item(&new, n_pos, n_angle, CYLINDER);
  init_item2(&new, 50.0, n_color, 0.5, 0.5);
  add_item(&items, new);
  return (items);
}
