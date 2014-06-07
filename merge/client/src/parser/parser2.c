/*
** main.c for Parser RT in /home/martel_c/rendu/RT/parser
**
** Made by martelliere
** Login   <martel_c@epitech.net>
**
** Started on  Tue May 13 17:52:15 2014 martelliere
** Last update Fri Jun  6 18:06:17 2014 Geoffrey Merran
*/

#include "parser.h"

void		check_scene(int k)
{
  if (k == 2)
    fprintf(stderr, "At least one light is needed by the RT.\n");
  else if (k == 1)
    fprintf(stderr, "You must provide the eye informations.\n");
  else
    fprintf(stderr, "Missing both eye and light informations.\n");
  exit(EXIT_FAILURE);
}

t_scene		*get_scene(char *buff)
{
  t_parser	*parser;
  t_scene	*scene;
  int		i;

  parser = my_xmalloc(sizeof(*parser));
  scene = NULL;
  scene = init_scene(scene);
  parser->tab = my_martel_to_wordtab(buff);
  parser->line = 1;
  parser->k = 0;
  parser->n = 0;
  i = 0;
  while (parser->tab[parser->n] != NULL)
    {
      parser->k = my_parser(scene, parser, i);
      parser->line++;
      parser->n++;
    }
  if (parser->k != 3)
    check_scene(parser->k);
  return (scene);
}

char   		*check_conf(int ac, char **av)
{
  char		*s;
  char		*buff;
  int		fd;

  buff = NULL;
  if (ac == 2)
    {
      fd = xopen(av[1], O_RDONLY, 00644);
      buff = my_alloc_init(sizeof(char), 0);
      while ((s = get_next_line(fd)) != NULL)
	{
	  buff = my_xrealloc(buff, strlen(s) + 1);
	  strcat(buff, s);
	  xfree(s);
	}
      xclose(fd);
    }
  else
    fprintf(stderr, "Usage: ./rt <file[.conf]>\n");
  return (buff);
}
