//gcc -Wno-format -o gui1  gui.c calculations.c polish.c arrays.c actions.c is_smh_compare.c variables.c operations_functions.c -Wno-deprecated-declarations -Wno-format-security -lm `pkg-config --cflags --libs gtk+-3.0` -rdynamic
//gcc -o gui gui.c arrays.c arrays.h polish.c polish.h is_smh_compare.c is_smh_compare.h actions.c actions.h calculations.c calculations.h variables.c variables.h operations_functions.c operations_functions.h -lm `pkg-config --cflags --libs gtk+-3.0` -rdynamic
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "../utils/foldersWorker.h"
#include "../polish.h"

GtkWidget *window;
GtkWidget *textview;
GtkWidget *label;
GtkTextBuffer *textbuffer;

GtkBuilder *builder;

G_MODULE_EXPORT void on_simple_button_clicked(GtkButton *b) {
    const gchar *text;

    text = gtk_button_get_label(b);

    gtk_text_buffer_insert_at_cursor(textbuffer, text, (gint) -1);
}

G_MODULE_EXPORT void on_button_calculate_clicked(GtkButton *b){
    //putting text in input
    GtkTextIter begin, end;
    const gchar *text_input;

    gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER(textbuffer), &begin, (gint) 0);
    gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER(textbuffer), &end, (gint) -1);

    text_input = gtk_text_buffer_get_text(GTK_TEXT_BUFFER(textbuffer), &begin, &end, FALSE);
    char tmp_input[1000];

    sprintf(tmp_input, "%s\n", text_input);

    char *HomePath = getenv("USERPROFILE");
    char pathInput[] = "\\AppData\\Local\\HSE-Calculator\\storage\\input.txt";
    char pathOutput[] = "\\AppData\\Local\\HSE-Calculator\\storage\\output.txt";

    char filePathInput[200] = {0};
    strncat(filePathInput, HomePath, 120);
    strncat(filePathInput, pathInput, 120);
    FILE *input;
    input = fopen(filePathInput, "w");
    fputs(tmp_input, input);
    fclose(input);

    //Calculate
    Calculations();

    //getting and showing answer
    const gchar *text_output;
    char tmp_output[1000];

    char filePathOutput[200] = {0};
    strncat(filePathOutput, HomePath, 120);
    strncat(filePathOutput, pathOutput, 120);
    FILE *output;
    output = fopen(filePathOutput, "r");
    text_output = fgets(tmp_output, 1000, output);
    fclose(output);

    text_output = tmp_output;

    gtk_label_set_text(GTK_LABEL(label), text_output);
}

G_MODULE_EXPORT void on_button_clear_clicked(GtkButton *b) {
    gtk_label_set_text(GTK_LABEL(label), (const gchar*) "");

    GtkTextIter begin, end;
    gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER(textbuffer), &begin, (gint) 0);
    gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER(textbuffer), &end, (gint) -1);

    gtk_text_buffer_delete(GTK_TEXT_BUFFER(textbuffer), &begin, &end);
}

G_MODULE_EXPORT void on_button_delete_clicked(GtkButton *b) {
    GtkTextIter end;
    GtkTextMark cursor;

    cursor = *gtk_text_buffer_get_insert(GTK_TEXT_BUFFER(textbuffer));
    gtk_text_buffer_get_iter_at_mark(GTK_TEXT_BUFFER(textbuffer), &end, &cursor);

    gtk_text_buffer_backspace(GTK_TEXT_BUFFER(textbuffer), &end, TRUE, TRUE);
}

G_MODULE_EXPORT void on_button_clear_answer_clicked(GtkButton *b) {
    gtk_label_set_text(GTK_LABEL(label), (const gchar*) "");
}

G_MODULE_EXPORT void on_button_TAB_clicked(GtkButton *b) {
    GtkTextIter end;
    GtkTextMark cursor;

    cursor = *gtk_text_buffer_get_insert(GTK_TEXT_BUFFER(textbuffer));
    gtk_text_buffer_get_iter_at_mark(GTK_TEXT_BUFFER(textbuffer), &end, &cursor);

    const gchar *text;
    text = "\n";

    gtk_text_buffer_insert(textbuffer, &end, text, (gint) -1);
}

G_MODULE_EXPORT void on_button_ASSIGN_A_VALUE_clicked(GtkButton *b) {
  GtkTextIter end;
  GtkTextMark cursor;

  cursor = *gtk_text_buffer_get_insert(GTK_TEXT_BUFFER(textbuffer));
  gtk_text_buffer_get_iter_at_mark(GTK_TEXT_BUFFER(textbuffer), &end, &cursor);

  const gchar *text;
  text = " = ";

  gtk_text_buffer_insert(textbuffer, &end, text, (gint) -1);
}

G_MODULE_EXPORT void on_exit(GtkWidget * w) {
    gtk_main_quit();
}

int main(int argc, char *argv[]) {
    generateStorage();
    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    GError * err = NULL;

    char *HomePath = getenv("USERPROFILE");
    char pathGui[] = "\\AppData\\Local\\HSE-Calculator\\storage\\gui.glade";
    char filePathGui[200] = {0};
    strncat(filePathGui, HomePath, 120);
    strncat(filePathGui, pathGui, 120);
    char pathIcon[] = "\\AppData\\Local\\HSE-Calculator\\storage\\icon.png";
    char filePathIcon[200] = {0};
    strncat(filePathIcon, HomePath, 120);
    strncat(filePathIcon, pathIcon, 120);

    gtk_builder_add_from_file(builder,filePathGui, &err);
    gtk_builder_connect_signals(builder, NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    gtk_window_set_title(window, "Calculator");
    gtk_window_set_icon_from_file (window, filePathIcon, NULL);

  textview = GTK_WIDGET(gtk_builder_get_object(builder, "textview"));
    label = GTK_WIDGET(gtk_builder_get_object(builder, "label"));
    textbuffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(textview));

    gtk_widget_show(window);
    gtk_main();

    exit(0);
}
