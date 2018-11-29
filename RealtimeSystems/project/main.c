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

#define XWIN                        1080  // window x resolution
#define YWIN                        780  // window y resolution
#define BKG                         0 // background color black

//------------------------------------------------------------- SW logic params

#define GUI_TASKS_PRIORITY          80 /* priority (SCHED_RR) of the GUI redrawing task */
#define CB_TASKS_PRIORITY           80 /* conveyor belt tasks priority */
#define USER_TASK_PRIORITY          80 /* user task priority */
#define PIZZA_TASK_PRIORITY         81
#define INGR_TASK_PRIORITY          80

#define GUI_TASKS_PER               20 /* period of the GUI redrawing task */
#define USER_TASK_PER               80 /* period of user serving task */
#define CB_TASK_PERIOD              1000 /* period of the conveyor belt pieces */
#define PIZZA_TASK_PER              CB_TASK_PERIOD
#define INGR_TASK_PER               PIZZA_TASK_PER

#define MAX_PIZZAS                  10 /* max number of pizzas TODO CONFLITTO CON NUM_TASK?*/
#define CB_PIECES_NUM               17 /* number of conveyor belt pieces */
#define PIZZA_INDEX_BEG             4 /* index of the first pizza task */

#define TSCALE                      1
#define INITIAL_SPEED               10 /* Initial speed*/

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

#define PIZZA_H_X                   CB_PIECE_H_X + 190 /* init pizza x coordinate */
#define PIZZA_H_Y                   CB_PIECE_H_Y + 30 /* init pizza y coordinate */
#define INGREDIENTS_NUM             6 /* Number of ingredients */

#define TOMATO_LINE_X               (TOMATO_X + 64) / 2
#define CHEESE_LINE_X               (CHEESE_X + 64) / 2
#define MUSHROOM_LINE_X             (MUSHROOM_X + 64) / 2
#define HAM_LINE_X                  (HAM_X + 64) / 2
#define OLIVE_LINE_X                (OLIVE_X + 64) / 2
#define ARTICHOKE_LINE_X            (ARTICHOKE_X + 64) / 2
#define CAMERA_LINE_X               (CAMERA_X + 64) / 2

//------------------------------------------------------------- Functions

void* display(void*);
void* conveyor_belt(void*);
void draw_conveyor_belt(int i);
void* user_inputs(void*);
void* ingredient(void*);

//------------------------------------------------------------- Global vars

int end = 0; // end flag
int nCurTasks = 0, nOrderedPizzas = 0;
float speed = INITIAL_SPEED; // Pizzas and conveyor belt pieces speed
BITMAP* pizza_dough, *cb_piece, *ingr_tomato, *ingr_cheese, *ingr_mushroom, *ingr_ham, *ingr_olive, *ingr_artichoke;

struct coordinates {
    long x;
    long y;
};

struct pizza {
    struct coordinates coord;
    int  ugly; // Has pizza passed quality test?
    char ingredients[INGREDIENTS_NUM];  // Ingredients of pizza
    char ingr_already[INGREDIENTS_NUM]; // Ingredients already on the pizza
    int  n_ingr_already; // Number of ingredients already on the pizza
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
 * Returns the scancode of a pressed key
 * @return Returns the scancode of a pressed key
 */
char get_scancode()
{
    if (keypressed())
        return readkey() >> 8;
    else return 0;
}

/**
 * Generate random pizza ingredients
 * @param ingredients random ingredients
 */
void generate_random_pizza(char *ingredients) {
    char list_ingr[] = "tcmhoa";
    int i;

    strncpy(ingredients, "", INGREDIENTS_NUM);

    srand(time(NULL));
    for (i = 0; i < INGREDIENTS_NUM; i++)
        if (rand() % 2)
            ingredients[i] = list_ingr[i];

    if(!strncmp(ingredients, "", INGREDIENTS_NUM))
        ingredients[0] = 'o'; // White pizza with only oil. I'm not hungry anymore...
}

/**
 * Wait for all tasks end
 */
void wait_for_tasks_end() {
    int i;
    int totalTasksNum = nCurTasks + nOrderedPizzas;

    for (i = 0; i < totalTasksNum; i++)
        pthread_join(i, NULL);
}

/**
 * Allegro initialization
 */
void init(void) {
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

    blit(videocam, screen, 0, 0, CAMERA_X, ICONS_Y, videocam->w, videocam->h);
    blit(oven, screen, 0, 0, OVEN_X, ICONS_Y, oven->w, oven->h);
    blit(artichoke, screen, 0, 0, ARTICHOKE_X, ICONS_Y, artichoke->w, artichoke->h);
    blit(olive, screen, 0, 0, OLIVE_X, ICONS_Y, olive->w, videocam->h);
    blit(ham, screen, 0, 0, HAM_X, ICONS_Y, ham->w, ham->h);
    blit(mushroom, screen, 0, 0, MUSHROOM_X, ICONS_Y, mushroom->w, mushroom->h);
    blit(cheese, screen, 0, 0, CHEESE_X, ICONS_Y, cheese->w, cheese->h);
    blit(tomato, screen, 0, 0, TOMATO_X, ICONS_Y, tomato->w, tomato->h);


    // create tasks to control conveyor belt pieces
    task_create(conveyor_belt, nCurTasks++, CB_TASK_PERIOD, CB_TASK_PERIOD, CB_TASKS_PRIORITY);

    // task that manages GUI
    task_create(display, nCurTasks++, GUI_TASKS_PER, GUI_TASKS_PER, GUI_TASKS_PRIORITY);

    task_create(user_inputs, nCurTasks++, USER_TASK_PER, USER_TASK_PER, USER_TASK_PRIORITY);

    task_create(ingredient, nCurTasks++, INGR_TASK_PER, INGR_TASK_PER, INGR_TASK_PRIORITY);
}

//------------------------------------------------------------------------------------- Conveyor belt

/**
 * Movement function for the conveyor belt pieces
 * @param arg task attributes (see struct task_par). You shouldn't care about this, it's injected
 * @return nothing
 */
void* conveyor_belt(void* arg) {
	int id, i, initial_piece_index = 0, movement; // task index
	int dt = TSCALE * get_task_period(arg) / 1000;

    // Init conveyor belt pieces
    id = get_task_index(arg);
    set_next_activation(id);

    for (i = 0; i < CB_PIECES_NUM; i++) {
        cb_pieces[i].bitmap = cb_piece;
        cb_pieces[i].coord.x = (i != 0 ? cb_pieces[i - 1].coord.x + cb_piece->w : CB_PIECE_H_X); // initial pos.: array
        cb_pieces[i].coord.y = CB_PIECE_H_Y;
    }

    while (!end) {
        for(i = 0; i < CB_PIECES_NUM; i++) {
            movement = speed * dt;
            cb_pieces[i].coord.x += movement;

            // handling end of conveyor belt => go to begin (i.e. the coordinates of the first piece in the queue)
            if (cb_pieces[i].coord.x > AL_MAX_H_X && cb_pieces[0].coord.x + cb_piece->w >= CB_PIECE_H_X) {
                // x of first piece - its width + the space it has just moved
                cb_pieces[i].coord.x = cb_pieces[initial_piece_index].coord.x - cb_piece->w + movement;
                initial_piece_index = i;
            }
        }

		wait_for_period(id);
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

    blit(b, screen, 0, 0, x, y, b->w, b->h);
}

//------------------------------------------------------------------------------------- Ingredients tasks

/**
 * Movement function for the conveyor belt pieces
 * @param arg task attributes (see struct task_par). You shouldn't care about this, it's injected
 * @return nothing
 */
void* ingredient(void* arg) {
    int id, i; // task index
    struct pizza *pizza;

    // Init conveyor belt pieces
    id = get_task_index(arg);
    set_next_activation(id);

    while (!end) {
        for (i = PIZZA_INDEX_BEG; i < nCurTasks + nOrderedPizzas; i++) {
            pizza = &pizzas[i];
            printf("ingredient for id %d center %ld VS %ld\n", i,(pizza->coord.x + pizza_dough->w) / 2, TOMATO_LINE_X);
            switch ((int) (pizza->coord.x + pizza_dough->w) / 2) {
                case TOMATO_LINE_X:
                    printf("%s\n", pizza->ingredients);
                    if (strstr(pizza->ingredients, "t") != NULL) {
                        pizza->ingr_already[pizza->n_ingr_already++] = 't';
                    }
                    break;
                case CHEESE_LINE_X:
                    if (strstr(pizza->ingredients, "c") != NULL) {
                        pizza->ingr_already[pizza->n_ingr_already++] = 'c';
                    }
                    break;
                case MUSHROOM_LINE_X:
                    if (strstr(pizza->ingredients, "m") != NULL) {
                        pizza->ingr_already[pizza->n_ingr_already++] = 'm';
                    }
                    break;
                case HAM_LINE_X:
                    if (strstr(pizza->ingredients, "h") != NULL) {
                        pizza->ingr_already[pizza->n_ingr_already++] = 'h';
                    }
                    break;
                case OLIVE_LINE_X:
                    if (strstr(pizza->ingredients, "o") != NULL) {
                        pizza->ingr_already[pizza->n_ingr_already++] = 'o';
                    }
                    break;
                case ARTICHOKE_LINE_X:
                    if (strstr(pizza->ingredients, "a") != NULL) {
                        pizza->ingr_already[pizza->n_ingr_already++] = 'a';
                    }
                    break;
                default: break;
            }
        }

        wait_for_period(id);
    }
}

//------------------------------------------------------------------------------------- Pizzas tasks

/**
 * Draw a pizza
 * @param index pizza index
 */
void draw_pizza(int index) {
    struct pizza pizza = pizzas[index];
    int x       = pizza.coord.x;
    int y       = pizza.coord.y;

    blit(pizza_dough, screen, 0, 0, x, y, pizza_dough->w, pizza_dough->h);
    if (strstr(pizza.ingr_already, "t") != NULL)
        blit(ingr_tomato, screen, 0, 0, x + 3, y + 3, ingr_tomato->w, ingr_tomato->h);
    if (strstr(pizza.ingr_already, "c") != NULL)
        blit(ingr_cheese, screen, 0, 0, x + 3, y + 3, ingr_cheese->w, ingr_cheese->h);
    if (strstr(pizza.ingr_already, "m") != NULL)
        blit(ingr_mushroom, screen, 0, 0, x + 3, y + 3, ingr_mushroom->w, ingr_mushroom->h);
    if (strstr(pizza.ingr_already, "h") != NULL)
        blit(ingr_ham, screen, 0, 0, x + 3, y + 3, ingr_ham->w, ingr_ham->h);
    if (strstr(pizza.ingr_already, "o") != NULL)
        blit(ingr_olive, screen, 0, 0, x + 3, y + 13, ingr_olive->w, ingr_olive->h);
    if (strstr(pizza.ingr_already, "a") != NULL)
        blit(ingr_artichoke, screen, 0, 0, x + 3, y + 3, ingr_artichoke->w, ingr_artichoke->h);
}

/**
 * Task to control a pizza motion
 * @param args task args
 * @return nothing
 */
void* pizza_motion(void* arg) {
    int id = get_task_index(arg);
    int dt = (int) TSCALE * get_task_period(arg) / 1000;

    set_next_activation(id);
    pizzas[id].coord.x = PIZZA_H_X;
    pizzas[id].coord.y = PIZZA_H_Y;

    while (!end) {
        pizzas[id].coord.x += speed * dt;

        wait_for_period(id);
    }
}

/**
 * Decides whether a new pizza can be created immediately or it has to be enqueued
 * @param ingredients ingredients of new pizza
 */
void manageOrders(char *ingredients) {
    int new_pizza_id;
    if(nOrderedPizzas + 1 >= MAX_PIZZAS) {
        printf("Sorry, pizza cannot be ordered.\n");
        return;
    }

    new_pizza_id = nCurTasks + nOrderedPizzas;
    strcpy(pizzas[new_pizza_id].ingredients, ingredients);
    strncpy(pizzas[new_pizza_id].ingr_already, "", INGREDIENTS_NUM);
    pizzas[new_pizza_id].n_ingr_already = 0;
    task_create(pizza_motion, new_pizza_id, PIZZA_TASK_PER, PIZZA_TASK_PER, PIZZA_TASK_PRIORITY);

    nOrderedPizzas++;
}

//------------------------------------------------------------------------------------- User task

void* user_inputs(void* arg) {
    int id = get_task_index(arg);
    char scan;
    char ingredients[INGREDIENTS_NUM] = { ' ' };
    int curIngredient = 0;

    set_next_activation(id);
    do {
        scan = get_scancode();
        switch (scan) {
            case KEY_UP:
                // todo
                break;
            case KEY_DOWN:
                // todo
                break;
            case KEY_T:
                ingredients[curIngredient++] = 't';
                break;
            case KEY_C:
                ingredients[curIngredient++] = 'c';
                break;
            case KEY_M:
                ingredients[curIngredient++] = 'm';
                break;
            case KEY_H:
                ingredients[curIngredient++] = 'h';
                break;
            case KEY_O:
                ingredients[curIngredient++] = 'o';
                break;
            case KEY_A:
                ingredients[curIngredient++] = 'a';
                break;
            case KEY_ENTER:
                // You cannot create a new pizza here. You need the first ingredient manager to be able to generate one too
                if (curIngredient == 0) // then user has only pressed ENTER => generate random ingredients
                    generate_random_pizza(ingredients);

                curIngredient = 0;
                printf("Ordered pizza: %s\n", ingredients);

                manageOrders(ingredients);

                strncpy(ingredients, "", INGREDIENTS_NUM);
                break;
            case KEY_ESC:
                printf("KEY_ESC: exiting game\n");
                end = 1;
                break;
            default:
                break;
        }
        wait_for_period(id);
    } while (scan != KEY_ESC);
}

//------------------------------------------------------------------------------------- Support logic (global management)

/**
 * Task refreshing the GUI
 * @param arg its argument
 * @return
 */
void* display(void* arg) {
	int id, i; // task index

	id = get_task_index(arg);

	set_next_activation(id);
	while (!end) {
		rectfill(screen, 0, CB_PIECE_H_Y, XWIN-1, YWIN-1, BKG);
		for (i = 0; i < CB_PIECES_NUM; i++) {
            draw_conveyor_belt(i);
		}

		for(i = PIZZA_INDEX_BEG; i < PIZZA_INDEX_BEG + nOrderedPizzas; i++)
		    draw_pizza(i);

		//if ( has_deadline_miss(i) ) // check for deadline miss
		//	; //show_dmiss(id); todo

		wait_for_period(id);
	}
}



int main(void) {
    init();

    while(!end);

    wait_for_tasks_end();
    allegro_exit();

    return 0;
}