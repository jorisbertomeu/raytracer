/*
** main.c for  in /home/merran_g/work/c_piscine/mkdir
**
** Made by Geoffrey Merran
** Login   <merran_g@epitech.net>
**
** Started on  Fri Oct  4 09:11:03 2013 Geoffrey Merran
** Last update Sat Jun  7 19:38:57 2014 Joris Bertomeu
*/

#include "core.h"
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <libclient.h>

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
}

void		fill(char **argv, t_libclient *slib, t_info *info)
{
  int		i = 0;
  int		pix_img;
  pthread_t	*threads;
  int		total;
  int		c;
  unsigned int	tab[18];
  int		size;
  int		n;

  size = 0;
  i = 0;
  tab[0] = 1080 * 1920 + 100;
  if (start == 0)
    init_lib(slib, argv[1], atoi(argv[2]));
  slib->flag = 1;
  info->nb_core = 4;

  info->fd_server = slib->to_server_socket;
  memset(slib->buffer, 0, 4096);
  read(slib->to_server_socket, slib->buffer, 4096);
  printf("Trame de bienvenue : %s\n", slib->buffer);

  memset(slib->buffer, 0, 4096);
  read(slib->to_server_socket, &size, sizeof(int));
  printf("Taille du fichier de conf : %d\n", size);
  n = 0;
  info->file = malloc((size + 1) * sizeof(char));
  while (n != size)
    n += read(slib->to_server_socket, &(info->file[n]), size - n);
  printf("Le client a recu le fichier de conf : %s\n", info->file);
  info->scene = get_scene(info->file);
  free(info->file);
  read(slib->to_server_socket, &(info->nb_clients), sizeof(int));
  printf("Un total de %d clients sont attendus\n", info->nb_clients);

  memset(slib->buffer, 0, 4096);
  read(slib->to_server_socket, &(info->pos_me), sizeof(int));
  printf("Je suis le client %d/%d\n", info->pos_me + 1, info->nb_clients);
  read(slib->to_server_socket, &(info->x), sizeof(int));
  read(slib->to_server_socket, &(info->y), sizeof(int));
  printf("Resolution : %dx%d\n", info->x, info->y);
  WIN_X = info->x;
  WIN_Y = info->y;
  pix_img = info->x * info->y;
  info->pix_img = pix_img;
  info->pix_by_core = malloc(info->nb_core * sizeof(int));
  i = 0;
  pix_img = pix_img / info->nb_clients;
  total = pix_img;
  while (i < info->nb_core)
    {
      if (i != info->nb_core - 1)
	{
	  info->pix_by_core[i] = pix_img / info->nb_core;
	  total = total - pix_img / info->nb_core;
	}
      else
	{
	  info->pix_by_core[i] = total;
	}
      info->max[i] = info->pix_by_core[i];
      printf("[%d] = %d --- Core %d Calcule : %d pixels\n",
	     i, info->max[i], i + 1, info->pix_by_core[i]);
      i++;
    }

  threads = malloc(info->nb_core * sizeof(*threads));
  usleep(100);
  write(slib->to_server_socket, &tab, 18 * sizeof(unsigned int));
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
  i = 0;
  while (i < info->nb_core)
    {
      info->current = i;
      pthread_create(&(threads[i]), NULL, calculate_pixel, info);
      pthread_join(threads[i], NULL);
      i++;
    }
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
