/*
** main_ins.c for  in /home/ades_n/Workspace/gui
** 
** Made by nicolas ades
** Login   <ades_n@epitech.net>
** 
** Started on  Fri Jun  6 16:35:09 2014 nicolas ades
** Last update Fri Jun  6 16:35:43 2014 nicolas ades
*/

#include "editor.h"

void		inser_color(t_editor *editor)
{
  editor->pColor = gtk_entry_new();
  gtk_widget_set_size_request(editor->pColor, 80, 25);
  gtk_fixed_put(GTK_FIXED(editor->frame), editor->pColor, 605, 220);
  editor->pLabel = gtk_label_new("Color :");
  gtk_fixed_put(GTK_FIXED(editor->frame), editor->pLabel, 550, 225);
}

void		inser_Brightness(t_editor *editor)
{
  editor->pBright = gtk_entry_new();
  gtk_widget_set_size_request(editor->pBright, 80, 25);
  gtk_fixed_put(GTK_FIXED(editor->frame), editor->pBright, 840, 220);
  editor->pLabel = gtk_label_new("Brightness :");
  gtk_fixed_put(GTK_FIXED(editor->frame), editor->pLabel, 750, 225);
}

void		inser_tx(t_editor *editor)
{
  editor->pTx = gtk_entry_new();
  gtk_widget_set_size_request(editor->pTx, 80, 25);
  gtk_fixed_put(GTK_FIXED(editor->frame), editor->pTx, 585, 75);
  editor->pLabel = gtk_label_new("T.x :");
  gtk_fixed_put(GTK_FIXED(editor->frame), editor->pLabel, 550, 80);
}

void		inser_ty(t_editor *editor)
{
  editor->pTy = gtk_entry_new();
  gtk_widget_set_size_request(editor->pTy, 80, 25);
  gtk_fixed_put(GTK_FIXED(editor->frame), editor->pTy, 585, 120);
  editor->pLabel = gtk_label_new("T.y :");
  gtk_fixed_put(GTK_FIXED(editor->frame), editor->pLabel, 550, 125);
}

void		inser_tz(t_editor *editor)
{
  editor->pTz = gtk_entry_new();
  gtk_widget_set_size_request(editor->pTz, 80, 25);
  gtk_fixed_put(GTK_FIXED(editor->frame), editor->pTz, 585, 170);
  editor->pLabel = gtk_label_new("T.z :");
  gtk_fixed_put(GTK_FIXED(editor->frame), editor->pLabel, 550, 175);
}
