/*
** push_in_file.c for  in /home/ades_n/Workspace/raytracer/merge/editor
** 
** Made by nicolas ades
** Login   <ades_n@epitech.net>
** 
** Started on  Sat Jun  7 18:41:24 2014 nicolas ades
** Last update Sat Jun  7 21:43:41 2014 nicolas ades
*/

#include "editor.h"

void		get_from_text_view(t_editor *editor)
{
  GtkTextIter start, end;
  GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(editor->area));
  gchar *text;
  
  gtk_text_buffer_get_bounds(buffer, &start, &end);
  text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
  printf("%s\n", text);
}

/* void		write_in_text_view(int fd, t_editor *editor) */
/* { */
  
/* } */
