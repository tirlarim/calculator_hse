//gcc -Wno-format -o gui1  gui.c calculations.c polish.c arrays.c actions.c is_smh_compare.c variables.c operations_functions.c -Wno-deprecated-declarations -Wno-format-security -lm `pkg-config --cflags --libs gtk+-3.0` -rdynamic
//gcc -o gui gui.c arrays.c arrays.h polish.c polish.h is_smh_compare.c is_smh_compare.h actions.c actions.h calculations.c calculations.h variables.c variables.h operations_functions.c operations_functions.h -lm `pkg-config --cflags --libs gtk+-3.0` -rdynamic
#include <gtk/gtk.h>
#include <stdlib.h>
#include "../src/polish.h"

GtkWidget* window;
GtkWidget* textview;
GtkWidget* label;
GtkTextBuffer* textbuffer;
GtkBuilder* builder;

G_MODULE_EXPORT void on_simple_button_clicked(GtkButton* b) {
  const gchar* text = gtk_button_get_label(b);
  gtk_text_buffer_insert_at_cursor(textbuffer, text, -1);
}

G_MODULE_EXPORT void on_button_calculate_clicked(GtkButton* b) {
  //putting text in input
  GtkTextIter begin, end;

  gtk_text_buffer_get_iter_at_offset(GTK_TEXT_BUFFER(textbuffer), &begin, 0);
  gtk_text_buffer_get_iter_at_offset(GTK_TEXT_BUFFER(textbuffer), &end, -1);

  const gchar* textInPtr = gtk_text_buffer_get_text(GTK_TEXT_BUFFER(textbuffer), &begin, &end, FALSE);
  // char* textOutPtr = calloc(1000, sizeof(*textOutPtr));
  // memcpy(textOutPtr, textInPtr, strlen(textInPtr) * sizeof(*textInPtr));

  //Calculate
  char* textOutPtr = Calculations((char*)textInPtr);

  gtk_label_set_text(GTK_LABEL(label), textOutPtr);
  free(textOutPtr);
}

G_MODULE_EXPORT void on_button_clear_clicked(GtkButton* b) {
  gtk_label_set_text(GTK_LABEL(label), "");

  GtkTextIter begin, end;
  gtk_text_buffer_get_iter_at_offset(GTK_TEXT_BUFFER(textbuffer), &begin, 0);
  gtk_text_buffer_get_iter_at_offset(GTK_TEXT_BUFFER(textbuffer), &end, -1);

  gtk_text_buffer_delete(GTK_TEXT_BUFFER(textbuffer), &begin, &end);
}

G_MODULE_EXPORT void on_button_delete_clicked(GtkButton* b) {
  GtkTextIter end;
  GtkTextMark cursor;

  cursor = *gtk_text_buffer_get_insert(GTK_TEXT_BUFFER(textbuffer));
  gtk_text_buffer_get_iter_at_mark(GTK_TEXT_BUFFER(textbuffer), &end, &cursor);

  gtk_text_buffer_backspace(GTK_TEXT_BUFFER(textbuffer), &end, TRUE, TRUE);
}

G_MODULE_EXPORT void on_button_clear_answer_clicked(GtkButton* b) {
  gtk_label_set_text(GTK_LABEL(label), "");
}

G_MODULE_EXPORT void on_button_TAB_clicked(GtkButton* b) {
  GtkTextIter end;
  GtkTextMark cursor;

  cursor = *gtk_text_buffer_get_insert(GTK_TEXT_BUFFER(textbuffer));
  gtk_text_buffer_get_iter_at_mark(GTK_TEXT_BUFFER(textbuffer), &end, &cursor);

  const gchar* text = "\n";

  gtk_text_buffer_insert(textbuffer, &end, text, (gint)-1);
}

G_MODULE_EXPORT void on_button_ASSIGN_A_VALUE_clicked(GtkButton* b) {
  GtkTextIter end;
  GtkTextMark cursor;

  cursor = *gtk_text_buffer_get_insert(GTK_TEXT_BUFFER(textbuffer));
  gtk_text_buffer_get_iter_at_mark(GTK_TEXT_BUFFER(textbuffer), &end, &cursor);

  const gchar* text = " = ";

  gtk_text_buffer_insert(textbuffer, &end, text, (gint)-1);
}

G_MODULE_EXPORT void on_exit(GtkWidget* w) {
  gtk_main_quit();
}

int main(int argc, char* argv[]) {
  gtk_init(&argc, &argv);
  GtkBuilder* builder = gtk_builder_new();
  GError* err = NULL;
  const char pathGui[] = "./view/gui.glade";
  const char pathIcon[] = "./view/icon.png";

  gtk_builder_add_from_file(builder, pathGui, &err);
  gtk_builder_connect_signals(builder, NULL);
  window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
  gtk_window_set_title(GTK_WINDOW(window), "Calculator");
  gtk_window_set_icon_from_file(GTK_WINDOW(window), pathIcon, NULL);
  textview = GTK_WIDGET(gtk_builder_get_object(builder, "textview"));
  label = GTK_WIDGET(gtk_builder_get_object(builder, "label"));
  textbuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview));
  gtk_widget_show(GTK_WIDGET(window));
  gtk_main();
  exit(0);
}
