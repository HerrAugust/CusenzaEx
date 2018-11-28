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
#include <assert.h>
#include "ptask.h" // a lib for periodic tasks

//-------------------------------------------------------------
// GLOBAL CONSTANTS
//------------------------------------------------------------- Window params

#define XWIN                        1024 // window x resolution
#define YWIN                        780  // window y resolution
#define BKG                         0 // background color black

//------------------------------------------------------------- SW logic params

#define GUI_TASKS_PER               20 /* period of the GUI redrawing task */
#define GUI_TASKS_PRIORITY          80 /* priority (SCHED_RR) of the GUI redrawing task */

#define USER_TASK_PER               80 /* period of user serving task */

#define MAX_PIZZAS                  10 /* max number of pizzas */
#define CB_PIECES                   15 /* number of conveyor belt pieces */
#define CB_INDEX_BEG                0 /* index of the first conveyor belt piece */
#define PIZZA_INDEX_BEG             (CB_INDEX_BEG + CB_PIECES) /* index of the first pizza */

#define AL_BEGIN_X                  50 /* where the assembly line should begin (x) */
#define AL_BEGIN_Y                  150 /* where the assembly line should begin (y) */

//------------------------------------------------------------- Icons params

#define ICONS_Y                     (YWIN - 580)
#define ICONS_OFF_X                 80

#define CAMERA_X                    (XWIN - 250)
#define OVEN_X                      (CAMERA_X - ICONS_OFF_X - 30)
#define ARTICHOKE_X                 (OVEN_X - ICONS_OFF_X)
#define OLIVE_X                     (ARTICHOKE_X - ICONS_OFF_X)
#define HAM_X                       (OLIVE_X - ICONS_OFF_X)
#define MUSHROOM_X                  (HAM_X - ICONS_OFF_X)
#define CHEESE_X                    (MUSHROOM_X - ICONS_OFF_X)
#define TOMATO_X                    (CHEESE_X - ICONS_OFF_X)

//------------------------------------------------------------- Functions

void* display(void*);
void* conveyor_belt(void*);
void draw_conveyor_belt(int i);

//------------------------------------------------------------- Global vars

int end = 0; // end flag
BITMAP* pizza_dough, *cb_piece;

struct coordinates {
    long x;
    long y;
} cb_coordinates[CB_PIECES]; // status of pieces of conveyor belt

struct pizza {
    struct coordinates coord;

} pizzas[MAX_PIZZAS];

//------------------------------------------------------------------------------------- Utility functions

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
 * Wait for task end
 * @param i
 */
void wait_for_task_end(pthread_t i) {
    pthread_join(i, NULL);
}

/**
 * Allegro initialization
 */
void init(void) {
	int i;

	allegro_init();
    set_color_depth(32); // set max color depth
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, XWIN, YWIN, 0, 0);
	clear_to_color(screen, BKG);
	install_keyboard();

	// instructions on GUI
	show_string("Press ENTER to order a random pizza or some letters + ENTER for a specific one:", 10, 10, 14);
	show_string("  t - tomato", 10, 25, 14);
	show_string("  c - cheese", 10, 40, 14);
	show_string("  m - mushrooms", 10, 55, 14);
	show_string("  h - ham", 10, 70, 14);
	show_string("  o - olives", 10, 85, 14);
	show_string("  a - artichokes", 10, 100, 14);

	// load icons
	BITMAP *videocam, *oven, *tomato, *cheese, *mushroom, *ham, *olive, *artichoke; // never moving objects
    videocam = load_bitmap("icons/videocam.bmp", NULL);
    pizza_dough = load_bitmap("icons/dough.bmp", NULL);
    oven = load_bitmap("icons/oven.bmp", NULL);
    cheese = load_bitmap("icons/cheese.bmp", NULL);
    mushroom = load_bitmap("icons/mushroom.bmp", NULL);
    ham = load_bitmap("icons/ham.bmp", NULL);
    olive = load_bitmap("icons/olive.bmp", NULL);
    artichoke = load_bitmap("icons/artichoke.bmp", NULL);
    tomato = load_bitmap("icons/tomato.bmp", NULL);
    cb_piece = load_bitmap("icons/cb_piece.bmp", NULL);
    assert(videocam != NULL); assert(pizza_dough != NULL); assert(cheese != NULL); assert(mushroom != NULL); assert(tomato != NULL);
    assert(ham != NULL); assert(olive != NULL); assert(artichoke != NULL); assert(cb_piece != NULL); assert(oven != NULL);

    blit(videocam, screen, 0, 0, CAMERA_X, ICONS_Y, videocam->w, videocam->h);
    blit(oven, screen, 0, 0, OVEN_X, ICONS_Y, oven->w, oven->h);
    blit(artichoke, screen, 0, 0, ARTICHOKE_X, ICONS_Y, artichoke->w, artichoke->h);
    blit(olive, screen, 0, 0, OLIVE_X, ICONS_Y, olive->w, videocam->h);
    blit(ham, screen, 0, 0, HAM_X, ICONS_Y, ham->w, ham->h);
    blit(mushroom, screen, 0, 0, MUSHROOM_X, ICONS_Y, mushroom->w, mushroom->h);
    blit(cheese, screen, 0, 0, CHEESE_X, ICONS_Y, cheese->w, cheese->h);
    blit(tomato, screen, 0, 0, TOMATO_X, ICONS_Y, tomato->w, tomato->h);


    return;

    // INGREDIENTS TASKS FIRST TODO
    for (i = CB_INDEX_BEG; i < CB_PIECES; i++) {
        task_create(conveyor_belt, i, GUI_TASKS_PER, GUI_TASKS_PER, GUI_TASKS_PRIORITY);
    }

    // task that manages GUI
    task_create(display, i + 1, GUI_TASKS_PER, GUI_TASKS_PER, GUI_TASKS_PRIORITY);
}

//------------------------------------------------------------------------------------- Conveyor belt

/**
 * Function executed by the conveyor belts
 * @param arg task attributes (see struct task_par)
 * @return
 */
void* conveyor_belt(void* arg) {
	int i; // task index
	char mes[80];

	i = get_task_index(arg);
	sprintf(mes, "I'M TASK %d, T = %d", i, get_task_period(arg));

	// Init conveyor belt pieces
	cb_coordinates[i].x = AL_BEGIN_X + (i != 0 ? i * cb_coordinates[i - 1].x : 0);
	cb_coordinates[i].y = AL_BEGIN_Y;

	while (!end) {
		cb_coordinates[i].x += (i != 0 ? cb_coordinates[i - 1].x : AL_BEGIN_X);
		cb_coordinates[i].y += cb_coordinates[i].y;

		// handling end of conveyor belt => go to begin
		//todo

		wait_for_period(i);
	}
}

/**
 * Draw conveyor belt piece
 * @param index conveyor belt piece index
 */
void draw_conveyor_belt(int index) {

}

//------------------------------------------------------------------------------------- Support logic (global management)

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
		//rectfill(screen, XBASE+1, YBASE+1, XWIN-1, YWIN-1, BKG);
		for (i = CB_INDEX_BEG; i < CB_PIECES; i++) {
			draw_conveyor_belt(i);
		}
		if ( has_deadline_miss(i) ) // check for deadline miss
			; //show_dmiss(id); todo
		wait_for_period(id);
	}
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