/*
** main.c for paint in /home/jobertomeu/Work/raytracer/graphic
** 
** Made by Joris Bertomeu
** Login   <jobertomeu@epitech.net>
** 
** Started on  Tue Jun  3 12:48:10 2014 Joris Bertomeu
** Last update Sat Jun  7 23:48:42 2014 Joris Bertomeu
*/

#include <stdio.h>
#include <gtk/gtk.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "gui.h"

GdkPixbuf	*load_pixbuf_from_file(char *filename)
{
  GError	*error;
  GdkPixbuf	*pixbuf;

  error = NULL;
  pixbuf = gdk_pixbuf_new_from_file(filename, &error);
  if (pixbuf == NULL)
    {
      g_print("Error loading file: %d : %s\n", error->code, error->message);
      g_error_free(error);
      exit(1);
    }
  return (pixbuf);
}

void	quit(GtkWidget *useless, t_gui *gui)
{
  exit(0);
}

void	edition_click()
{
  printf("Edition_click\n");
}

void	init_win_rt(t_gui *gui)
{
  gui->rt.sys.image = load_pixbuf_from_file ("launching.jpg");
  gdk_pixbuf_render_pixmap_and_mask(gui->rt.sys.image,
				    &(gui->rt.sys.background), NULL, 0);
  gui->rt.sys.style = gtk_style_new();
  gui->rt.sys.style->bg_pixmap[0] = gui->rt.sys.background;
  gui->rt.sys.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(gui->rt.sys.window), GTK_WIN_POS_CENTER);
  gtk_window_set_title(GTK_WINDOW(gui->rt.sys.window), "Raytracer - Launching");
  gtk_window_set_decorated(GTK_WINDOW(gui->rt.sys.window), FALSE);
  gtk_window_set_default_size(GTK_WINDOW(gui->rt.sys.window), 400, 200);
  gtk_widget_set_style(GTK_WIDGET(gui->rt.sys.window),
		       GTK_STYLE (gui->rt.sys.style));
  gtk_window_set_transient_for(GTK_WINDOW (gui->rt.sys.window),
			       (GtkWindow*) gui->main.sys.window);
  gui->rt.sys.frame = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(gui->rt.sys.window), gui->rt.sys.frame);
}

void	init_button_load(t_gui *gui)
{
  gui->rt.buttons.load = gtk_button_new_with_label("Open File");
  gtk_widget_set_size_request(gui->rt.buttons.load, 80, 30);
  gtk_fixed_put(GTK_FIXED(gui->rt.sys.frame),
		gui->rt.buttons.load, 300, 30);
}

void	init_button_go(t_gui *gui)
{
  gui->rt.buttons.go = gtk_button_new_with_label("Start Raycasting !");
  gtk_widget_set_size_request(gui->rt.buttons.go, 120, 30);
  gtk_fixed_put(GTK_FIXED(gui->rt.sys.frame),
		gui->rt.buttons.go, 230, 80);
}

void		*cancel_rt(GtkWidget *useless, t_gui *gui)
{
  gtk_widget_set_sensitive(gui->main.sys.window, TRUE);
  gtk_widget_destroy(gui->rt.sys.window);
}

void	init_button_can_rt(t_gui *gui)
{
  gui->rt.buttons.can = gtk_button_new_with_label("Cancel");
  gtk_widget_set_size_request(gui->rt.buttons.can, 120, 30);
  gtk_fixed_put(GTK_FIXED(gui->rt.sys.frame),
		gui->rt.buttons.can, 50, 80);
}

void	init_entry_path(t_gui *gui)
{
  gui->rt.buttons.entry = gtk_entry_new();
  gtk_widget_set_size_request(gui->rt.buttons.entry, 280, 30);
  gtk_fixed_put(GTK_FIXED(gui->rt.sys.frame),
		gui->rt.buttons.entry, 20, 30);
}

void	init_all_buttons_rt(t_gui *gui)
{
  init_button_load(gui);
  init_entry_path(gui);
  init_button_go(gui);
  init_button_can_rt(gui);
}

void		open_file(GtkWidget *useless, t_gui *gui)
{
  char		*filename;
  GtkWidget	*dialog;
  int		flag;

  flag = 0;
  dialog = gtk_file_chooser_dialog_new("Open File",
					(GtkWindow*) gui->rt.sys.window,
					GTK_FILE_CHOOSER_ACTION_OPEN,
					GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
					GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
					NULL);
  if (gtk_dialog_run(GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
    {
      flag = 1;
      filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
    }
  gtk_widget_destroy(dialog);
  if (flag == 1)
    {
      gtk_entry_set_text(GTK_ENTRY(gui->rt.buttons.entry), filename);
      g_free(filename);
    }
}

void	launch_rt_go(GtkWidget *w, t_gui *gui)
{
  (void)w;
  strcpy(gui->args.conf,
  	 gtk_entry_get_text(GTK_ENTRY(gui->rt.buttons.entry)));
  gtk_widget_set_sensitive(gui->main.sys.window, TRUE);
  gtk_widget_destroy(gui->rt.sys.window);
  
  /* gtk_widget_destroy(gui->main.sys.window); */
  printf("-- RESUM --\n");
  printf("Port : %s\n", gui->args.port);
  printf("Nb_Max : %s\n", gui->args.nb_max);
  printf("X : %s\n", gui->args.x);
  printf("Y : %s\n", gui->args.y);
  printf("conf : %s\n", gui->args.conf);
}

void	rt_click(GtkWidget *useless, t_gui *gui)
{
  gtk_widget_set_sensitive(gui->main.sys.window, FALSE);
  init_win_rt(gui);
  init_all_buttons_rt(gui);
  gtk_widget_show_all(gui->rt.sys.window);
  g_signal_connect(G_OBJECT(gui->rt.sys.window), "delete-event",
		   G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(G_OBJECT(gui->rt.buttons.load), "clicked",
		   G_CALLBACK(open_file), gui);
  g_signal_connect(G_OBJECT(gui->rt.buttons.can), "clicked",
		   G_CALLBACK(cancel_rt), gui);
  g_signal_connect(G_OBJECT(gui->rt.buttons.go), "clicked",
		   G_CALLBACK(launch_rt_go), gui);
  gtk_main();
}

GList	*init_resol_list()
{
  GList	*list;

  list = NULL;
  list = g_list_append(list, g_strdup_printf("800x600"));
  list = g_list_append(list, g_strdup_printf("1024x768"));
  list = g_list_append(list, g_strdup_printf("1080x1920"));
  return (list);
}

GList	*init_antia_list()
{
  GList	*list;

  list = NULL;
  list = g_list_append(list, g_strdup_printf("x2"));
  list = g_list_append(list, g_strdup_printf("x4"));
  list = g_list_append(list, g_strdup_printf("x8"));
  list = g_list_append(list, g_strdup_printf("x16"));
  return (list);
}

GList	*init_cl_list()
{
  GList	*list;

  list = NULL;
  list = g_list_append(list, g_strdup_printf("1"));
  list = g_list_append(list, g_strdup_printf("2"));
  list = g_list_append(list, g_strdup_printf("3"));
  list = g_list_append(list, g_strdup_printf("4"));
  list = g_list_append(list, g_strdup_printf("5"));
  list = g_list_append(list, g_strdup_printf("6"));
  return (list);
}

GList	*init_mode_list()
{
  GList	*list;

  list = NULL;
  list = g_list_append(list, g_strdup_printf("Sépia"));
  list = g_list_append(list, g_strdup_printf("Noir & Blanc"));
  list = g_list_append(list, g_strdup_printf("Andy Warhol"));
  list = g_list_append(list, g_strdup_printf("Surexposé"));
  list = g_list_append(list, g_strdup_printf("Balance des blancs"));
  return (list);
}

void		*save_options(GtkWidget *useless, t_gui *gui)
{
  GtkWidget	*dialog;

  strcpy(gui->args.nb_max,
	 gtk_entry_get_text(GTK_ENTRY(GTK_COMBO(gui->opt.combo.nb_clients)->entry)));
  strcpy(gui->args.x,
	 gtk_entry_get_text(GTK_ENTRY(GTK_COMBO(gui->opt.combo.resol)->entry)));
  strcpy(gui->args.y,
	 gtk_entry_get_text(GTK_ENTRY(GTK_COMBO(gui->opt.combo.resol)->entry)));
  printf("-- RESUM --\n");
  printf("Port : %s\n", gui->args.port);
  printf("Nb_Max : %s\n", gui->args.nb_max);
  printf("X : %s\n", gui->args.x);
  printf("Y : %s\n", gui->args.y);
  printf("conf : %s\n", gui->args.conf);
  dialog = gtk_message_dialog_new((GtkWindow*) gui->opt.sys.window,
				  GTK_DIALOG_MODAL,
				  GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
				  "Settings saved !");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
  gtk_widget_set_sensitive(gui->main.sys.window, TRUE);
  gtk_widget_destroy(gui->opt.sys.window);
}

void		*cancel_options(GtkWidget *useless, t_gui *gui)
{
  gtk_widget_set_sensitive(gui->main.sys.window, TRUE);
  gtk_widget_destroy(gui->opt.sys.window);
}

void	init_win_opt(t_gui *gui)
{
  gui->opt.sys.image = load_pixbuf_from_file ("config.jpg");
  gdk_pixbuf_render_pixmap_and_mask(gui->opt.sys.image,
				    &(gui->opt.sys.background), NULL, 0);
  gui->opt.sys.style = gtk_style_new();
  gui->opt.sys.style->bg_pixmap[0] = gui->opt.sys.background;
  gui->opt.sys.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(gui->opt.sys.window), GTK_WIN_POS_CENTER);
  gtk_window_set_title(GTK_WINDOW(gui->opt.sys.window), "Raytracer - Options");
  gtk_window_set_decorated(GTK_WINDOW(gui->opt.sys.window), FALSE);
  gtk_window_set_default_size(GTK_WINDOW(gui->opt.sys.window), 350, 300);
  gtk_widget_set_style(GTK_WIDGET(gui->opt.sys.window),
		       GTK_STYLE (gui->opt.sys.style));
  gtk_window_set_transient_for(GTK_WINDOW (gui->opt.sys.window),
			       (GtkWindow*) gui->main.sys.window);
  gui->opt.sys.frame = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(gui->opt.sys.window), gui->opt.sys.frame);
}

void	init_resol(t_gui *gui)
{
  gui->opt.list.list_resol = init_resol_list();
  gui->opt.labels.resol_l = gtk_label_new("Resolution : ");
  gtk_fixed_put(GTK_FIXED(gui->opt.sys.frame), gui->opt.labels.resol_l, 30, 50);
  gui->opt.combo.resol = gtk_combo_new();
  gtk_entry_set_editable(GTK_ENTRY(GTK_COMBO(gui->opt.combo.resol)->entry),
			 FALSE);
  gtk_combo_set_popdown_strings(GTK_COMBO(gui->opt.combo.resol),
				gui->opt.list.list_resol) ;
  gtk_entry_set_text(GTK_ENTRY(GTK_COMBO(gui->opt.combo.resol)->entry),
		     "800x600");
  gtk_fixed_put(GTK_FIXED(gui->opt.sys.frame), gui->opt.combo.resol, 150, 45);
}

void	init_antia(t_gui *gui)
{
  gui->opt.list.list_antia = init_antia_list();
  gui->opt.labels.antialias_l = gtk_label_new("Antialiasing : ");
  gtk_fixed_put(GTK_FIXED(gui->opt.sys.frame),
		gui->opt.labels.antialias_l, 30, 100);
  gui->opt.combo.antialias = gtk_combo_new();
  gtk_entry_set_editable(GTK_ENTRY(GTK_COMBO(gui->opt.combo.antialias)->entry),
			 FALSE);
  gtk_combo_set_popdown_strings(GTK_COMBO(gui->opt.combo.antialias),
				gui->opt.list.list_antia) ;
  gtk_entry_set_text(GTK_ENTRY(GTK_COMBO(gui->opt.combo.antialias)->entry),
		     "x2");
  gtk_fixed_put(GTK_FIXED(gui->opt.sys.frame), gui->opt.combo.antialias,
		150, 95);
}

void	init_clients(t_gui *gui)
{
  gui->opt.list.list_client = init_cl_list();
  gui->opt.labels.nb_clients_l = gtk_label_new("Nombre clients : ");
  gtk_fixed_put(GTK_FIXED(gui->opt.sys.frame),
		gui->opt.labels.nb_clients_l, 30, 150);
  gui->opt.combo.nb_clients = gtk_combo_new();
  gtk_entry_set_editable(GTK_ENTRY(GTK_COMBO(gui->opt.combo.nb_clients)->entry),
			 FALSE);
  gtk_combo_set_popdown_strings(GTK_COMBO(gui->opt.combo.nb_clients),
				gui->opt.list.list_client) ;
  gtk_entry_set_text(GTK_ENTRY(GTK_COMBO(gui->opt.combo.nb_clients)->entry),
		     "1");
  gtk_fixed_put(GTK_FIXED(gui->opt.sys.frame), gui->opt.combo.nb_clients,
		150, 145);
}

void	init_mode(t_gui *gui)
{
  gui->opt.list.list_mode = init_mode_list();
  gui->opt.labels.mode_l = gtk_label_new("Mode de rendu : ");
  gtk_fixed_put(GTK_FIXED(gui->opt.sys.frame), gui->opt.labels.mode_l, 30, 200);
  gui->opt.combo.mode = gtk_combo_new();
  gtk_entry_set_editable(GTK_ENTRY(GTK_COMBO(gui->opt.combo.mode)->entry),
			 FALSE);
  gtk_combo_set_popdown_strings(GTK_COMBO(gui->opt.combo.mode),
				gui->opt.list.list_mode) ;
  gtk_entry_set_text(GTK_ENTRY(GTK_COMBO(gui->opt.combo.mode)->entry), "Sépia");
  gtk_fixed_put(GTK_FIXED(gui->opt.sys.frame), gui->opt.combo.mode, 150, 195);
}

void	init_all_combo(t_gui *gui)
{
  init_resol(gui);
  init_antia(gui);
  init_clients(gui);
  init_mode(gui);
}

void	init_button_ok_opt(t_gui *gui)
{
  gui->opt.buttons.ok_btn = gtk_button_new_with_label("OK");
  gtk_widget_set_size_request(gui->opt.buttons.ok_btn, 100, 25);
  gtk_fixed_put(GTK_FIXED(gui->opt.sys.frame),
		gui->opt.buttons.ok_btn, 50, 250);
}

void	init_button_cancel_opt(t_gui *gui)
{
  gui->opt.buttons.can_btn = gtk_button_new_with_label("Cancel");
  gtk_widget_set_size_request(gui->opt.buttons.can_btn, 100, 25);
  gtk_fixed_put(GTK_FIXED(gui->opt.sys.frame),
		gui->opt.buttons.can_btn, 200, 250);
}

void	init_all_buttons_opt(t_gui *gui)
{
  init_button_ok_opt(gui);
  init_button_cancel_opt(gui);
}

void	options_click(GtkWidget *useless, t_gui *gui)
{
  gtk_widget_set_sensitive(gui->main.sys.window, FALSE);
  init_win_opt(gui);
  init_all_combo(gui);
  init_all_buttons_opt(gui);
  gtk_widget_show_all(gui->opt.sys.window);
  g_signal_connect(G_OBJECT(gui->opt.sys.window), "delete-event",
		   G_CALLBACK(cancel_options), gui);
  g_signal_connect(G_OBJECT(gui->opt.buttons.ok_btn), "clicked",
		   G_CALLBACK(save_options), gui);
  g_signal_connect(G_OBJECT(gui->opt.buttons.can_btn), "clicked",
		   G_CALLBACK(cancel_options), gui);
  gtk_main();
}

void	credits_click()
{
  printf("Credits_click\n");
}

void	init_sys(t_gui *gui)
{
  gui->main.sys.image = load_pixbuf_from_file ("img.jpg");
  gdk_pixbuf_render_pixmap_and_mask(gui->main.sys.image,
				    &(gui->main.sys.background), NULL, 0);
  gui->main.sys.style = gtk_style_new();
  gui->main.sys.style->bg_pixmap[0] = gui->main.sys.background;
  gui->main.sys.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(gui->main.sys.window), "Raytracer Launcher");
  gtk_window_set_decorated(GTK_WINDOW(gui->main.sys.window), FALSE);
  gtk_window_set_default_size(GTK_WINDOW (gui->main.sys.window), 800, 600);
  gtk_window_set_position(GTK_WINDOW(gui->main.sys.window), GTK_WIN_POS_CENTER);
  gtk_widget_set_style(GTK_WIDGET(gui->main.sys.window),
		       GTK_STYLE (gui->main.sys.style));
  gtk_window_set_transient_for(GTK_WINDOW (gui->main.sys.window), NULL);
  gui->main.sys.frame = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(gui->main.sys.window), gui->main.sys.frame);
}

void	init_b_edition(t_gui *gui)
{
  gui->main.buttons.edition = gtk_button_new_with_label("Edition");
  gtk_widget_set_size_request(gui->main.buttons.edition, 200, 50);
  gtk_fixed_put(GTK_FIXED(gui->main.sys.frame),
		gui->main.buttons.edition, 300, 50);
}

void	init_b_rt(t_gui *gui)
{
  gui->main.buttons.rt = gtk_button_new_with_label("Launch RayTracer");
  gtk_widget_set_size_request(gui->main.buttons.rt, 200, 50);
  gtk_fixed_put(GTK_FIXED(gui->main.sys.frame), gui->main.buttons.rt, 300, 150);
}

void	init_b_options(t_gui *gui)
{
  gui->main.buttons.options = gtk_button_new_with_label("Options");
  gtk_widget_set_size_request(gui->main.buttons.options, 200, 50);
  gtk_fixed_put(GTK_FIXED(gui->main.sys.frame),
		gui->main.buttons.options, 300, 250);
}

void	init_b_quit(t_gui *gui)
{
  gui->main.buttons.quit = gtk_button_new_with_label("Quit");
  gtk_widget_set_size_request(gui->main.buttons.quit, 200, 50);
  gtk_fixed_put(GTK_FIXED(gui->main.sys.frame),
		gui->main.buttons.quit, 300, 350);
}

void	init_b_cred(t_gui *gui)
{
  gui->main.buttons.cred = gtk_button_new_with_label("Credits");
  gtk_widget_set_size_request(gui->main.buttons.cred, 200, 50);
  gtk_fixed_put(GTK_FIXED(gui->main.sys.frame),
		gui->main.buttons.cred, 300, 450);
}

void	init_all_buttons(t_gui *gui)
{
  init_b_edition(gui);
  init_b_rt(gui);
  init_b_options(gui);
  init_b_quit(gui);
  init_b_cred(gui);
}

void	manage_callback(t_gui *gui)
{
  g_signal_connect(G_OBJECT(gui->main.sys.window), "delete-event",
		   G_CALLBACK(quit), gui);
  gtk_signal_connect (GTK_OBJECT (gui->main.buttons.edition), "clicked",
                      GTK_SIGNAL_FUNC (edition_click), NULL);
  gtk_signal_connect (GTK_OBJECT (gui->main.buttons.quit), "clicked",
                      G_CALLBACK(quit), NULL);
  gtk_signal_connect (GTK_OBJECT (gui->main.buttons.rt), "clicked",
                      GTK_SIGNAL_FUNC (rt_click), gui);
  gtk_signal_connect (GTK_OBJECT (gui->main.buttons.options), "clicked",
                      GTK_SIGNAL_FUNC (options_click), gui);
  gtk_signal_connect (GTK_OBJECT (gui->main.buttons.cred), "clicked",
                      GTK_SIGNAL_FUNC (credits_click), NULL);
}

void	init_arg(t_gui *gui)
{
  gui->args.port = malloc(16 * sizeof(char));
  memset(gui->args.port, 0, 16);
  strcpy(gui->args.port, "33669");
  gui->args.nb_max = malloc(8 * sizeof(char));
  memset(gui->args.nb_max, 0, 8);
  strcpy(gui->args.nb_max, "1");
  gui->args.x = malloc(16 * sizeof(char));
  memset(gui->args.x, 0, 16);
  strcpy(gui->args.x, "800");
  gui->args.y = malloc(16 * sizeof(char));
  memset(gui->args.y, 0, 16);
  strcpy(gui->args.y, "600");
  gui->args.conf = malloc(2048 * sizeof(char));
  memset(gui->args.conf, 0, 2048);
  strcpy(gui->args.conf, "naz");
  printf("-- RESUM --\n");
  printf("Port : %s\n", gui->args.port);
  printf("Nb_Max : %s\n", gui->args.nb_max);
  printf("X : %s\n", gui->args.x);
  printf("Y : %s\n", gui->args.y);
  printf("conf : %s\n", gui->args.conf);
}

int main (int argc, char *argv[])
{
  t_gui		*gui;

  gui = malloc(sizeof(*gui));
  gtk_init(&argc, &argv);
  init_arg(gui);
  init_sys(gui);
  init_all_buttons(gui);
  manage_callback(gui);
  gtk_widget_show_all(gui->main.sys.window);
  gtk_main();
  printf("finish\n");
  return 0;
}
