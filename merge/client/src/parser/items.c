/*
** items.c for items in /home/merran_g/work/c_igraph/rtv1
** 
** Made by Geoffrey Merran
** Login   <merran_g@epitech.net>
** 
** Started on  Sun Mar 16 01:54:50 2014 Geoffrey Merran
** Last update Sun Jun  8 12:12:00 2014 Jeremy Mediavilla
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

float		get_type_effect_val(char *balise, char **conf, int i)
{
  int		j;
  int		len;
  float		tmp;

  j = 0;
  len = strlen(balise);
  while (j < 3)
    {
      if (strncmp(conf[i], balise, len) == 0)
	{
	  tmp = get_fbalise_value_spec(conf[i], balise, i);
	  if (tmp < 0 || tmp > 2)
	    {
	      fprintf(stderr, "Error on line %i : value must be \
between 0 and 2\n", (i + 1));
	      return (0);
	    }
	  return (tmp);
	}
      j++;
      i++;
    }
  return (0);
}
