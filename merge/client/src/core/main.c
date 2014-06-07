/*
** main.c for rt in /home/jobertomeu/Work/raytracer/merge
** 
** Made by Joris Bertomeu
** Login   <jobertomeu@epitech.net>
** 
** Started on  Sat Jun  7 19:42:19 2014 Joris Bertomeu
** Last update Sat Jun  7 20:17:34 2014 Joris Bertomeu
*/

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <libclient.h>
#include "core.h"
#define _BSD_SOURCE

int	WIN_X;
int	WIN_Y;
int	start;

typedef struct s_info	t_info;
struct s_info
{
  int	nb_clients;
  int	*pix_by_core;
  int	nb_core;
  int	current;
  int	pix_img;
  int	x;
  int	y;
  int	pos_me;
  int	max[16];
  int	fd_server;
  char	*file;
  t_scene	*scene;
  int		i;
  int		j;
  int		k;
};

void	init_int(t_info *info)
{
  info->j = 1;
  info->k = 0;
  info->i = 0;
}

t_pos	do_pos(int i, t_info *info)
{
  t_pos	pos;

  pos.x = i % info->x;
  pos.y = i / info->y;
  return (pos);
}

void	do_all(unsigned int *tab, t_info *info, t_pos pos)
{
  tab[info->k] = info->i;
  pos = do_pos(info->i, info);
  tab[info->k + 8] = calc_image(pos, info->scene);
  info->k++;
  if (info->j != 0 && info->j % 8 == 0)
    {
      write(info->fd_server, tab, 18 * sizeof(unsigned int));
      info->k = 0;
    }
  info->i += 4 * info->nb_clients;
  info->j++;
}

void	*calculate_pixel(void *data)
{
  t_info	*info;
  unsigned int	*tab;
  t_pos		pos;

  info = (t_info*) data;
  tab = malloc(18 * sizeof(int));
  init_int(info);
  while (info->i < 18)
    tab[info->i++] = 0;
  info->i = info->pos_me + info->current * info->nb_clients;
  printf("Thread Créé pour le core %d i = %d\n", info->current, info->i);
  tab[0] = info->i;
  tab[8] = 0x000000;
  while (info->j <= info->max[info->current] - 1)
    do_all(tab, info, pos);
  write(info->fd_server, tab, 18 * sizeof(unsigned int));
  printf("Thread %d a finit avec j = %d\n", info->current, info->j);
  return (NULL);
}

void	rcv_trames(t_libclient *slib, t_info *info)
{
  int	n;
  int	size;

  n = 0;
  memset(slib->buffer, 0, 4096);
  read(slib->to_server_socket, slib->buffer, 4096);
  printf("Trame de bienvenue : %s\n", slib->buffer);
  memset(slib->buffer, 0, 4096);
  read(slib->to_server_socket, &size, sizeof(int));
  n = 0;
  info->file = malloc((size + 1) * sizeof(char));
  while (n != size)
    n += read(slib->to_server_socket, &(info->file[n]), size - n);
  info->scene = get_scene(info->file);
  free(info->file);
  read(slib->to_server_socket, &(info->nb_clients), sizeof(int));
  memset(slib->buffer, 0, 4096);
  read(slib->to_server_socket, &(info->pos_me), sizeof(int));
  read(slib->to_server_socket, &(info->x), sizeof(int));
  read(slib->to_server_socket, &(info->y), sizeof(int));
  WIN_X = info->x;
  WIN_Y = info->y;
}

void	calculate_pix_core(t_info *info, int total)
{
  int	i;
  int	pix_img;

  pix_img = info->pix_img / info->nb_clients;
  i = 0;
  while (i < 4)
    {
      if (i != info->nb_core - 1)
	{
	  info->pix_by_core[i] = pix_img / 4;
	  total -= pix_img / 4;
	}
      else
	info->pix_by_core[i] = total;
      info->max[i] = info->pix_by_core[i];
      printf("[%d] = %d --- Core %d Calcule : %d pixels\n",
	     i, info->max[i], i + 1, info->pix_by_core[i]);
      i++;
    }
}

void	wait_rep(t_libclient *slib)
{
  int	c;

  c = 0;
  while (1)
    {
      read(slib->to_server_socket, &c, sizeof(char));
      if (c == 0x7f01 || c == 0x01)
	break;
      else
	{
	  printf("Bad start trame : %x\n", c);
	  exit(-1);
	}
    }
}

void	create_threads(t_info *info, pthread_t *threads)
{
  int	i;

  i = 0;
  while (i < 4)
    {
      info->current = i;
      pthread_create(&(threads[i]), NULL, calculate_pixel, info);
      pthread_join(threads[i], NULL);
      i++;
    }
}

void		fill(char **argv, t_libclient *slib, t_info *info)
{
  int		pix_img;
  pthread_t	*threads;
  int		total;
  unsigned int	tab[18];

  tab[0] = 1080 * 1920 + 100;
  if (start == 0)
    init_lib(slib, argv[1], atoi(argv[2]));
  slib->flag = 1;
  info->fd_server = slib->to_server_socket;
  rcv_trames(slib, info);
  pix_img = info->x * info->y;
  info->pix_img = pix_img;
  info->pix_by_core = malloc(4 * sizeof(int));
  total = info->pix_img;
  calculate_pix_core(info, total);
  threads = malloc(4 * sizeof(*threads));
  usleep(100);
  write(slib->to_server_socket, &tab, 18 * sizeof(unsigned int));
  wait_rep(slib);
  create_threads(info, threads);
  my_putstr("\rPixel Color calculation done !\n");
  tab[0] = 1920 * 1080 + 200;
  write(slib->to_server_socket, &tab, 18 * sizeof(unsigned int));
}

void	printerror(char *msg)
{
  fprintf(stderr, msg);
  exit(-1);
}

void	check_arg(int ac, char **argv)
{
  if (ac != 4)
    printerror("Usage : ./clientrt <ServerIP> <Port> <ConfFile>\n");
  if (atoi(argv[2]) <= 0 && atoi(argv[2]) >= 99999999)
    printerror("Port number must be > 0 and < 99999999\n");
}

int		main(int ac, char **argv)
{
  t_libclient	*slib;
  t_info	*info;

  check_arg(ac, argv);
  info = malloc(sizeof(*info));
  slib = malloc(sizeof(*slib));
  start = 0;
  while (1)
    {
      fill(argv, slib, info);
      start = 1;
    }
  return (0);
}
