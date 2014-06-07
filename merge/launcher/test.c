#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

GdkPixbuf *load_pixbuf_from_file (const char *filename)
{
    GError *error = NULL;
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file (filename, &error);

    if (pixbuf == NULL)
    {
        g_print ("Error loading file: %d : %s\n", error->code, error->message);
        g_error_free (error);
        exit (1);
    }
    return pixbuf;
}

int main (int argc, char **argv)
{
    GtkWidget *window = NULL;
    GdkPixbuf *image = NULL;
    GtkWidget *widget = NULL;
    GdkPixmap *background = NULL;
    GtkStyle *style = NULL;

    gtk_init (&argc, &argv);
    image = load_pixbuf_from_file ("img.jpg");
    gdk_pixbuf_render_pixmap_and_mask (image, &background, NULL, 0);
    style = gtk_style_new ();
    style->bg_pixmap[0] = background;
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW(window), "Raytracer Launcher");
    gtk_window_set_default_size (GTK_WINDOW (window), 800, 600);
    gtk_widget_set_style (GTK_WIDGET(window), GTK_STYLE (style));
    gtk_window_set_transient_for (GTK_WINDOW (window), NULL);

    GtkWidget *hbox = NULL;
    hbox = gtk_hbox_new (0, FALSE);
    gtk_container_add (GTK_CONTAINER(window), hbox);

    GtkWidget *button = NULL;
    button = gtk_button_new_with_label ("Sonic");
    gtk_box_pack_start (GTK_BOX (hbox), button, FALSE, FALSE, 0);

    gtk_widget_show_all (window);
    gtk_main ();
    return 0;
}
