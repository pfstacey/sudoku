/*
 * Author: Matt Keating
 * Teammates: Piper Stacey, Sarah Korb, Marlee Montella
 */
 
#include <gtk/gtk.h>

static void solve (GtkWidget *widget,  gpointer   data) {
    	g_print ("Hello World\n");
}

static void activate (GtkApplication *app, gpointer user_data) {
	GtkWidget *window;
	GtkWidget *button;
	GtkWidget *button_box;

	//test code for text
	GtkWidget *view;
	GtkTextBuffer *buffer;
	PangoFontDescription *font_desc;
	GdkRGBA rgba;
	GtkCssProvider *provider;
	GtkStyleContext *context;

	window = gtk_application_window_new (app);
	gtk_window_set_title (GTK_WINDOW (window), "Window");
	gtk_window_set_default_size (GTK_WINDOW (window), 600, 600);

	button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
	gtk_container_add (GTK_CONTAINER (window), button_box);

	button = gtk_button_new_with_label ("Solve");
	g_signal_connect (button, "clicked", G_CALLBACK (solve), NULL);
	gtk_container_add (GTK_CONTAINER (button_box), button);

	//test code for text
	view = gtk_text_view_new ();
	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
	gtk_text_buffer_set_text (buffer, "Hello, this is some text", -1);

	context = gtk_widget_get_style_context (view);

	/* Change left margin throughout the widget */
	gtk_text_view_set_left_margin (GTK_TEXT_VIEW (view), 30);

	gtk_widget_show_all (window);
}

int main (int argc, char **argv) {
	GtkApplication *app;
	int status;

	app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
	status = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);

	return status;
}

