/*
** find_inter.c for find_inter in /home/merran_g/work/c_igraph/rtv1
** 
** Made by Geoffrey Merran
** Login   <merran_g@epitech.net>
** 
** Started on  Sun Mar 16 18:42:28 2014 Geoffrey Merran
** Last update Mon May 19 23:20:50 2014 Geoffrey Merran
*/

#include "core.h"

t_vector	get_eq_param(t_vector eye, float k, t_vector pos_3d)
{
  t_vector	p;

  p.x = eye.x + (k * pos_3d.x);
  p.y = eye.y + (k * pos_3d.y);
  p.z = eye.z + (k * pos_3d.z);
  return (p);
}

void	best_of_k(t_rinter new, t_item item, t_inter *inter)
{
  if ((is_fzero(inter->k) && !is_fzero(new.k)) ||
      ((new.k < inter->k && new.k > 0.0001)))
    {
      inter->k = new.k;
      inter->rgb = item.color;
      init_vec(&inter->n, item.pos.x, item.pos.y, item.pos.z);
    }
}

t_finter       	*get_inters()
{
  t_finter     	*inter_x;

  inter_x = my_xmalloc(5 * sizeof(*inter_x));
  inter_x[SPHERE - 1] = inter_sphere;
  inter_x[PLANE - 1] = inter_plan;
  inter_x[CONE - 1] = inter_cone;
  inter_x[CYLINDER - 1] = inter_cylinder;
  inter_x[4] = NULL;
  return (inter_x);
}

void		init_inter(t_inter *inter)
{
  init_rgb(&inter->rgb, 0, 0, 0);
  init_vec(&inter->n, 0, 0, 0);
  inter->k = 0;
}

t_inter		find_inter(t_cam eye, t_vector pos_3d, t_node *items)
{
  t_node	*tmp;
  t_inter	inter;
  t_finter     	*inter_x;

  tmp = items;
  init_inter(&inter);
  inter_x = get_inters();
  rotate_all(&eye.pos, eye.angle);
  rotate_all(&pos_3d, eye.angle);
  while (tmp)
    {
      best_of_k(inter_x[tmp->item.type - 1]
		(eye, pos_3d, tmp->item), tmp->item, &inter);
      tmp = tmp->next;
    }
  free(inter_x);
  return (inter);
}
