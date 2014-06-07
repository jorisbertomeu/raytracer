/*
** main.c for rt in /home/jobertomeu/Work/raytracer/merge
** 
** Made by Joris Bertomeu
** Login   <jobertomeu@epitech.net>
** 
** Started on  Sat Jun  7 19:42:19 2014 Joris Bertomeu
** Last update Sun Jun  8 01:00:33 2014 nicolas ades
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
