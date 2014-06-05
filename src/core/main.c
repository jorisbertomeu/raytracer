/*
** main.c for  in /home/merran_g/work/c_piscine/mkdir
**
** Made by Geoffrey Merran
** Login   <merran_g@epitech.net>
**
** Started on  Fri Oct  4 09:11:03 2013 Geoffrey Merran
** Last update Thu Jun  5 22:04:49 2014 Geoffrey Merran
*/

#include "core.h"

unsigned int   	calc_image(t_pos pos, t_scene *scene)
{
  t_vector	pos_3d;
  t_inter      	inter;
  t_spot	spot;
  unsigned int 	color;

  init_vec(&spot.pos, -300, 300, 150);
  init_rgb(&spot.color, 255, 255, 255);
  pos_3d.x = scene->eye->distance;
  pos_3d.y = (WIN_X / 2.000) - (float) pos.x;
  pos_3d.z = (WIN_Y / 2.000) - (float) pos.y;
  inter = find_inter(*scene->eye, pos_3d, scene->items);
  inter.p = get_eq_param(scene->eye->pos, inter.k, pos_3d);
  inter.n = get_normal(inter);
  if (is_shadow(spot, inter, scene->items))
    return (change_rgb(0, 0, 0));
  color = luminosity(spot, inter);
  return (color);
}

void		fill_image(t_img *img, t_scene *scene)
{
  t_pos		count;
  int		complete;

  init_pos(&count, 0, 0);
  my_putstr("Please Wait...");
  while (count.y < img->size.y)
    {
      complete = (count.y * 100) / img->size.y;
      if ((complete % 10) == 0)
	my_printf("\rPlease Wait... %d %%", complete);
      count.x = 0;
      while (count.x < img->size.x)
	{
	  my_pixel_put_to_image(count, img->mlx_ptr,
				img, calc_image(count, scene));
	  count.x++;
	}
      count.y++;
    }
  my_putstr("\rPixel Color calculation done !\n");
}

void	init_cam(t_cam *cam)
{
  init_vec(&cam->pos, -300, 0, 150);
  init_vec(&cam->angle, 0, 0, 0);
  cam->distance = 100;
}

t_scene		*init_scene()
{
  t_scene	*scene;

  scene = my_xmalloc(sizeof(*scene));
  scene->eye = my_xmalloc(sizeof(*scene->eye));
  init_cam(scene->eye);
  scene->items = get_items();
  return (scene);
}

int		main()
{
  mlxptr	init_ptr;
  t_pos		win_size;
  t_window	win;
  t_img		img;
  t_screen	screen;
  t_scene	*scene;

  init_ptr = xmlx_init();
  init_pos(&win_size, WIN_X, WIN_Y);
  init_window(init_ptr, &win, win_size, WIN_TITLE);
  init_img(&img, win, win_size);
  init_screen(&screen, win, img);
  scene = init_scene();
  fill_image(&img, scene);
  mlx_key_hook(win.ptr, key_hook, &screen);
  mlx_expose_hook(win.ptr, expose_hook, &screen);
  mlx_loop(win.mlx_ptr);
  return (0);
}
