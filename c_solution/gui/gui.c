#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

GtkWidget *entry;
GtkWidget *result;
GtkTextBuffer *text_buffer;
GtkTextIter start;
GtkTextIter end;

void do_print(GtkWidget *calculate, gpointer data) {

    gtk_text_buffer_get_iter_at_offset(GTK_TEXT_BUFFER(text_buffer), &start, (gint) 0);
    gtk_text_buffer_get_iter_at_offset(GTK_TEXT_BUFFER(text_buffer), &end, (gint) -1);

    gchar *buffer1;
    buffer1 = gtk_text_buffer_get_text(GTK_TEXT_BUFFER(text_buffer), &start, &end, TRUE);
    char buffer2[100];
    FILE *input;
    FILE *output;
    input = fopen("input.txt", "w");
    output = fopen("output.txt", "r");
    fputs(buffer1, input);
    fgets(buffer2, 100, output);
    gtk_label_set_text(GTK_LABEL(result), buffer2);
    fclose(input);
    fclose(output);
}

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

    entry = gtk_text_view_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 0, 0, 1, 1);

    text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(entry));
    gtk_text_buffer_set_text(text_buffer, "", (gint) -1);

    calculate = gtk_button_new_with_label("=");
    g_signal_connect(calculate, "clicked", G_CALLBACK(do_print), NULL);
    gtk_grid_attach(GTK_GRID(grid), calculate, 2, 0, 1, 1);

    result = gtk_label_new("result:");
    gtk_grid_attach(GTK_GRID(grid), result, 3, 0, 1, 1);
    
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}