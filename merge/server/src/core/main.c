/*
** main.c for  in /home/merran_g/work/c_piscine/mkdir
**
** Made by Geoffrey Merran
** Login   <merran_g@epitech.net>
**
** Started on  Fri Oct  4 09:11:03 2013 Geoffrey Merran
** Last update Sat Jun  7 21:53:11 2014 Joris Bertomeu
*/

#include "core.h"

GdkPixbuf	*pixbuf;
GdkPixbuf	*pixbuff;
int		g_flag;
int		start;

void	print_error(char *str)
{
  char	*cmd;

  cmd = malloc(512 * sizeof(char));
  memset(cmd, 0, 512);
  sprintf(cmd, "%s > ", str);
  perror(cmd);
  free(cmd);
  exit(-1);
}

char	*search_ip_from_fd(t_libserver *libserver, int fd)
{
  char	*ip;
  int	i;

  i = 0;
  ip = malloc((INET_ADDRSTRLEN + 15) * sizeof(char));
  memset(ip, 0, (INET_ADDRSTRLEN + 15));
  while (i < 6)
    {
      if (libserver->clients[i].fd == fd)
	{
	  inet_ntop(AF_INET, &(libserver->clients[i].cli_addr.sin_addr.s_addr),
		    ip, INET_ADDRSTRLEN);
	}
      i++;
    }
  return (ip);
}

int	search_id_from_fd(t_libserver *libserver, int fd)
{
  int	i;

  i = 0;
  while (i < 6)
    {
      if (libserver->clients[i].fd == fd)
	return (i);
      i++;
    }
  return (-1);
}

void	send_all(t_libserver *libserver, char *addr_client, char *buff)
{
  int	i;
  char	c;

  (void)addr_client;
  if (strcmp(buff, "go") == 0)
    {
      i = 0;
      c =  0x01;
      while (i < 6)
	{
	  if (libserver->clients[i].active == 1)
	    write(libserver->clients[i].fd, &c, sizeof(char));
	  i++;
	}
    }
}

void	del_client(t_libserver *libserver, char *addr_client, int fd_ok)
{
  int	id;

  id = search_id_from_fd(libserver, fd_ok);
  libserver->clients[id].active = 0;
  libserver->clients[id].idsock = 0;
  libserver->clients[id].id = 0;
  libserver->clients[id].fd = 0;
  printf("%s a quitté la conversation\n", addr_client);
}

void		pixel_put_to_pixbuf(GdkPixbuf *pixbuf, int x, int y, guchar *tab)
{
  int		rowstride;
  int		n_channels;
  guchar	*pixel;
  guchar	*p;

  n_channels = gdk_pixbuf_get_n_channels(pixbuf);
  rowstride = gdk_pixbuf_get_rowstride(pixbuf);
  pixel = gdk_pixbuf_get_pixels(pixbuf);
  p = pixel + y * rowstride + x *n_channels;
  p[0] = tab[2];
  p[1] = tab[1];
  p[2] = tab[0];
}

void		stock_clr_img(t_libserver *libserver, t_gui_serv *gui)
{
  int		i;
  t_pos		count;
  t_union	trans;

  i = 0;
  while (i < 8)
    {
      if (((int*) libserver->tab)[i] == 0 &&
	  ((int*) libserver->tab)[i + 8] == 0)
	return ;
      count.x = ((int*) libserver->tab)[i] % gui->twidth;
      count.y = ((int*) libserver->tab)[i] / gui->twidth;
      trans.clr = ((int*) libserver->tab)[i + 8];
      if (start == 0)
	pixel_put_to_pixbuf(pixbuf, count.x, count.y, (guchar *) trans.color);
      else
	pixel_put_to_pixbuf(pixbuff, count.x, count.y, (guchar *) trans.color);
      i++;
    }
}

void	do_finish(t_libserver *libserver, t_gui_serv *gui)
{
  libserver->nb_finish++;
  if (libserver->nb_finish == libserver->cl_total)
    {
      time(&(gui->finish));
      libserver->flag = 0;
      g_flag = 1;
    }
}

void		parse_line(char *buff, int fd_ok, t_libserver *libserver, t_gui_serv *gui)
{
  char		*addr_client;
  static int	cmptr = 0;

  addr_client = search_ip_from_fd(libserver, fd_ok);
  if (strcmp(buff, "bye") == 0)
    del_client(libserver, addr_client, fd_ok);
  else if (((int*) libserver->tab)[0] == 1080 * 1920 + 100)
    {
      libserver->nb_ready++;
      if (libserver->nb_ready == libserver->cl_total)
	send_all(libserver, addr_client, "go");
    }
  else if (((int*) libserver->tab)[0] == 1080 * 1920 + 200)
    do_finish(libserver, gui);
  else
    {
      stock_clr_img(libserver, gui);
      if (cmptr == 0)
	time(&(gui->start));
      cmptr += 8;
      if (start == 0)
	gtk_progress_set_percentage(GTK_PROGRESS(gui->progress),
				    (gfloat)(cmptr) / (800 * 600));
    }
  free(addr_client);
}

void	init_clients(t_libserver *libserver)
{
  int	i;

  i = 0;
  while (i < 7)
    {
      libserver->clients[i].active = 0;
      libserver->clients[i].id = 0;
      libserver->clients[i].idsock = 0;
      libserver->clients[i].fd = 0;
      i++;
    }
}

void	init_lib(t_libserver *libserver, int port)
{
  if (start == 0)
    {
      init_clients(libserver);
      printf("Server port : %d\n", port);
      libserver->portno = port;
      libserver->id_client = 0;
      if ((libserver->sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	print_error("Socket Opening failed");
      bzero((char *) &(libserver->serv_addr), sizeof(libserver->serv_addr));
      libserver->serv_addr.sin_family = AF_INET;
      libserver->serv_addr.sin_addr.s_addr = INADDR_ANY;
      libserver->serv_addr.sin_port = htons(libserver->portno);
      if (bind(libserver->sockfd, (struct sockaddr *) &(libserver->serv_addr),
	       sizeof(libserver->serv_addr)) < 0)
	print_error("Bind error");
    }
  libserver->nb_ready = 0;
  libserver->flag = 1;
  libserver->nb_finish = 0;
  libserver->tab[0] = 99;
}

void	add_client(int	id, t_libserver *libserver)
{
  libserver->clients[libserver->id_client].cli_addr = libserver->cli_addr[0];
  libserver->clients[libserver->id_client].id = id;
  libserver->clients[libserver->id_client].active = 1;
  libserver->clients[libserver->id_client].idsock = libserver->id_client;
  libserver->clients[libserver->id_client].fd =
    libserver->fds[libserver->id_client];
}

int	id_exist(int id, t_libserver *libserver)
{
  int	i;

  i = 0;
  while (i < 6)
    {
      if (libserver->clients[i].id == id && libserver->clients[i].active == 1)
	return (1);
      i++;
    }
  return (0);
}

void	send_first_data(t_libserver *libserver, int nb_cl_total, t_gui_serv *gui)
{
  int	size;

  size = strlen(gui->file);
  write(libserver->newsockfd, "Bienvenue sur le MABM_RTServer !\n",
	strlen("Bienvenue sur le MABM_RTServer !\n") + 1);
  sleep(1);
  write(libserver->newsockfd, &size, sizeof(int));
  printf("Taille cnf : %d\n", (int) strlen(gui->file));
  write(libserver->newsockfd, gui->file, strlen(gui->file));
  printf("Envoie du fichier de conf\n");
  sleep(1);
  write(libserver->newsockfd, &nb_cl_total, sizeof(int));
  printf("Envoie du nombre de clients total\n");
  sleep(1);
  write(libserver->newsockfd, &(libserver->id_client), sizeof(int));
  printf("Envoie de la position du client\n");
  write(libserver->newsockfd, &(gui->twidth), sizeof(int));
  printf("Envoie de la resolution_x\n");
  write(libserver->newsockfd, &(gui->theigh), sizeof(int));
  printf("Envoie de la resolution_y\n");
}

void	send_rest(t_libserver *libserver, t_gui_serv *gui, int i)
{
  write(libserver->clients[i].fd, &(libserver->id_client), sizeof(int));
  printf("Envoie de la position du client\n");
  write(libserver->clients[i].fd, &(gui->twidth), sizeof(int));
  printf("Envoie de la resolution_x\n");
  write(libserver->clients[i].fd, &(gui->theigh), sizeof(int));
  printf("Envoie de la resolution_y\n");
}

void	send_first_data_re(t_libserver *libserver, int nb_cl_total,
			   t_gui_serv *gui)
{
  int	size;
  int	i;

  i = 0;
  size = strlen(gui->file);
  while (i < 6)
    {
      if (libserver->clients[i].active == 1)
	{
	  write(libserver->clients[i].fd, "Bienvenue sur le MABM_RTServer !\n",
		strlen("Bienvenue sur le MABM_RTServer !\n") + 1);
	  sleep(1);
	  write(libserver->clients[i].fd, &size, sizeof(int));
	  printf("Taille cnf : %d\n", (int) strlen(gui->file));
	  write(libserver->clients[i].fd, gui->file, strlen(gui->file));
	  printf("Envoie du fichier de conf\n");
	  sleep(1);
	  write(libserver->clients[i].fd, &nb_cl_total, sizeof(int));
	  printf("Envoie du nombre de clients total\n");
	  sleep(1);
	  send_rest(libserver, gui, i);
	}
      i++;
    }
}

void		check_new_client(t_libserver *libserver, int nb_cl_total, t_gui_serv *gui)
{
  char		*addr_client;

  addr_client = malloc(INET_ADDRSTRLEN * sizeof(*addr_client));
  if (id_exist(libserver->cli_addr[0].sin_addr.s_addr, libserver) == 0)
    {
      if (libserver->id_client >= 5)
	printf("Number maximum of player reached\n");
      else
	{
	  inet_ntop(AF_INET, &(libserver->cli_addr[0].sin_addr.s_addr),
		    addr_client, INET_ADDRSTRLEN);
	  printf("-------------------\nNouveau client : %s\
\n-------------------\n\n", addr_client);
	  send_first_data(libserver, nb_cl_total, gui);
	  libserver->fds[libserver->id_client] = libserver->newsockfd;
	  add_client(libserver->cli_addr[0].sin_addr.s_addr, libserver);
	  libserver->id_client++;
	}
    }
  free(addr_client);
}

void	init_fds(t_libserver *libserver)
{
  int	i;

  i = 0;
  while (i < 6)
    libserver->fds[i++] = 0;
}

int	init_fd(fd_set	*rfds, t_libserver *libserver)
{
  int	i;
  int	max;

  i = 0;
  max = libserver->sockfd + 1;
  FD_ZERO(rfds);
  FD_SET(libserver->sockfd, rfds);
  while (i < libserver->id_client)
    {
      FD_SET(libserver->fds[i], rfds);
      max = (libserver->fds[i] >= max) ? libserver->fds[i] + 1 : max;
      i++;
    }
  return (max);
}

void	do_sock_fd(t_libserver *libserver, int client_max, t_gui_serv *gui)
{
  libserver->clilen = sizeof(libserver->cli_addr[0]);
  libserver->newsockfd = accept(libserver->sockfd,
				(struct sockaddr *)&(libserver->cli_addr[0]),
				(socklen_t*) &(libserver->clilen));
  check_new_client(libserver, client_max, gui);
  if (libserver->newsockfd < 0)
    print_error("Acception client error");
}

void	do_sock_client(t_libserver *libserver, fd_set rfds, t_gui_serv *gui)
{
  int	i;
  int	total;

  i = 0;
  total = 18 * sizeof(unsigned int);
  while (i < 6)
    {
      libserver->n = 0;
      if (FD_ISSET(libserver->fds[i], &rfds) == 1)
	{
	  memset(libserver->buffer, 0, 4096);
	  while (libserver->n != total)
	    libserver->n += read(libserver->fds[i], &(libserver->tab[libserver->n]),
				 total - libserver->n);
	  if (libserver->n <= 0)
	    print_error("Socket Read error");
	  else
	    {
	      libserver->current_id_fd = i;
	      parse_line(libserver->buffer, libserver->fds[i], libserver, gui);
	      return;
	    }
	}
      i++;
    }
}

void	init_all_serv(t_libserver *libserver, t_params *params)
{
  init_lib(libserver, params->port);
  if (start == 0)
    {
      libserver->cl_total = params->nb_clients;
      init_fds(libserver);
      listen(libserver->sockfd, 5);
      printf("Waiting connection on port %d ...\n", libserver->portno);
    }
}

void	decision(t_gui_serv *gui, fd_set rfds, t_libserver *libserver)
{
  if (FD_ISSET(libserver->sockfd, &rfds) == 1)
    do_sock_fd(libserver, gui->params->nb_clients, gui);
  else
    do_sock_client(libserver, rfds, gui);
}

void		*server(void *ok)
{
  t_libserver	*libserver;
  t_gui_serv	*gui;
  fd_set	rfds;
  int		retval;
  int		max;

  libserver = malloc(sizeof(*libserver));
  gui = ok;
  libserver = gui->libserver;
  init_all_serv(libserver, gui->params);
  while (1)
    {
      max = init_fd(&rfds, libserver);
      retval = select(max, &rfds, NULL, NULL, 0);
      if (retval == -1)
	printf("Error : Select\n");
      else if (retval == EINTR)
	printf("Signal Caught\n");
      else if (retval <= 6)
	decision(gui, rfds, libserver);
      else
	printf("Error - Max : %d retval : %d\n", max, retval);
    }
  return (0);
}

void	refresh_img(GtkWidget *useless, t_gui_serv *gui)
{
  (void)useless;
  gtk_image_set_from_pixbuf(GTK_IMAGE(gui->image), pixbuf);
  gtk_widget_show_all(gui->window);
}

void	refresh_imgf(GtkWidget *useless, t_gui_serv *gui)
{
  (void)useless;
  gtk_image_set_from_pixbuf(GTK_IMAGE(gui->imagef), pixbuff);
  gtk_widget_show_all(gui->windowf);
}

void	*refresh_img_func_full(void *data)
{
  t_gui_serv	*gui;

  gui = data;
  g_flag = 0;
  while (g_flag == 0)
    {
      refresh_imgf(NULL, gui);
      sleep(1);
    }
  refresh_imgf(NULL, gui);
  return (NULL);
}

void		*refresh_img_func(void *data)
{
  char		*final;
  t_gui_serv	*gui;

  gui = data;
  final = malloc(128 * sizeof(char));
  while (g_flag == 0)
    {
      refresh_img(NULL, gui);
      sleep(1);
    }
  memset(final, 0, 128);
  sprintf(final, "Calculé en moins de %d minute(s) et %d seconde(s)",
	  (int)(gui->finish - gui->start) / 60,
	  (int)(gui->finish - gui->start) % 60);
  refresh_img(NULL, gui);
  gui->label = gtk_label_new(final);
  gtk_fixed_put(GTK_FIXED(gui->frame),
		gui->label, 50, 20);
  gtk_widget_show_all(gui->window);
  return (NULL);
}

int		there_is_ext(const gchar *str, char *ext)
{
  int		i;
  int		j;

  i = 0;
  j = 0;
  while (str[i])
    {
      if (str[i] == ext[j])
	     {
	      i++;
	      j++;
	      if (j == (int)strlen(ext))
	        return (0);
	     }
      else
        i++;
    }
  return (-1);
}

void	widget_destroy(GtkWidget *w, GtkWidget *ok)
{
  (void)w;
  gtk_widget_destroy(ok);
}

gchar		*clear_path(const gchar *str, char *ext)
{
  char		*res;

  if (!str)
    return (NULL);
  if (there_is_ext(str, ext) != 0)
    {
      res = malloc((strlen((char *)str) + strlen(ext)) * sizeof(*res));
      strcpy(res, (char *)str);
      res = strcat(res, ext);
      return (res);
    }
  else
    {
      res = malloc((strlen((char *)str) + 1) * sizeof(*res));
      strcpy(res, (char *) str);
      return (res);
    }
}

void		write_to_jpg(GtkWidget *widget, GtkWidget *select)
{
  GError	*error;
  const gchar	*path;
  char		*name;

  (void)widget;
  (void)select;
  error = NULL;
  path = gtk_file_selection_get_filename(GTK_FILE_SELECTION(select));
  name = clear_path(path, ".jpeg");
  gdk_pixbuf_save(pixbuf, name, "jpeg", &error, NULL);
  widget_destroy(NULL, select);
}

void		save_jpg(GtkWidget *widget, GdkPixbuf *pixbuf)
{
  GtkWidget	*selection;

  (void)widget;
  (void)pixbuf;
  selection = gtk_file_selection_new("Path Selection");
  gtk_window_set_modal(GTK_WINDOW(selection), TRUE);
  gtk_file_selection_hide_fileop_buttons(GTK_FILE_SELECTION(selection));
  gtk_widget_show(selection);
  g_signal_connect(G_OBJECT(GTK_FILE_SELECTION(selection)->ok_button),
		   "clicked", G_CALLBACK(write_to_jpg), selection);
  g_signal_connect(G_OBJECT(GTK_FILE_SELECTION(selection)->cancel_button),
		   "clicked", G_CALLBACK(widget_destroy), selection);
}

void		write_to_png(GtkWidget *widget, GtkWidget *select)
{
  GError	*error;
  const gchar	*path;
  char		*name;

  (void)widget;
  error = NULL;
  path = gtk_file_selection_get_filename(GTK_FILE_SELECTION(select));
  name = clear_path(path, ".png");
  gdk_pixbuf_save(pixbuf, name, "png", &error, NULL);
  widget_destroy(NULL, select);
}

void		save_png(GtkWidget *widget, GdkPixbuf *pixbuf)
{
  GtkWidget	*selection;

  (void)widget;
  (void)pixbuf;
  selection = gtk_file_selection_new("Path Selection");
  gtk_window_set_modal(GTK_WINDOW(selection), TRUE);
  gtk_file_selection_hide_fileop_buttons(GTK_FILE_SELECTION(selection));
  gtk_widget_show(selection);
  g_signal_connect(G_OBJECT(GTK_FILE_SELECTION(selection)->ok_button),
		   "clicked", G_CALLBACK(write_to_png), selection);
  g_signal_connect(G_OBJECT(GTK_FILE_SELECTION(selection)->cancel_button),
		   "clicked", G_CALLBACK(widget_destroy), selection);
}

void		write_to_png_full(GtkWidget *widget, GtkWidget *select)
{
  GError	*error;
  const gchar	*path;
  char		*name;

  (void)widget;
  error = NULL;
  path = gtk_file_selection_get_filename(GTK_FILE_SELECTION(select));
  name = clear_path(path, ".png");
  gdk_pixbuf_save(pixbuff, name, "png", &error, NULL);
  widget_destroy(NULL, select);
}

void		save_png_full(GtkWidget *widget, GdkPixbuf *pixbuf)
{
  GtkWidget	*selection;

  (void)widget;
  (void)pixbuf;
  selection = gtk_file_selection_new("Path Selection");
  gtk_window_set_modal(GTK_WINDOW(selection), TRUE);
  gtk_file_selection_hide_fileop_buttons(GTK_FILE_SELECTION(selection));
  gtk_widget_show(selection);
  g_signal_connect(G_OBJECT(GTK_FILE_SELECTION(selection)->ok_button),
		   "clicked", G_CALLBACK(write_to_png_full), selection);
  g_signal_connect(G_OBJECT(GTK_FILE_SELECTION(selection)->cancel_button),
		   "clicked", G_CALLBACK(widget_destroy), selection);
}

void	create_btn_w(t_gui_serv *gui)
{
  gui->refresh_btn = gtk_button_new_with_label("Refresh");
  gtk_widget_set_size_request(gui->refresh_btn, 100, 30);
  gtk_fixed_put(GTK_FIXED(gui->frame), gui->refresh_btn, 400, 700);

  gui->png_btn = gtk_button_new_with_label("Save to PNG");
  gtk_widget_set_size_request(gui->png_btn, 100, 30);
  gtk_fixed_put(GTK_FIXED(gui->frame), gui->png_btn, 50, 700);

  gui->jpg_btn = gtk_button_new_with_label("Save to JPG");
  gtk_widget_set_size_request(gui->jpg_btn, 100, 30);
  gtk_fixed_put(GTK_FIXED(gui->frame), gui->jpg_btn, 750, 700);

  gui->full_btn = gtk_button_new_with_label("FullRes");
  gtk_widget_set_size_request(gui->full_btn, 100, 30);
  gtk_fixed_put(GTK_FIXED(gui->frame), gui->full_btn, 225, 700);
}

void	init_win_serv(t_gui_serv *gui)
{
  gui->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(gui->window), "Raytracer Server");
  gtk_window_set_default_size(GTK_WINDOW(gui->window), 900, 750);
  gtk_window_set_position(GTK_WINDOW(gui->window), GTK_WIN_POS_CENTER);
  gui->frame = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(gui->window), gui->frame);
  gui->progress = gtk_progress_bar_new();
  gtk_progress_configure(GTK_PROGRESS(gui->progress), 0, 0, 100);
  gtk_widget_set_size_request(gui->progress, 800, 30);
  gtk_fixed_put(GTK_FIXED(gui->frame), gui->progress, 50, 660);
}

void	call_all(t_gui_serv *gui)
{
  gui->twidth = gui->width;
  gui->theigh = gui->heigh;
  start = 1;
  init_all_serv(gui->libserver, gui->params);
  send_first_data_re(gui->libserver, gui->params->nb_clients, gui);
}

void	get_key_event(GtkWidget *w, GdkEventKey *event)
{
  if (strcmp(gdk_keyval_name(event->keyval), "Escape") == 0)
    gtk_widget_destroy(w);
  if (strcmp(gdk_keyval_name(event->keyval), "s") == 0)
    save_png_full(w, pixbuff);
}

void		init_res_func(t_gui_serv *gui)
{
  gui->windowf = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(gui->windowf), "Raytracer Server - FULLRES");
  gtk_window_set_decorated(GTK_WINDOW(gui->windowf), FALSE);
  gtk_window_fullscreen(GTK_WINDOW(gui->windowf));
}

void		manage_call_res(t_gui_serv *gui)
{
  g_signal_connect(G_OBJECT(gui->windowf), "delete-event",
		   G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(G_OBJECT(gui->windowf), "key-release-event",
		   G_CALLBACK(get_key_event), NULL);
}

void		full_res_func(GtkWidget *w, t_gui_serv *gui)
{
  GtkWidget	*frame;
  pthread_t	thread;
  GdkScreen	*screen;
  int		x;
  int		y;

  (void)w;
  call_all(gui);
  gtk_rc_parse("./sys/rc.cnf");
  init_res_func(gui);
  frame = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(gui->windowf), frame);
  gui->imagef = gtk_image_new_from_pixbuf(pixbuff);
  gtk_widget_set_size_request(gui->imagef, gui->width, gui->heigh);
  screen = gdk_screen_get_default();
  x = gdk_screen_get_width(screen);
  y = gdk_screen_get_height(screen);
  gtk_fixed_put(GTK_FIXED(frame), gui->imagef,
		(gint)((x / 2) - (gui->width / 2)),
		(gint)((y / 2) - (gui->heigh / 2)));
  pthread_create(&thread, NULL, refresh_img_func_full, gui);
  gtk_widget_show_all(gui->windowf);
  manage_call_res(gui);
  gtk_main();
}

void		start_gtk(t_gui_serv *gui)
{
  pthread_t	thread;

  init_win_serv(gui);
  gui->image = gtk_image_new_from_pixbuf(pixbuf);
  gtk_widget_set_size_request(gui->image, 800, 600);
  gtk_fixed_put(GTK_FIXED(gui->frame), gui->image, 50, 50);
  create_btn_w(gui);

  pthread_create(&thread, NULL, refresh_img_func, (void*)gui);
  gtk_widget_show_all(gui->window);

  g_signal_connect(G_OBJECT(gui->window), "delete-event",
		   G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(G_OBJECT(gui->refresh_btn), "clicked",
		   G_CALLBACK(refresh_img), gui);
  g_signal_connect(G_OBJECT(gui->png_btn), "clicked",
		   G_CALLBACK(save_png), pixbuf);
  g_signal_connect(G_OBJECT(gui->jpg_btn), "clicked",
		   G_CALLBACK(save_jpg), pixbuf);
  g_signal_connect(G_OBJECT(gui->full_btn), "clicked",
		   G_CALLBACK(full_res_func), gui);

  gtk_main();
}

void            *my_xrealloc(char *str, int size)
{
  char          *new_str;

  if (str == NULL)
    exit(EXIT_FAILURE);
  if (size == 0)
    return (str);
  new_str = malloc((strlen(str) + size + 1) * sizeof(char));
  *new_str = '\0';
  my_strcat(new_str, str);
  free(str);
  return (new_str);
}

char   		*check_conf(char *arg)
{
  char		*buff;
  int		fd;

  buff = NULL;
  if ((fd = open(arg, O_RDONLY, 00644)) == -1)
    {
      fprintf(stderr, "File %s not fount\n", arg);
      exit(-1);
    }
  buff = my_read_inf(fd);
  close(fd);
  return (buff);
}

void	fill_resol(t_gui_serv *gui, char **argv)
{
  gui->width = atoi(argv[3]);
  gui->heigh = atoi(argv[4]);
  gui->twidth = 800;
  gui->theigh = 600;
}

void		start_serv(int ac, char **argv)
{
  t_gui_serv	*gui;
  pthread_t	thread;

  start = 0;
  gui = malloc(sizeof(*gui));
  gui->libserver = malloc(sizeof(t_libserver));
  gui->file = check_conf(argv[5]);
  gui->params = malloc(sizeof(*(gui->params)));
  gui->params->nb_clients = atoi(argv[2]);
  gui->params->port = atoi(argv[1]);
  gui->argv = argv;
  fill_resol(gui, argv);
  g_flag = 0;
  XInitThreads();
  gtk_init(&ac, &argv);
  pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, 0, 8, 800, 600);
  pixbuff = gdk_pixbuf_new(GDK_COLORSPACE_RGB, 0, 8, gui->width, gui->heigh);
  pthread_create(&thread, NULL, server, gui);
  start_gtk(gui);
}

int		main(int ac, char *argv[])
{
  if (ac != 6)
    {
      printf("USAGE: ./rt_server <Port> <Nb_clients_max>\
 <Width> <Heigh> <Conf File>\n");
      exit(-1);
    }
  else if (atoi(argv[1]) >= 1 && atoi(argv[1]) <= 999999
	   && atoi(argv[2]) >= 1 && atoi(argv[2]) <= 6)
    start_serv(ac, argv);
  else
    {
      printf("You must enter a valid port and a number maximum of 6 peers\n");
      exit(-1);
    }
  return (0);
}
