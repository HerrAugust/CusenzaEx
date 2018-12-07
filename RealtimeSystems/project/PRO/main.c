/**
  * Real-time program to produce pizzas on an assembly line. Cuncurrent pizzas are supported
  *
  * Note: task ID <-> pizzas[i] is done with +/- PIZZA_INDEX_BEG in the code
  *
  * Contributions:
  * Prof. Giorgio Buttazzo  - author of "framework" (ptask, timeutil, ..)
  * Agostino Mascitti - documentation & code (Nov - Dic 2018)
  */

#include <stdlib.h> // include standard lib first
#include <stdio.h>
#include <sched.h>
#include <allegro.h>
#include <assert.h>

//-------------------------------------------------------------
// GLOBAL CONSTANTS
//------------------------------------------------------------- Window params

#define XWIN                        1080  /* window x resolution */
#define YWIN                        1000   /* window y resolution */
#define BKG                         0     /* background color black */

//------------------------------------------------------------- SW logic params

#define GUI_TASKS_PRIORITY          80 /* priority (SCHED_RR) of the GUI redrawing task */
#define CB_TASKS_PRIORITY           80 /* conveyor belt tasks priority */
#define USER_TASK_PRIORITY          80 /* user task priority */
#define PIZZA_TASK_PRIORITY         81 /* pizzas tasks priority */
#define INGR_TASK_PRIORITY          80 /* ingredients task priority */
#define PM_TASK_PRIORITY            80 /* Pizzas manager priority */
#define MON_TASK_PRIORITY           80 /* Monitor window task priority */

#define GUI_TASKS_PER               20 /* period of the GUI redrawing task */
#define USER_TASK_PER               100 /* period of user serving task */
#define CB_TASK_PERIOD              100 /* period of the conveyor belt pieces */
#define PIZZA_TASK_PER              80 /* period between pizza redrawings */
#define INGR_TASK_PER               80 /* ingredients task period */
#define PM_TASK_PER                 200 /* period of pizzas manager task */
#define MON_TASK_PER                80 /* monitor window task period */

#define MAX_PIZZAS                  10 /* max number of pizzas */
#define CB_PIECES_NUM               17 /* number of conveyor belt pieces */
#define PIZZA_INDEX_BEG             11 /* index of the first pizza task */

#define QUEUE_LENGTH                5 /* Pizzas queue length */

#define TSCALE                      9.0 /* time scale factor */
#define INITIAL_SPEED               26 /* Initial speed*/
#define MIN_SPEED                   INITIAL_SPEED /* Min supported speed */
#define MAX_SPEED                   30 /* Max supported speed */

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

#define CB_PIECE_H_X                0 /* init horizontal conveyor belt piece x coord */
#define CB_PIECE_H_Y                (ICONS_Y + 90) /* init horizontal conveyor belt piece y coord */
#define AL_MAX_H_X                  XWIN /* Where the horizontal assembly line ends */

#define PIZZA_H_X                   TOMATO_X - 130 /* init pizza x coordinate */
#define PIZZA_H_Y                   CB_PIECE_H_Y + 30 /* init pizza y coordinate */
#define INGREDIENTS_NUM             6 /* Number of ingredients */

#define TOMATO_LINE_X               TOMATO_X + 64 / 2
#define CHEESE_LINE_X               CHEESE_X + 64 / 2
#define MUSHROOM_LINE_X             MUSHROOM_X + 64 / 2
#define HAM_LINE_X                  HAM_X + 64 / 2
#define OLIVE_LINE_X                OLIVE_X + 64 / 2
#define ARTICHOKE_LINE_X            ARTICHOKE_X + 64 / 2
#define CAMERA_LINE_X               CAMERA_X + 64 / 2

#define COLOR_INGR_TOMATO           makecol(215,24,24)
#define COLOR_INGR_CHEESE           makecol(255,243,207)
#define COLOR_INGR_MUSHROOM         makecol(101,101,101)
#define COLOR_INGR_OLIVE            makecol(24,24,24)
#define COLOR_INGR_HAM              makecol(255,0,0)
#define COLOR_INGR_ARTICHOKE        makecol(81,235,48)

//------------------------------------------------------------- Monitor window

#define MONITOR_WIDTH               200
#define MONITOR_HEIGHT              200
#define MONITOR_X                   10
#define MONITOR_Y                   YWIN - MONITOR_HEIGHT - 10

//------------------------------------------------------------- Asides

#define DEADLINE_MISS_X             XWIN - 150
#define DEADLINE_MISS_Y             0
BITMAP* pizza_dough, *cb_piece, *ingr_tomato, *ingr_cheese, *ingr_mushroom, *ingr_ham, *ingr_olive, *ingr_artichoke, *monitor_bmp;
BITMAP *videocam, *oven, *tomato, *cheese, *mushroom, *ham, *olive, *artichoke; // never moving objects

void show_string(char string[80], int x, int y, int color) {
    textout_ex(screen, font, string, x, y, color, BKG);
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
    srand(time(NULL));
    set_trans_blender(128, 128, 128, 128); // for draw_trans_sprite()

	// load icons
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
    ingr_tomato = load_bitmap("icons/ingr_tomato.bmp", NULL);
    ingr_cheese = load_bitmap("icons/ingr_cheese.bmp", NULL);
    ingr_ham = load_bitmap("icons/ingr_ham.bmp", NULL);
    ingr_mushroom = load_bitmap("icons/ingr_mushroom.bmp", NULL);
    ingr_olive = load_bitmap("icons/ingr_olive.bmp", NULL);
    ingr_artichoke = load_bitmap("icons/ingr_artichoke.bmp", NULL);
    assert(videocam != NULL); assert(pizza_dough != NULL); assert(cheese != NULL); assert(mushroom != NULL); assert(tomato != NULL);
    assert(ham != NULL); assert(olive != NULL); assert(artichoke != NULL); assert(cb_piece != NULL); assert(oven != NULL);
    assert(ingr_tomato != NULL); assert(ingr_cheese != NULL); assert(ingr_ham != NULL); assert(ingr_mushroom != NULL);
    assert(ingr_olive != NULL); assert(ingr_artichoke != NULL);
}


void draw_instructions() {
    // instructions on GUI
    show_string("Press ENTER to order a random pizza or some letters + ENTER for a specific one:", 10, 10, 255);
    show_string("  t - tomato", 10, 25, 255);
    show_string("  c - cheese", 10, 40, 255);
    show_string("  m - mushrooms", 10, 55, 255);
    show_string("  h - ham", 10, 70, 255);
    show_string("  o - olives", 10, 85, 255);
    show_string("  a - artichokes", 10, 100, 255);
    show_string("  up/down - pizzas speed", 10, 115, 255);
}

void draw_ingr_icons() {
    draw_sprite(screen, videocam, CAMERA_X, ICONS_Y);
    draw_sprite(screen, oven, OVEN_X, ICONS_Y);
    draw_sprite(screen, artichoke, ARTICHOKE_X, ICONS_Y);
    draw_sprite(screen, olive, OLIVE_X, ICONS_Y);
    draw_sprite(screen, ham, HAM_X, ICONS_Y);
    draw_sprite(screen, mushroom, MUSHROOM_X, ICONS_Y);
    draw_sprite(screen, cheese, CHEESE_X, ICONS_Y);
    draw_sprite(screen, tomato, TOMATO_X, ICONS_Y);
}



int main(void) {

    init();

    BITMAP* monitor_bmp = create_bitmap(MONITOR_WIDTH, MONITOR_HEIGHT);
    clear_to_color(monitor_bmp, 255);
    
    draw_ingr_icons();
    draw_instructions();

    blit(screen, monitor_bmp, 0,0,0,0,64, 64);
    draw_sprite(screen, monitor_bmp, TOMATO_X, ICONS_Y);

    while(1);

    return 0;
}