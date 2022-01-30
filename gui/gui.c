#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

static GtkWidget *entry;

void do_print(GtkWidget *calculate, gpointer data) {

    char *buffer = (char *)gtk_entry_get_text(GTK_ENTRY(entry));
    FILE *input;
    input = fopen("input.txt", "w");
    fputs(buffer, input);
    fclose(input);
}

// gcc 007_gtk.c -o 007_gtk `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`
int main(int argc, char **argv) {
    GtkWidget *window, *grid, *calculate;
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_title(GTK_WINDOW(window), "SHIT");
    gtk_window_set_default_size(GTK_WINDOW (window), 400, 500);
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 0, 0, 1, 1);

    calculate = gtk_button_new_with_label("=");
    g_signal_connect(calculate, "clicked", G_CALLBACK(do_print), NULL);
    gtk_grid_attach(GTK_GRID(grid), calculate, 2, 0, 1, 1);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}