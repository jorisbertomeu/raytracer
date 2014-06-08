/*
** parser.c for  in /home/mediav_j/mabm/raytracer/merge/client/src/parser/mediav_parser
** 
** Made by Jeremy Mediavilla
** Login   <mediav_j@epitech.net>
** 
** Started on  Sat Jun  7 19:15:56 2014 Jeremy Mediavilla
** Last update Sun Jun  8 07:38:26 2014 Jeremy Mediavilla
*/

#define _BSD_SOURCE
#include "core.h"

int		is_char_from_str(char c, char *delim)
{
  int		i;

  i = 0;
  while (delim[i])
    {
      if (c == delim[i])
	return (1);
      i++;
    }
  return (0);
}

int		nbr_char_begin(char *str, char *delim)
{
  int		i;

  i = 0;
  while (str[i])
    {
      if (is_char_from_str(str[i], delim) != 1)
	return (i);
      i++;
    }
  return (i);
}

char		*remove_char_begin(char *str, char *delim)
{
  int		i;
  int	        size;
  char		*final;
  int		j;

  i = 0;
  j = 0;
  size = strlen(str) - nbr_char_begin(str, delim);
  if (size <= 0)
    {
      fprintf(stderr, "Error on conf file : There is an empty line\n");
      exit(0);
    }
  final = my_xmalloc((size + 1) * sizeof(char));
  memset(final, '\0', (size + 1));
  while (is_char_from_str(str[i], delim) == 1)
    i++;
  while (str[i])
    {
      final[j] = str[i];
      i++;
      j++;
    }
  return (final);
}

int		is_xml_balise(char **tab, char *balise, int i)
{
  int		len;

  len = strlen(balise);
  while (tab[i])
    {
      if (strncmp(remove_char_begin(tab[i], "\t "), balise, len) == 0)
	return (1);
      i++;
    }
  return (0);
}

void		toto(char **tab)
{
  int		i;

  i = 0;
  while (tab[i])
    {
      /* printf("%s\n", remove_char_begin(tab[i], " ")); */
      printf("%s\n", tab[i]);
      i++;
    }
}

char		*get_closing_balise(char *balise)
{
  int		size;
  char		*closing;
  int		i;

  size = strlen(balise) + 2;
  closing = my_xmalloc(size * sizeof(char));
  memset(closing, '\0', size);
  closing[0] = '<';
  closing[1] = '/';
  i = 2;
  while (balise[i - 1] != '\0')
    {
      closing[i] = balise[i - 1];
      i++;
    }
  return (closing);
}

int		is_valid_balise(char *str)
{
  char		*balise[6];
  int		i;

  i = 0;
  balise[0] = "<EYE>";
  balise[1] = "<SPHERE>";
  balise[2] = "<PLAN>";
  balise[3] = "<SPOT>";
  balise[4] = "<CYLINDRE>";
  balise[5] = "<CONE>";
  while (i < 6)
    {
      if (strcmp(balise[i], str) == 0)
	return (1);
      i++;
    }
  return (0);
}

void		is_closing_balise(int i, char *balise, char **conf)
{
  char		*closing;
  int		tmp;

  tmp = i;
  closing = get_closing_balise(balise);
  while (conf[i])
    {
      if (is_valid_balise(conf[i]) == 1)
	{
	  fprintf(stderr, "Error on line %i : you can't open a balise \
without closing the previous one\n", (i + 1));
	  exit(0);
	}
      if (strcmp(closing, conf[i]) == 0)
	return ;
      i++;
    }
  fprintf(stderr, "Error on line %i : Balise isn't closed\n", tmp);
  exit(0);
}

void		wrong_balise(int *i, char **conf)
{
  fprintf(stderr, "Error on line %i ! Unknown balise : %s\n", (*i + 1), conf[*i]);
  exit(0);
}

int		get_ibalise_value(char *line, char *balise, int j)
{
  int		len;
  int		size;
  char		*final;
  int		i;

  i = 0;
  len = strlen(balise);
  size = 2 * len + 2;
  final = my_xmalloc(size * sizeof(char));
  memset(final, '\0', size);
  while (line[len] && line[len + 0] != '<')
    {
      if (!(line[len] >= '0' && line[len] <= '9'))
	{
	  fprintf(stderr, "Error on line %i : wrong number in %s balise\n", (j + 1), balise);
	  exit(0);
	}
      final[i] = line[len];
      i++;
      len++;
    }
  return (atoi(final));
}

float		get_fbalise_value(char *line, char *balise,  int j)
{
  int		len;
  int		size;
  char		*final;
  int		i;

  i = 0;
  len = strlen(balise);
  size = 2 * len + 2;
  final = my_xmalloc(size * sizeof(char));
  memset(final, '\0', size);
  while (line[len] && line[len + 0] != '<')
    {
      if (!(line[len] >= '0' && line[len] <= '9'))
	{
	  fprintf(stderr, "Error on line %i : wrong number in %s balise\n", (j + 1), balise);
	  exit(0);
	}
      final[i] = line[len];
      i++;
      len++;
    }
  return (atof(final));
}

float		get_fcoord_pars(char **conf, int i, char *balise)
{
  int		j;
  int		len;
  int		tmp;

  j = 0;
  tmp = i - 1;
  len = strlen(balise);
  while (j < 3)
    {
      if (conf[i] && strncmp(conf[i], balise, len) == 0)
	return (get_fbalise_value(conf[i], balise, i));
      i++;
      j++;
    }
  fprintf(stderr, "Error on line %i : Missing %s balise \
after %s\n", (tmp + 1), balise, conf[tmp]);
  exit(0);
}

void		get_item_pos(char **conf, int i, char *balise)
{
  float		pos_x;
  float		pos_y;
  float		pos_z;

  /* faire un t_vector * en fonction de rot ou pos */
  while (conf[i] && strcmp(conf[i], balise) != 0)
    i++;
  if (conf[i] && strcmp(conf[i], balise) == 0)
    i++;
  pos_x = get_fcoord_pars(conf, i, "<x>");
  pos_y = get_fcoord_pars(conf, i, "<y>");
  pos_z = get_fcoord_pars(conf, i, "<z>");
  printf("\nx : %f\ny : %f\nz : %f\n", pos_x, pos_y, pos_z);
}

void		print_rgb_error(int i)
{
  fprintf(stderr, "Error on line %i : color value must be \
between 0 and 255\n", i);
  exit(0);
}

int		get_color_rgb(int i, char **conf, char *balise)
{
  int		j;
  int		len;
  int		tmp;
  int		tmp2;

  j = 0;
  tmp = i - 1;
  len = strlen(balise);
  if (strcmp(conf[i],"<COLOR>") == 0)
    i++;
  while (j < 3)
    {
      if (strncmp(conf[i], balise, len) == 0)
	{
	  tmp2 = get_ibalise_value(conf[i], balise, i);
	  if (tmp2 < 0 || tmp2 > 255)
	    print_rgb_error(tmp);
	  return (tmp2);
	}
      i++;
      j++;
    }
  fprintf(stderr, "Error on line %i : Missing %s balise \
after %s\n", (tmp + 1), balise, conf[tmp]);
  exit(0);
}

void		get_color_info(int i, char **conf)
{
  char		*closing;
  int		r;
  int		g;
  int		b;

  while (conf[i] && strcmp(conf[i], "<COLOR>") != 0)
    i++;
  if (conf[i] && conf[i + 1] != '\0')
    i++;
  closing = get_closing_balise(conf[i]);
  r = get_color_rgb(i, conf, "<r>");
  g = get_color_rgb(i, conf, "<g>");
  b = get_color_rgb(i, conf, "<b>");
  printf("\nr : %i\ng : %i\nb : %i\n", r, g, b);
  while (conf[i] && strcmp(conf[i], closing) != 0)
    (i)++;
  if (conf[i] && conf[i + 1] != '\0')
    (i)++;
}

float		get_fbalise_value_spec(char *line, char *balise,  int j)
{
  int		len;
  int		size;
  char		*final;
  int		i;

  i = 0;
  len = strlen(balise);
  size = 2 * len + 2;
  final = my_xmalloc(size * sizeof(char));
  memset(final, '\0', size);
  while (line[len] && line[len + 0] != '<')
    {
      if (!(line[len] >= '0' && line[len] <= '9') && line[len] != '.')
	{
	  fprintf(stderr, "Error on line %i : wrong number in %s balise\n", (j + 1), balise);
	  exit(0);
	}
      final[i] = line[len];
      i++;
      len++;
    }
  return (atof(final));
}

float		get_effects_val(char *balise, char **conf, int i)
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
	  if (tmp < 0 || tmp > 1)
	    {
	      fprintf(stderr, "Error on line %i : value must be \
between 0 and 1\n", (i + 1));
	    }
	  return (tmp);
	}
      j++;
      i++;
    }
  return (0);
}

void		get_effects(int i, char **conf)
{
  float		brill;
  float		transp;
  float		refl;

  while (conf[i] && strcmp(conf[i], "<EFFECTS>") != 0)
    i++;
  if (conf[i + 1] != '\0')
    i++;
  brill = get_effects_val("<BRILL>", conf, i);
  transp = get_effects_val("<TRANSP>", conf, i);
  refl = get_effects_val("<REFLEXION>", conf, i);
  printf("b : %f\nt : %f\nr : %f\n", brill, transp, refl);
}

void		get_size_item(int i, char **conf)
{
  float		size;

  while (conf[i] && strcmp(conf[i], "<SIZE>") != 0)
    i++;
  if (conf[i] && conf[i + 1] != '\0')
    i++;
  size = 0.15;
  printf("\nSize : %f\n", size);
}

void		get_item_info(int *i, char **conf, char *balise)
{
  char		*closing;
  char		*closing2;
  int		tmp;

  (void)balise;
  closing = get_closing_balise(conf[*i]);
  if (conf[*i + 1] != '\0')
    (*i)++;
  is_closing_balise(*i, conf[*i], conf);
  tmp = *i;
  get_effects(tmp, conf);
  get_size_item(tmp, conf);
  get_color_info(tmp, conf);
  get_item_pos(conf, *i, conf[*i]);
  closing2 = get_closing_balise(conf[*i]);
  while (conf[*i] && strcmp(conf[*i], closing2) != 0)
    (*i)++;
  if (conf[*i + 1] != '\0')
    (*i)++;
  get_item_pos(conf, *i, conf[*i]);
  while (conf[*i] && strcmp(conf[*i], closing) != 0)
    (*i)++;
  /* if (conf[*i] && conf[*i + 1] != '\0') */
  /*   (*i)++; */
}

void		get_eye_info(int *i, char **conf, char *balise)
{
  char		*curr;
  char		*closing;

  (void)i;
  (void)conf;
  printf("\nEYE\n");
  if (conf[*i] && conf[*i + 1] != '\0')
    (*i)++;
  is_closing_balise(*i, conf[*i], conf);
  curr = strdup(conf[*i]);
  if (conf[*i] && !(strcmp(conf[*i], get_closing_balise(balise)) == 0))
    {
      get_item_pos(conf, *i, conf[*i]);
      closing = get_closing_balise(curr);
      while (conf[*i] && strcmp(conf[*i], closing) != 0)
	(*i)++;
      if (conf[*i] && conf[*i + 1] != '\0')
	(*i)++;
      get_item_pos(conf, *i, conf[*i]);
    }
}

void		get_spot_info(int *i, char **conf, char *balise)
{
  char		*curr;
  char		*closing;

  (void)i;
  (void)conf;
  printf("\nSPOT\n");
  if (conf[*i] && conf[*i + 1] != '\0')
    (*i)++;
  is_closing_balise(*i, conf[*i], conf);
  curr = strdup(conf[*i]);
  if (conf[*i] && !(strcmp(conf[*i], get_closing_balise(balise)) == 0))
    {
      get_item_pos(conf, *i, conf[*i]);
      closing = get_closing_balise(curr);
      while (conf[*i] && strcmp(conf[*i], closing) != 0)
	(*i)++;
      if (conf[*i] && conf[*i + 1] != '\0')
	(*i)++;
      get_color_info(*i, conf);
    }
}

void		check_balise(int *i, char *balise, char **conf, t_scene *scene)
{
  char		*tab[6];
  void		(*which_func[6])(int *, char **, char *);
  int		j;

  (void)scene;
  j = 0;
  tab[0] = "<EYE>";
  tab[1] = "<SPHERE>";
  tab[2] = "<PLAN>";
  tab[3] = "<SPOT>";
  tab[4] = "<CYLINDRE>";
  tab[5] = "<CONE>";
  which_func[0] = &get_eye_info;
  which_func[1] = &get_item_info;
  which_func[2] = &get_item_info;
  which_func[3] = &get_spot_info;
  which_func[4] = &get_item_info;
  which_func[5] = &get_item_info;
  while (j < 6)
    {
      if (strcmp(tab[j], balise) == 0)
	{
	  (*which_func[j])(i, conf, balise);
	  j = 7;
	}
      j++;
    }
  /* if (j == 6) */
  /*   wrong_balise(i, conf); */
}

char		**epure_tab(char **tab, char *delim)
{
  int		i;

  i = 0;
  while (tab[i])
    {
      tab[i] = remove_char_begin(tab[i], delim);
      i++;
    }
  return (tab);
}

void		init_scene(t_scene **scene)
{
  *scene = my_xmalloc(sizeof(**scene));
  (*scene)->items = NULL;
  (*scene)->spots = NULL;
  (*scene)->eye = my_xmalloc(sizeof(*(*scene)->eye));
}

t_scene		*get_scene(char *file)
{
  t_scene	*scene;
  char		**conf;
  int		i;

  i = 0;
  if (strlen(file) == 0)
    {
      fprintf(stderr, "Error file is empty\n");
      exit(0);
    }
  conf = my_strd_to_wordtab(file, "\n");
  if (is_xml_balise(conf, "<EYE>", 0) != 1)
    {
      fprintf(stderr, "Error on conf file : EYE missing\n");
      exit(0);
    }
  conf = epure_tab(conf, "\t ");
  init_scene(&scene);
  while (conf[i])
    {
      check_balise(&i, conf[i], conf, scene);
      i++;
    }
  return (scene);
}
