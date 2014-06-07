/*
** editor.h for  in /home/ades_n/Workspace/gui
** 
** Made by nicolas ades
** Login   <ades_n@epitech.net>
** 
** Started on  Wed Jun  4 13:22:29 2014 nicolas ades
** Last update Sat Jun  7 15:38:12 2014 nicolas ades
*/

#ifndef EDITOR_H_
# define EDITOR_H_

# define WIN_X 1200
# define WIN_Y 720
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <gtk/gtk.h>

typedef struct	s_editor
{
  GtkWidget	*pWindow;
  GtkWidget	*pWinSave;
  GtkWidget	*pWinHelp;
  GtkWidget	*pselection;
  GtkWidget	*Helpframe;
  GtkWidget	*Saveframe;
  GtkWidget	*pLabel;
  GtkWidget	*pCancelBtn;
  GtkWidget	*pSFBtn;
  GtkWidget	*pQuitBtn;
  GtkWidget	*pSaveBtn;
  GtkWidget	*pOpenBtn;
  GtkWidget	*pHelpBtn;
  GtkWidget	*pNewBtn;
  GtkWidget	*pAddBtn;
  GtkWidget	*frame;
  GtkWidget	*pbox;
  GtkWidget	*area;
  GtkWidget	*pname;
  GtkWidget	*pTx;
  GtkWidget	*pTy;
  GtkWidget	*pTz;
  GtkWidget	*pSize;
  GtkWidget	*pColor;
  GtkWidget	*pRx;
  GtkWidget	*pRy;
  GtkWidget	*pRz;
  GtkWidget	*pBright;
  GtkWidget	*pReflex;
  GtkWidget	*pOpa;
  GList		*list;
  GtkWidget	*combo;
}		t_editor;

GList		*create_list();
void		create_combo(t_editor *);
void		create_help_win(GtkWidget *, t_editor *);
void		quit_btn(t_editor *);
void		new_btn(t_editor *);
void		save_btn(t_editor *);
void		create_file(GtkWidget *, t_editor *);
void		open_btn(t_editor *);
void		help_btn(t_editor *);
void		add_btn(t_editor *);
void		inser_color(t_editor *);
void		inser_Brightness(t_editor *);
void		inser_tx(t_editor *);
void		inser_ty(t_editor *);
void		inser_tz(t_editor *);
void		inser_rx(t_editor *);
void		inser_ry(t_editor *);
void		inser_rz(t_editor *);
void		inser_name(t_editor *);
void		inser_opacity(t_editor *);
void		inser_reflexion(t_editor *);
void		cancel_save_btn(t_editor *);
void		save2_btn(t_editor *);
void		create_save_win(GtkWidget *, t_editor *);
void		editor(int, char **);
void		catch_sig(t_editor *);
void		init_window(t_editor *);
void		catch_event(GtkWidget *, gpointer );
void		create_area(t_editor *);
void		my_gtk_main_quit(GtkWidget *, t_editor *);
void		my_widget_destroy(GtkWidget *, t_editor *);
void		create_box1(t_editor *);

#endif /* EDITOR_H_ */
