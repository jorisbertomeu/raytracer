/*
** items.c for items in /home/merran_g/work/c_igraph/rtv1
** 
** Made by Geoffrey Merran
** Login   <merran_g@epitech.net>
** 
** Started on  Sun Mar 16 01:54:50 2014 Geoffrey Merran
** Last update Sat Jun  7 22:26:12 2014 Geoffrey Merran
*/

#include "parser.h"

void		add_item(t_node **list, t_item new)
{
  t_node	*tmp;

  tmp = my_xmalloc(sizeof(*tmp));
  tmp->item.pos = new.pos;
  tmp->item.angle = new.angle;
  tmp->item.qua = new.qua;
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
  init_vec(&n_pos, 0, 200, 200);
  init_rgb(&n_color, 255, 255, 255);
  add_spot(&spots, n_pos, n_color);
  init_vec(&n_pos, 0, 0, -100);
  init_rgb(&n_color, 255, 255, 255);
  add_spot(&spots, n_pos, n_color);
  /* init_vec(&n_pos, 200, 0, 150); */
  /* init_rgb(&n_color, 255, 255, 255); */
  /* add_spot(&spots, n_pos, n_color); */
  /* init_vec(&n_pos, 0, 300, -150); */
  /* init_rgb(&n_color, 255, 255, 255); */
  /* add_spot(&spots, n_pos, n_color); */
  /* init_vec(&n_pos, 0, -300, -150); */
  /* init_rgb(&n_color, 255, 255, 255); */
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
  new.qua.a = 0;
  new.qua.b = 0;
  new.qua.c = 0;
  /* init_vec(&n0_pos, -200, -100, 100); */
  /* init_vec(&n_angle, 0, 0, 0); */
  /* init_rgb(&n_color, 255, 0, 0); */
  /* init_item(&new, n_pos, n_angle, CONE); */
  /* init_item2(&new, 30.0, n_color, 0.5, 0.5); */
  /* add_item(&items, new); */
  init_vec(&n_pos, 0, 0, -200);
  init_vec(&n_angle, 0, 0, 0);
  init_rgb(&n_color, 0, 0, 255);
  init_item(&new, n_pos, n_angle, PLANE);
  init_item2(&new, 0, n_color, 0.5, 0.1);
  add_item(&items, new);
  /* init_vec(&n_pos, 0, 0, 200); */
  /* init_vec(&n_angle, 180, 0, 0); */
  /* init_rgb(&n_color, 0, 0, 255); */
  /* init_item(&new, n_pos, n_angle, PLANE); */
  /* init_item2(&new, 0, n_color, 0.5, 0.1); */
  /* add_item(&items, new); */
  /* init_vec(&n_pos, 0, 200, 0); */
  /* init_vec(&n_angle, 90, 0, 0); */
  /* init_rgb(&n_color, 0, 0, 255); */
  /* init_item(&new, n_pos, n_angle, PLANE); */
  /* init_item2(&new, 0, n_color, 0.5, 0.1); */
  /* add_item(&items, new); */
  /* init_vec(&n_pos, 0, -200, 0); */
  /* init_vec(&n_angle, -90, 0, 0); */
  /* init_rgb(&n_color, 0, 0, 255); */
  /* init_item(&new, n_pos, n_angle, PLANE); */
  /* init_item2(&new, 0, n_color, 0.5, 0.1); */
  /* add_item(&items, new); */
  init_vec(&n_pos, 0, 200, 0);
  init_vec(&n_angle, 0, 0, 0);
  init_rgb(&n_color, 255, 0, 0);
  init_item(&new, n_pos, n_angle, CONE);
  init_item2(&new, 10.0, n_color, 0.1, 0.1);
  add_item(&items, new);
  return (items);
}
