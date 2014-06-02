/*
** kekette.c for  in /home/mediav_j/mabm/raytracer/src/kekette
** 
** Made by Jeremy Mediavilla
** Login   <mediav_j@epitech.net>
** 
** Started on  Mon Jun  2 15:32:31 2014 Jeremy Mediavilla
** Last update Mon Jun  2 15:39:49 2014 Jeremy Mediavilla
*/

#include "my_mlx.h"

unsigned int	get_pix_clr(int pixel, int length, t_scene *scene)
{
  t_post	*pos;

  if (length == 0)
    {
      fprintf(stderr, "Error length can't be equal to zero\n");
      exit(0);
    }
  pos.x = pixel % length;
  pos.y = pixel / length;
  return (calc_image(pos, scene));
}
