/*
 * Author: Matt Keating
 * Teammates: Piper Stacey, Sarah Korb, Marlee Montella
 */
 
#include <gtk/gtk.h>
#include "common/puzzle.h"
#include "common/create.h"
#include "common/solve.h"

GtkWidget *grid;
puzzle_t *puzzle;

bool solved = false;

int * load_puzzle_into_81x1(){
	int *nums = malloc(81 * sizeof(int));

        for(int i = 0; i < 81; i++){
                nums[i] = puzzle_getValue(puzzle, i / 9, i % 9);
        }

        return nums;
}

int * load_puzzle(){
	puzzle = puzzle_new();

	rand_init();
	build_puzzle(puzzle);

	int *nums = malloc(81 * sizeof(int));

	return load_puzzle_into_81x1();
}

int * solve_puzzle(){
	backtrack(puzzle, 0, 0);

	return load_puzzle_into_81x1();
}

static void solve (GtkWidget *widget,  gpointer   data) {
    	
	if(solved == true){
		printf("Already solved\n");
		return;
	}
	
	solved = true;

	int * numbers = solve_puzzle();
	
	for(int i = 0; i < 81; i++){
		GtkWidget *text = gtk_grid_get_child_at(GTK_GRID(grid), i % 9, i / 9);
		GtkTextBuffer *buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (text));
		
		char *num = malloc(2 * sizeof(char));
                sprintf(num, "%d", numbers[i]);
		
		gtk_text_buffer_set_text (buffer, num, -1);

		free(num);
	}

	free(numbers);
	free(puzzle);
}

//TODO: create loader function to load in all of the numbers

static void grid_setup(){
	int * numbers = load_puzzle();

	for(int i = 0; i < 81; i++){
		GtkWidget *text = gtk_text_view_new ();
		GtkTextBuffer *buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (text));

		char *num = malloc(2 * sizeof(char));
		sprintf(num, "%d", numbers[i]);

		gtk_text_buffer_set_text (buffer, num, -1);
	
		gtk_grid_attach(GTK_GRID(grid), text, i % 9, i / 9, 1, 1);
		
		free(num);
	}

	free(numbers);
}

static void activate (GtkApplication *app, gpointer user_data) {
	GtkWidget *window;
	GtkWidget *solvebutton;

	window = gtk_application_window_new (app);
	gtk_window_set_title (GTK_WINDOW (window), "Window");
	gtk_window_set_default_size (GTK_WINDOW (window), 600, 600);

	grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(window), grid);
	gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);

	grid_setup();

	solvebutton = gtk_button_new_with_label ("Solve");
	g_signal_connect (solvebutton, "clicked", G_CALLBACK (solve), NULL);
	gtk_grid_attach(GTK_GRID(grid), solvebutton, 4, 9, 1, 1);

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

