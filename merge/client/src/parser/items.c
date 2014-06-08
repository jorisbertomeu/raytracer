/*
** items.c for items in /home/merran_g/work/c_igraph/rtv1
** 
** Made by Geoffrey Merran
** Login   <merran_g@epitech.net>
** 
** Started on  Sun Mar 16 01:54:50 2014 Geoffrey Merran
** Last update Sun Jun  8 09:49:09 2014 Jeremy Mediavilla
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
  tmp->item.transparence = new.transparence;
  tmp->item.reflexion = new.reflexion;
  /* tmp->item.effect = new.effect; */
  tmp->next = *list;
  *list = tmp;
}
