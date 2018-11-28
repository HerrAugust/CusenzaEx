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

#define GUI_TASKS_PRIORITY          80 /* priority (SCHED_RR) of the GUI redrawing task */
#define CB_TASKS_PRIORITY           80 /* conveyor belt tasks priority */

#define GUI_TASKS_PER               20 /* period of the GUI redrawing task */
#define USER_TASK_PER               80 /* period of user serving task */
#define CB_TASK_PERIOD              1000

#define MAX_PIZZAS                  10 /* max number of pizzas TODO CONFLITTO CON NUM_TASK?*/
#define CB_PIECES_NUM               2 /* number of conveyor belt pieces */
#define CB_INDEX_BEG                0 /* index of the first conveyor belt piece */
#define PIZZA_INDEX_BEG             (CB_INDEX_BEG + CB_PIECES) /* index of the first pizza */

//------------------------------------------------------------- Icons params

#define ICONS_Y                     (YWIN - 580) /* y coordinate of icons */
#define ICONS_OFF_X                 80 /* Offset between 2 icons */

#define CAMERA_X                    (XWIN - 250)
#define OVEN_X                      (CAMERA_X - ICONS_OFF_X - 30)
#define ARTICHOKE_X                 (OVEN_X - ICONS_OFF_X)
#define OLIVE_X                     (ARTICHOKE_X - ICONS_OFF_X)
#define HAM_X                       (OLIVE_X - ICONS_OFF_X)
#define MUSHROOM_X                  (HAM_X - ICONS_OFF_X)
#define CHEESE_X                    (MUSHROOM_X - ICONS_OFF_X)
#define TOMATO_X                    (CHEESE_X - ICONS_OFF_X)

#define CB_PIECE_H_X                100 /* horizontal conveyor belt piece x coord */
#define CB_PIECE_H_Y                (ICONS_Y + 90) /* horizontal conveyor belt piece y coord */

#define DELTA_X                     30 /* X offset for conveyor belt pieces*/

#define AL_MAX_H_X                  XWIN /* Where the horizontal assembly line ends */

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
};

struct pizza {
    struct coordinates coord;

} pizzas[MAX_PIZZAS];

struct cb_piece {
    struct coordinates coord;
    BITMAP*  bitmap;
} cb_pieces[CB_PIECES_NUM];

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


    // create tasks to control conveyor belt pieces
    for (i = CB_INDEX_BEG; i < CB_PIECES_NUM; i++) {
        task_create(conveyor_belt, i, CB_TASK_PERIOD, CB_TASK_PERIOD, CB_TASKS_PRIORITY);
    }

    // task that manages GUI
    task_create(display, i + 1, GUI_TASKS_PER, GUI_TASKS_PER, GUI_TASKS_PRIORITY);
}

//------------------------------------------------------------------------------------- Conveyor belt

/**
 * Movement function for the conveyor belt pieces
 * @param arg task attributes (see struct task_par). You shouldn't care about this, it's injected
 * @return nothing
 */
void* conveyor_belt(void* arg) {
	int i; // task index

	i = get_task_index(arg);

	// Init conveyor belt pieces
    cb_pieces[i].bitmap  = cb_piece;
    cb_pieces[i].coord.x = CB_PIECE_H_X + (i != 0 ? cb_pieces[i - 1].coord.x + cb_piece->w : 0);
    cb_pieces[i].coord.y = CB_PIECE_H_Y;
    printf("");

    set_activation(i);
	while (!end) {
        cb_pieces[i].coord.x += cb_pieces[i].coord.x + DELTA_X;

		// handling end of conveyor belt => go to begin
		if(cb_pieces[i].coord.x > AL_MAX_H_X) cb_pieces[i].coord.x = CB_PIECE_H_X;

		wait_for_period(i);
	}
}

/**
 * Draw conveyor belt piece
 * @param index conveyor belt piece index
 */
void draw_conveyor_belt(int index) {
    BITMAP* b = cb_pieces[index].bitmap;
    int x = cb_pieces[index].coord.x;
    int y = cb_pieces[index].coord.y;
    printf("draw_conveyor_belt %d: (%d,%d)\n", index, x, y);

    blit(b, screen, 0, 0, x, y, b->w, b->h);

    wait_for_period(index);
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

	set_activation(id);
	while (!end) {
		rectfill(screen, 0, CB_PIECE_H_Y, XWIN-1, YWIN-1, BKG);
		for (i = CB_INDEX_BEG; i < CB_PIECES_NUM; i++) {
            draw_conveyor_belt(i);
		}
		//if ( has_deadline_miss(i) ) // check for deadline miss
		//	; //show_dmiss(id); todo
		wait_for_period(id);
	}
}



int main(void) {
    int i = 0; // GUI
    char scan;

    init();

    do {
        scan = 0;
        if (keypressed()) scan = readkey() >> 8;
        if (scan == KEY_SPACE && MAX_PIZZAS < NUM_TASKS) {

        }
    } while (scan != KEY_ESC);

    end = 1;
    // todo set task detatched

    readkey();
    allegro_exit();

    return 0;
}