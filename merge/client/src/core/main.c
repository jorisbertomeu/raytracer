/*
** main.c for  in /home/mediav_j/mabm/raytracer/merge/client
** 
** Made by Jeremy Mediavilla
** Login   <mediav_j@epitech.net>
** 
** Started on  Sun Jun  8 07:30:43 2014 Jeremy Mediavilla
** Last update Sun Jun  8 07:38:36 2014 Jeremy Mediavilla
*/

#include "core.h"
#define _BSD_SOURCE

int	WIN_X;
int	WIN_Y;
int	start;

void	check_arg(int ac, char **argv)
{
  if (ac != 4)
    printerror("Usage : ./clientrt <ServerIP> <Port> <ConfFile>\n");
  if (atoi(argv[2]) <= 0 && atoi(argv[2]) >= 99999999)
    printerror("Port number must be > 0 and < 99999999\n");
}

int		main(int ac, char **argv)
{
  int		fd;
  char		*buf;

  (void)ac;
  fd = open(argv[1], O_RDONLY);
  buf = my_read_inf(fd);
  close(fd);
  get_scene(buf);
  /* t_libclient	*slib; */
  /* t_info	*info; */

  /* check_arg(ac, argv); */
  /* info = malloc(sizeof(*info)); */
  /* slib = malloc(sizeof(*slib)); */
  /* start = 0; */
  /* while (1) */
  /*   { */
  /*     fill(argv, slib, info); */
  /*     start = 1; */
  /*   } */
  return (0);
}
