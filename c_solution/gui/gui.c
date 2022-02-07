//gcc -Wno-format -o gui gui.c -Wno-deprecated-declarations -Wno-format-security -lm `pkg-config --cflags --libs gtk+-3.0` -rdynamic
#include <gtk/gtk.h>
#include <stdio.h>

GtkWidget *window;
GtkWidget *textview;
GtkWidget *label;
GtkTextBuffer *textbuffer;

GtkBuilder *builder;

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file ("gui.glade");
    gtk_builder_connect_signals(builder, NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    textview = GTK_WIDGET(gtk_builder_get_object(builder, "textview"));
    label = GTK_WIDGET(gtk_builder_get_object(builder, "label"));
    textbuffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(textview));
    
    gtk_widget_show(window);

    gtk_main();

    return EXIT_SUCCESS;
}

void on_simple_button_clicked(GtkButton *b) {
    // GtkTextIter end;
    const gchar *text;

	// gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER(textbuffer), &end, (gint) -1);

    text = gtk_button_get_label(b);

    gtk_text_buffer_insert_at_cursor(textbuffer, text, (gint) -1);
}

void on_button_calculate_clicked(GtkButton *b){
    //putting text in input
    GtkTextIter begin, end;
    const gchar *text_input;

    gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER(textbuffer), &begin, (gint) 0);
	gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER(textbuffer), &end, (gint) -1);

    text_input = gtk_text_buffer_get_text(GTK_TEXT_BUFFER(textbuffer), &begin, &end, FALSE);
    char tmp_input[100];
    
    sprintf(tmp_input, "%s", text_input);

    FILE *input;
    input = fopen("input.txt", "w");
    fputs(tmp_input, input);
    fclose(input);

    //getting and showing answer
    const gchar *text_output;
    char tmp_output[100];

    FILE *output;
    output = fopen("output.txt", "r");
    text_output = fgets(tmp_output, 100, output);
    fclose(output);

    text_output = tmp_output;

    gtk_label_set_text(GTK_LABEL(label), text_output);
}

void on_button_clear_clicked(GtkButton *b) {
    gtk_label_set_text(GTK_LABEL(label), (const gchar*) "");

    GtkTextIter begin, end;
    gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER(textbuffer), &begin, (gint) 0);
	gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER(textbuffer), &end, (gint) -1);
    
    gtk_text_buffer_delete(GTK_TEXT_BUFFER(textbuffer), &begin, &end);
}

void on_button_delete_clicked(GtkButton *b) {
    GtkTextIter end;
    GtkTextMark cursor;

    cursor = *gtk_text_buffer_get_insert(GTK_TEXT_BUFFER(textbuffer));
    gtk_text_buffer_get_iter_at_mark(GTK_TEXT_BUFFER(textbuffer), &end, &cursor);

	// gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER(textbuffer), &end, (gint) -1);

    gtk_text_buffer_backspace(GTK_TEXT_BUFFER(textbuffer), &end, TRUE, TRUE);
}

void on_button_clear_answer_clicked(GtkButton *b) {
    gtk_label_set_text(GTK_LABEL(label), (const gchar*) "");
}

void on_button_TAB_clicked(GtkButton *b) {
    GtkTextIter end;
    const gchar *text;

	gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER(textbuffer), &end, (gint) -1);

    text = "\n";

    gtk_text_buffer_insert(textbuffer, &end, text, (gint) -1);
}