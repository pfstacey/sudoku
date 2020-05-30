/*
 * Author: Matt Keating
 * Teammates: Piper Stacey, Sarah Korb, Marlee Montella
 */
 
#include <gtk/gtk.h>

GtkWidget *r0;
GtkWidget *r1;
GtkWidget *r2;
GtkWidget *r3;
GtkWidget *r4;
GtkWidget *r5;
GtkWidget *r6;
GtkWidget *r7;
GtkWidget *r8;

const int COL_SIZE = 3;

static void solve (GtkWidget *widget,  gpointer   data) {
    	g_print ("Hello World\n");
}

static void activate (GtkApplication *app, gpointer user_data) {
	GtkWidget *window;
	GtkWidget *solvebutton;

	GtkWidget *grid;

	window = gtk_application_window_new (app);
	gtk_window_set_title (GTK_WINDOW (window), "Window");
	gtk_window_set_default_size (GTK_WINDOW (window), 600, 600);

	grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(window), grid);
	gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);

	r0 = gtk_entry_new();
	gtk_grid_attach(GTK_GRID(grid), r0, 0, 0, COL_SIZE, 1);
	gtk_entry_set_text(GTK_ENTRY(r0), "hello world");

	r1 = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(grid), r1, 0, 1, COL_SIZE, 1);

	r2 = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(grid), r2, 0, 2, COL_SIZE, 1);

        r3 = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(grid), r3, 0, 3, COL_SIZE, 1);

	r4 = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(grid), r4, 0, 4, COL_SIZE, 1);

        r5 = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(grid), r5, 0, 5, COL_SIZE, 1);

	r6 = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(grid), r6, 0, 6, COL_SIZE, 1);

        r7 = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(grid), r7, 0, 7, COL_SIZE, 1);

	r8 = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(grid), r8, 0, 8, COL_SIZE, 1);

	solvebutton = gtk_button_new_with_label ("Solve");
	g_signal_connect (solvebutton, "clicked", G_CALLBACK (solve), NULL);
	gtk_grid_attach(GTK_GRID(grid), solvebutton, 1, 9, 1, 1);

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

