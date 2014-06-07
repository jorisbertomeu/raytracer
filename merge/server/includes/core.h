/*
** main.h for main in /home/merran_g/work/c_igraph/rtv1
** 
** Made by Geoffrey Merran
** Login   <merran_g@epitech.net>
** 
** Started on  Fri Mar 14 16:54:50 2014 Geoffrey Merran
** Last update Sun Jun  8 00:42:59 2014 nicolas ades
*/

#ifndef MAIN_
# define MAIN_

# define WIN_X 800
# define WIN_Y 600
# define ESCAPE 65307
# define _BSD_SOURCE
# include <math.h>
# include <arpa/inet.h>
# include <stdlib.h>
# include <strings.h>
# include <string.h>
# include <libserver.h>
# include <pthread.h>
# include <gtk/gtk.h>
# include <time.h>
# include <X11/Xlib.h>
# include "gui.h"
# include "my.h"
# include "my_printf.h"
# include "parser.h"


typedef union	s_union
{
  unsigned int	clr;
  unsigned char	color[4];
}		t_union;

typedef struct	s_params
{
  int		nb_clients;
  int		port;
}		t_params;

typedef		struct s_list
{
  char		*data;
  struct s_list *next;
  struct s_list *prev;
}		t_list;

typedef struct	s_gui_serv
{
  GtkWidget	*window;
  GtkWidget	*windowf;
  GtkWidget	*imagef;
  GtkWidget	*frame;
  GtkWidget	*image;
  GtkWidget	*refresh_btn;
  GtkWidget	*png_btn;
  GtkWidget	*jpg_btn;
  GtkWidget	*full_btn;
  GtkWidget	*progress;
  GtkWidget	*label;
  char		*file;
  t_params	*params;
  time_t	start;
  time_t	finish;
  int		width;
  int		heigh;
  int		twidth;
  int		theigh;
  char		**argv;
  t_libserver	*libserver;
}		t_gui_serv;

typedef struct s_pos		t_pos;
struct				s_pos
{
  int				x;
  int				y;
};

char		*my_read_inf(int);
t_list		*create_list(char *str);
void		add_after(t_list *list, char *str);
void		add_before(t_list *list, char *str);
void		remove_from_list(t_list *list);
void		add_to_end(t_list *list, char *str);

#endif /* MAIN_ */
