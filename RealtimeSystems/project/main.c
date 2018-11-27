/**
  * HELLO.C: SIMPLE DEMO WHERE EACH PERIODIC TASK
  * DISPLAYS A CHARACTER AT EVERY PERIOD
  *
  * Contributions:
  * Giorgio Buttazzo- original author
  * Agostino Mascitti - Documentation & code organization (Nov 2018)
  */

#include <stdlib.h> // include standard lib first
#include <stdio.h>
#include <sched.h>
#include <allegro.h>
#include "ptask.h" // a lib for periodic tasks

//-------------------------------------------------------------
// GLOBAL CONSTANTS
//------------------------------------------------------------- Window params

#define XWIN 640 // window x resolution
#define YWIN 480 // window y resolution
#define XBASE 40 // X start for the message
#define YBASE 50 // Y level for the first task
#define BKG 0 // background color black

//------------------------------------------------------------- SW logic params

#define GUI_TASKS_PER 20
#define GUI_TASKS_PRIORITY 80

#define USER_TASK_PER 80

#define MAX_PIZZAS 10
#define CB_PIECES  15

#define TSCALE 10 /* time scale factor */

//------------------------------------------------------------- Functions

void* display(void*);
void* conveyor_belt(void*);

//------------------------------------------------------------- Global vars

int end = 0; // end flag
int nCurTask = 0;
struct pizza pizzas[MAX_PIZZAS];
struct coordinates cb_coordinates[CB_PIECES]; // status of pieces of conveyor belt

//-------------------------------------------------------------

/**
 * Shows a string on screen
 * @param string the string to be shown
 * @param x x coordinate
 * @param y y coordinate
 * @param color color
 */
void show_string(char string[80], int x, int y, int color) {
	textout_ex(screen, font, string, x, y, color, BKG);
}

/**
 * Allegro initialization
 */
void init(void) {
	int i;

	allegro_init();
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, XWIN, YWIN, 0, 0);
	clear_to_color(screen, BKG);
	install_keyboard();

	// instructions
	show_string("Press ENTER to order a random pizza or some letters + ENTER for a specific one:", 10, 10, 14);
	show_string("  t - tomato", 10, 25, 14);
	show_string("  c - cheese", 10, 40, 14);
	show_string("  m - mushrooms", 10, 55, 14);
	show_string("  h - ham", 10, 70, 14);
	show_string("  o - olives", 10, 85, 14);
	show_string("  a - artichokes", 10, 100, 14);

	// task that manages GUI
	task_create(display, nCurTask, GUI_TASKS_PER, GUI_TASKS_PER, GUI_TASKS_PRIORITY);
	nCurTask++;

	// basic GUI: conveyor belts (x2) and icons
	// INGREDIENTS TASKS FIRST TODO.
	for (i = 0; i < 2; i++, nCurTask++)
		task_create(conveyor_belt, nCurTask, GUI_TASKS_PER, GUI_TASKS_PER, GUI_TASKS_PRIORITY);

}

/**
 * Function executed by the conveyor belts
 * @param arg task attributes (see struct task_par)
 * @return
 */
void* conveyor_belt(void* arg) {
	int i, k = 0; // task and character index
	int x, y;
	char buf[2];  // temp buffer for 1 character string
	char mes[80];
	float dt;

	i = get_task_index(arg);
	sprintf(mes, "I'M TASK %d, T = %d", i, get_task_period(arg));

	// Init conveyor belt pieces
	for (i = 0; i < )
	dt = TSCALE*(float)get_task_period(i)/1000;

	while (!end) {
		cb_coordinates[i].vy -= G*dt;
		cb_coordinates[i].x += cb_coordinates[i].vx * dt;
		cb_coordinates[i].y += cb_coordinates[i].vy*dt - g*dt*dt/2;

		wait_for_period(i);
	}
}

/**
 * Task refreshing the GUI
 * @param arg its argument
 * @return
 */
void* display(void* arg)
{
	int id, i; // task index

	id = get_task_index(arg);

	while (!end) {
		rectfill(screen, XBASE+1, YBASE+1, XWIN-1, YWIN-1, BKG);
		for (i = 1; i < nGUItasks; i++) {  // ID = 1 is for this task, refreshing the GUI
			draw_conveyor_belt(i);
		}
		if ( has_deadline_miss(i) ) // check for deadline miss
			; //show_dmiss(id); todo
		wait_for_period(id);
	}
}

void wait_for_task_end(pthread_t i) {
	pthread_join(i, NULL);
}

int main(void) {
    int i = 0; // GUI
    char scan;

    init();

    /*do {
        scan = 0;
        if (keypressed()) scan = readkey() >> 8;
        if (scan == KEY_SPACE && nCurTask < NUM_TASKS) {
            task_create(hello, nCurTask, PER + nCurTask * PINC, PER + nCurTask * PINC, 50);
			nCurTask++;
        }
    } while (scan != KEY_ESC);

    end = 1;
    for (i = 0; i <= nCurTask; i++)
        wait_for_task_end(i);*/

    readkey();
    allegro_exit();

    return 0;
}