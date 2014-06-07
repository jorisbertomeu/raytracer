/*
** editor.c for  in /home/ades_n/Workspace/gui
** 
** Made by nicolas ades
** Login   <ades_n@epitech.net>
** 
** Started on  Wed Jun  4 13:21:49 2014 nicolas ades
** Last update Sat Jun  7 20:23:07 2014 nicolas ades
*/

#include "editor.h"

GList		*create_list()
{
  GList		*list;

  list = NULL;
  list = g_list_append(list, g_strdup_printf("Circle"));
  list = g_list_append(list, g_strdup_printf("Plan"));
  list = g_list_append(list, g_strdup_printf("Effects"));
  list = g_list_append(list, g_strdup_printf("Cylinder"));
  list = g_list_append(list, g_strdup_printf("Cone"));
  list = g_list_append(list, g_strdup_printf("Eye"));
  list = g_list_append(list, g_strdup_printf("Spot"));
  return (list);
}

void		create_combo(t_editor *editor)
{
  editor->combo = gtk_combo_new();
  gtk_entry_set_editable(GTK_ENTRY(GTK_COMBO(editor->combo)->entry), FALSE);
  gtk_combo_set_popdown_strings(GTK_COMBO(editor->combo), editor->list);
  gtk_entry_set_text(GTK_ENTRY(GTK_COMBO(editor->combo)->entry), "Circle");
  gtk_fixed_put(GTK_FIXED(editor->frame), editor->combo, 550, 30);
}

void		editor(int ac, char **av)
{
  t_editor	*editor;

  editor = malloc(sizeof(*editor));
  gtk_init(&ac, &av);
  init_window(editor);
  editor->list = create_list();
  quit_btn(editor);
  save_btn(editor);
  open_btn(editor);
  help_btn(editor);
  new_btn(editor);
  add_btn(editor);
  create_box1(editor);
  create_box2(editor);
  inser_tx(editor);
  inser_ty(editor);
  inser_tz(editor);
  inser_rx(editor);
  inser_ry(editor);
  inser_rz(editor);
  inser_color(editor);
  inser_Brightness(editor);
  inser_opacity(editor);
  inser_reflexion(editor);
  inser_r(editor);
  inser_g(editor);
  inser_b(editor);
  create_area(editor);
  create_combo(editor);
  catch_sig(editor);
  gtk_widget_show_all(editor->pWindow);
  gtk_main();
}
