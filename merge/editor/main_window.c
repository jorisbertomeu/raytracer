/*
** main_window.c for  in /home/ades_n/Workspace/gui
** 
** Made by nicolas ades
** Login   <ades_n@epitech.net>
** 
** Started on  Fri Jun  6 16:33:18 2014 nicolas ades
** Last update Sun Jun  8 07:31:27 2014 Joris Bertomeu
*/

#define _BSD_SOURCE
#include "editor.h"

void		catch_event(GtkWidget *pWidget, gpointer pData)
{
  (void)pWidget;
  (void)pData;
  gtk_main_quit();
}

void		init_window(t_editor *editor)
{
  editor->pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(editor->pWindow), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(editor->pWindow), WIN_X, WIN_Y);
  gtk_window_set_resizable(GTK_WINDOW(editor->pWindow), FALSE);
  gtk_window_set_title(GTK_WINDOW(editor->pWindow), "MABM_RT: Editor");
  editor->frame = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(editor->pWindow), editor->frame);
}

void		create_area(t_editor *editor)
{
  editor->area = gtk_text_view_new();
  gtk_widget_set_size_request(editor->area, 500, 680);
  gtk_fixed_put(GTK_FIXED(editor->frame), editor->area, 30, 40);
  editor->buffer = gtk_text_buffer_new(NULL);
}

void		create_box1(t_editor *editor)
{
  editor->pbox = gtk_frame_new("File config");
  gtk_widget_set_size_request(editor->pbox, 1080, 700);
  gtk_fixed_put(GTK_FIXED(editor->frame), editor->pbox, 15, 15);
}

void		create_box2(t_editor *editor)
{
  editor->pbox2 = gtk_frame_new("RGB Color");
  gtk_widget_set_size_request(editor->pbox2, 330, 50);
  gtk_fixed_put(GTK_FIXED(editor->frame), editor->pbox2, 550, 320);
}

void	set_all_sen_true(t_editor *editor)
{
  gtk_widget_set_sensitive(editor->pR, TRUE);
  gtk_widget_set_sensitive(editor->pG, TRUE);
  gtk_widget_set_sensitive(editor->pB, TRUE);
  gtk_widget_set_sensitive(editor->pRx, TRUE);
  gtk_widget_set_sensitive(editor->pRy, TRUE);
  gtk_widget_set_sensitive(editor->pRz, TRUE);
  gtk_widget_set_sensitive(editor->pColor, TRUE);
  gtk_widget_set_sensitive(editor->pBright, TRUE);
  gtk_widget_set_sensitive(editor->pReflex, TRUE);
  gtk_widget_set_sensitive(editor->pOpa, TRUE);
  gtk_widget_set_sensitive(editor->pColor, TRUE);
}

void	set_sen_eye(t_editor *editor)
{
  set_all_sen_true(editor);
  gtk_widget_set_sensitive(editor->pR, FALSE);
  gtk_widget_set_sensitive(editor->pG, FALSE);
  gtk_widget_set_sensitive(editor->pB, FALSE);
  gtk_widget_set_sensitive(editor->pColor, FALSE);
  gtk_widget_set_sensitive(editor->pBright, FALSE);
  gtk_widget_set_sensitive(editor->pReflex, FALSE);
  gtk_widget_set_sensitive(editor->pOpa, FALSE);
  gtk_widget_set_sensitive(editor->pColor, FALSE);
}

void	grising_cases(GtkWidget *w, t_editor *editor)
{
  (void)w;
  if (strcmp(gtk_entry_get_text(GTK_ENTRY(GTK_COMBO(editor
						    ->combo)->entry)), "SPOT") == 0)
    {
      set_all_sen_true(editor);
      gtk_widget_set_sensitive(editor->pRx, FALSE);
      gtk_widget_set_sensitive(editor->pRy, FALSE);
      gtk_widget_set_sensitive(editor->pRz, FALSE);
      gtk_widget_set_sensitive(editor->pColor, FALSE);
      gtk_widget_set_sensitive(editor->pBright, FALSE);
      gtk_widget_set_sensitive(editor->pReflex, FALSE);
      gtk_widget_set_sensitive(editor->pOpa, FALSE);
      gtk_widget_set_sensitive(editor->pColor, FALSE);
    }
  else if (strcmp(gtk_entry_get_text(GTK_ENTRY(GTK_COMBO(editor
						    ->combo)->entry)), "EYE") == 0)
    set_sen_eye(editor);
  else
    set_all_sen_true(editor);
}

char	*get_final(t_editor *editor)
{
  char		*final;
  int		star;
  GtkTextBuffer	*saved;
  GtkTextIter	start;
  GtkTextIter	end;
  char       	*text;

  saved = gtk_text_view_get_buffer(GTK_TEXT_VIEW(editor->area));
  gtk_text_buffer_get_start_iter(saved, &start);
  gtk_text_buffer_get_end_iter(saved, &end);
  text = (char *) gtk_text_buffer_get_text(saved, &start, &end, FALSE);
  star = strlen(text);
  final = malloc((star + 1024 + 2) * sizeof(char));
  memset(final, 0, (star + 1024 + 2));
  strcpy(final, text);
  editor->star = star;
  return (final);
}

char	*cts(const gchar *str)
{
  char	*tmp;

  tmp = malloc((16 + 1) * sizeof(char));
  memset(tmp, 0, 16);
  strcpy(tmp, "0");
  if (str[0] != 0)
    return ((char *)str);
  return (tmp);
}

char		*add_spot(t_editor *editor)
{
  char		*final;

  final = get_final(editor);
  sprintf(&final[editor->star], "<SPOT>\n\t<POS>\n\t\t<x>%s</x>\n\t\t<y>\
%s</y>\n\t\t<z>%s</z>\n\t</POS>\n\t<COLOR>\n\t\t<r>%s</g>\
\n\t\t<g>%s</G>\n\t\t<b>%s</b>\n\t</COLOR>\n</SPOT>\n",
	  cts(gtk_entry_get_text(GTK_ENTRY(editor->pTx))),
	  cts(gtk_entry_get_text(GTK_ENTRY(editor->pTy))),
	  cts(gtk_entry_get_text(GTK_ENTRY(editor->pTz))),
	  cts(gtk_entry_get_text(GTK_ENTRY(editor->pR))),
	  cts(gtk_entry_get_text(GTK_ENTRY(editor->pG))),
	  cts(gtk_entry_get_text(GTK_ENTRY(editor->pB))));
  return (final);
}

char		*add_eye(t_editor *editor)
{
  char		*final;

  final = get_final(editor);
  sprintf(&final[editor->star], "<EYE>\n\t<POS>\n\t\t<x>%s</x>\n\t\t<y>\
%s</y>\n\t\t<z>%s</z>\n\t</POS>\n\t<ROT>\n\t\t<x>%s</x>\
\n\t\t<y>%s</y>\n\t\t<z>%s</z>\n\t</ROT>\n</EYE>\n",
	  cts(gtk_entry_get_text(GTK_ENTRY(editor->pTx))),
	  cts(gtk_entry_get_text(GTK_ENTRY(editor->pTy))),
	  cts(gtk_entry_get_text(GTK_ENTRY(editor->pTz))),
	  cts(gtk_entry_get_text(GTK_ENTRY(editor->pRx))),
	  cts(gtk_entry_get_text(GTK_ENTRY(editor->pRy))),
	  cts(gtk_entry_get_text(GTK_ENTRY(editor->pRz))));
  return (final);
}

char	*sort_number(const gchar *str)
{
  char	*final;

  final = malloc(16 * sizeof(char));
  memset(final, 0, 16);
  strcpy(final, "0");
  if (strcmp(str, "Wave") == 0)
    strcpy(final, "1");
  if (strcmp(str, "Checkerboard") == 0)
    strcpy(final, "2");
  return (final);
}

char	*add_object(t_editor *editor)
{
  char	*final;

  final = get_final(editor);
  sprintf(&final[editor->star], "<%s>\n\t<POS>\n\t\t<x>%s</x>\n\t\t<y>\
%s</y>\n\t\t<z>%s</z>\n\t</POS>\n\t<ROT>\n\t\t<x>%s</x>\
\n\t\t<y>%s</y>\n\t\t<z>%s</z>\n\t</ROT>\n\t<COLOR>\n\t\t<r>%s</g>\
\n\t\t<g>%s</G>\n\t\t<b>%s</b>\n\t</COLOR>\n\t<EFFECTS>\n\t\t<BRILL>%s</BRILL>\
\n\t\t<TRANSP>%s</TRANSP>\n\t\t<REFLEXION>%s</REFLEXION\
>\n\t\t<EFFECT>%s</EFFECT>\n\t</EFFECTS>\n\
</%s>\n", cts(gtk_entry_get_text(GTK_ENTRY(GTK_COMBO(editor->combo)->entry))),
	  cts(gtk_entry_get_text(GTK_ENTRY(editor->pTx))),
	  cts(gtk_entry_get_text(GTK_ENTRY(editor->pTy))),
	  cts(gtk_entry_get_text(GTK_ENTRY(editor->pTz))),
	  cts(gtk_entry_get_text(GTK_ENTRY(editor->pRx))),
	  cts(gtk_entry_get_text(GTK_ENTRY(editor->pRy))),
	  cts(gtk_entry_get_text(GTK_ENTRY(editor->pRz))),
	  cts(gtk_entry_get_text(GTK_ENTRY(editor->pR))),
	  cts(gtk_entry_get_text(GTK_ENTRY(editor->pG))),
	  cts(gtk_entry_get_text(GTK_ENTRY(editor->pB))),
	  cts(gtk_entry_get_text(GTK_ENTRY(editor->pBright))),
	  cts(gtk_entry_get_text(GTK_ENTRY(editor->pOpa))),
	  cts(gtk_entry_get_text(GTK_ENTRY(editor->pReflex))),
	  sort_number(gtk_entry_get_text(GTK_ENTRY(GTK_COMBO(editor->pColor)->entry))),
	  cts(gtk_entry_get_text(GTK_ENTRY(GTK_COMBO(editor->combo)->entry))));
  return (final);
}

void	add_obj(GtkWidget *w, t_editor *editor)
{
  char	*final;

  (void)w;
  if (strcmp(gtk_entry_get_text(GTK_ENTRY(GTK_COMBO(editor
						    ->combo)->entry)), "SPOT") == 0)
    final = add_spot(editor);
  else if (strcmp(gtk_entry_get_text(GTK_ENTRY(GTK_COMBO(editor
							 ->combo)->entry)), "EYE") == 0)
    final = add_eye(editor);
  else
    final = add_object(editor);
  gtk_text_buffer_set_text(editor->buffer, final, (gint) strlen(final));
  gtk_text_view_set_buffer((GTK_TEXT_VIEW(editor->area)),
			   GTK_TEXT_BUFFER(editor->buffer));
}

void		catch_sig(t_editor *editor)
{
  g_signal_connect(G_OBJECT(editor->pWindow),
		   "destroy", G_CALLBACK(catch_event), NULL);
  g_signal_connect(G_OBJECT(editor->pQuitBtn),
		   "clicked", G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(G_OBJECT(editor->pHelpBtn),
		   "clicked", G_CALLBACK(create_help_win), editor);
  g_signal_connect(G_OBJECT(editor->pSaveBtn),
		   "clicked", G_CALLBACK(create_save_win), editor);
  g_signal_connect(G_OBJECT(editor->pAddBtn),
		   "clicked", G_CALLBACK(add_obj), editor);
  g_signal_connect(G_OBJECT(GTK_COMBO(editor->combo)->entry),
		   "changed", G_CALLBACK(grising_cases), editor);
  /* g_signal_connect(G_OBJECT(editor->pAddBtn),
     "clicked", G_CALLBACK(write_in_file), editor); */
}
