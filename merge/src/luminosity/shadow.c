/*
** shadow.c for shadow in /home/merran_g/work/c_igraph/raytracer
** 
** Made by Geoffrey Merran
** Login   <merran_g@epitech.net>
** 
** Started on  Wed Jun  4 01:46:57 2014 Geoffrey Merran
** Last update Thu Jun  5 00:57:48 2014 Geoffrey Merran
*/

#include "core.h"

int		is_shadow(t_spot spot, t_inter inter, t_vector pos_3d, t_node *items)
{
  t_inter	inter_shadow;
  t_cam		spot_dir;
  t_node	tmp;

  tmp.item = inter.item;
  tmp.next = NULL;
  if (inter.k == 0)
    return (1);
  spot_dir.pos.x = spot.pos.x;
  spot_dir.pos.y = spot.pos.y;
  spot_dir.pos.z = spot.pos.z;
  spot_dir.distance = 100;
  init_vec(&spot_dir.angle, 0, 0, 0);
  inter_shadow = find_inter(spot_dir, pos_3d, items);
  inter_shadow.p = get_eq_param(pos_3d, inter_shadow.k, spot_dir.pos);
  /* printf("shadow : %f %f\n", inter_shadow.k, inter.k); */
  /* if (inter_shadow.k < 1.0000 && inter_shadow.k > 0.000001) */
  /*   return (1); */
  if (inter.item.type == SPHERE)
    printf("%d\n", inter_shadow.item.type);
  if (inter.item.pos.x == inter_shadow.item.pos.x
      && inter.item.pos.y == inter_shadow.item.pos.y
      && inter.item.pos.z == inter_shadow.item.pos.z)
    return (0);
  return (1);
}
