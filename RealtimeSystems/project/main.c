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
#include <semaphore.h>
#include "ptask.h" // a lib for periodic tasks

//-------------------------------------------------------------
// GLOBAL CONSTANTS
//------------------------------------------------------------- Window params

#define XWIN                        1080  /* window x resolution */
#define YWIN                        780   /* window y resolution */
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
#define USER_TASK_PER               80 /* period of user serving task */
#define CB_TASK_PERIOD              100 /* period of the conveyor belt pieces */
#define PIZZA_TASK_PER              CB_TASK_PERIOD /* period between pizza redrawings */
#define INGR_TASK_PER               PIZZA_TASK_PER /* ingredients task period */
#define PM_TASK_PER                 200 /* period of pizzas manager task */
#define MON_TASK_PER                PIZZA_TASK_PER /* monitor window task period */

#define MAX_PIZZAS                  10 /* max number of pizzas TODO CONFLITTO CON NUM_TASK?*/
#define CB_PIECES_NUM               17 /* number of conveyor belt pieces */
#define PIZZA_INDEX_BEG             7 /* index of the first pizza task */

#define QUEUE_LENGTH                5 /* Pizzas queue length */

#define TSCALE                      9.0 /* time scale factor */
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

#define PIZZA_H_X                   CB_PIECE_H_X + 30 /* init pizza x coordinate */
#define PIZZA_H_Y                   CB_PIECE_H_Y + 30 /* init pizza y coordinate */
#define INGREDIENTS_NUM             6 /* Number of ingredients */

#define TOMATO_LINE_X               TOMATO_X + 64 / 2
#define CHEESE_LINE_X               CHEESE_X + 64 / 2
#define MUSHROOM_LINE_X             MUSHROOM_X + 64 / 2
#define HAM_LINE_X                  HAM_X + 64 / 2
#define OLIVE_LINE_X                OLIVE_X + 64 / 2
#define ARTICHOKE_LINE_X            ARTICHOKE_X + 64 / 2
#define CAMERA_LINE_X               CAMERA_X + 64 / 2

//------------------------------------------------------------- Monitor window

#define MONITOR_X                   50
#define MONITOR_Y                   450
#define MONITOR_WIDTH               200
#define MONITOR_HEIGHT              200

//------------------------------------------------------------- Functions

void* display(void*);
void* conveyor_belt(void*);
void draw_conveyor_belt(int i);
void* user_inputs(void*);
void* ingredient(void*);
void* new_orders(void* arg) ;
void* monitor(void* arg);
void* pizza_motion(void* arg) ;

//------------------------------------------------------------- Global vars
int end = 0; // End of program flag

int nCurTasks = 0, nOrderedPizzas = 0; // Counters of currently active tasks and pizzas on the assembly line
int lastPizzaID = PIZZA_INDEX_BEG;
float speed = INITIAL_SPEED; // Pizzas and conveyor belt pieces speed
BITMAP* pizza_dough, *cb_piece, *ingr_tomato, *ingr_cheese, *ingr_mushroom, *ingr_ham, *ingr_olive, *ingr_artichoke;
BITMAP* monitor_bmp;

char ordered_pizzas_queue[QUEUE_LENGTH][INGREDIENTS_NUM];
int  index_last_queue = -1;
sem_t sem_queue;

struct coordinates {
    float x;
    float y;
};

struct pizza {
    struct coordinates coord;
    int  ugly; // Has pizza passed quality test?
    char ingredients[INGREDIENTS_NUM];  // Ingredients of pizza
    char ingr_already[INGREDIENTS_NUM]; // Ingredients already on the pizza
    int  shipped; // 1 if pizza can be destroyed and space left to the next one
    BITMAP* pizza_with_ingr; // pizza dough with its ingredients
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

int str_contains(char *str, char to_check) {
    char buf[2] = "";
    buf[0] = to_check;

    return strstr(str, buf) != NULL;
}

/**
 * Returns the scancode of a pressed key
 * @return Returns the scancode of a pressed key
 */
char get_scancode() {
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
    srand(time(NULL));
    set_trans_blender(128, 128, 128, 128); // for draw_trans_sprite()
    sem_init(&sem_queue, 0, 1); // binary semaphore

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

    draw_sprite(screen, videocam, CAMERA_X, ICONS_Y);
    draw_sprite(screen, oven, OVEN_X, ICONS_Y);
    draw_sprite(screen, artichoke, ARTICHOKE_X, ICONS_Y);
    draw_sprite(screen, olive, OLIVE_X, ICONS_Y);
    draw_sprite(screen, ham, HAM_X, ICONS_Y);
    draw_sprite(screen, mushroom, MUSHROOM_X, ICONS_Y);
    draw_sprite(screen, cheese, CHEESE_X, ICONS_Y);
    draw_sprite(screen, tomato, TOMATO_X, ICONS_Y);


    // create tasks to control conveyor belt pieces
    task_create(conveyor_belt, nCurTasks++, CB_TASK_PERIOD, CB_TASK_PERIOD, CB_TASKS_PRIORITY);

    // task that manages GUI
    task_create(display, nCurTasks++, GUI_TASKS_PER, GUI_TASKS_PER, GUI_TASKS_PRIORITY);

    task_create(user_inputs, nCurTasks++, USER_TASK_PER, USER_TASK_PER, USER_TASK_PRIORITY);

    task_create(ingredient, nCurTasks++, INGR_TASK_PER, INGR_TASK_PER, INGR_TASK_PRIORITY);

    task_create(new_orders, nCurTasks++, PM_TASK_PER, PM_TASK_PER, PM_TASK_PRIORITY);

    task_create(monitor, nCurTasks++, MON_TASK_PER, MON_TASK_PER, MON_TASK_PRIORITY);
}

//------------------------------------------------------------------------------------- Conveyor belt

/**
 * Movement function for the conveyor belt pieces
 * @param arg task attributes (see struct task_par). You shouldn't care about this, it's injected
 * @return nothing
 */
void* conveyor_belt(void* arg) {
	int id, i, initial_piece_index = 0; // task index
	float dt = TSCALE * (float) get_task_period(arg) / 1000;
	float movement;

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
    float x = cb_pieces[index].coord.x;
    float y = cb_pieces[index].coord.y;

    draw_sprite(screen, b, x, y);
}

//------------------------------------------------------------------------------------- Ingredients tasks

/**
 * Manages each ingredient machine, putting the ingredient when needed
 * @param arg task attributes
 * @return nothing
 */
void* ingredient(void* arg) {
    int id, i; // task index
    struct pizza *pizza;

    // Init conveyor belt pieces
    id = get_task_index(arg);
    set_next_activation(id);
    while (!end) {
        for (i = PIZZA_INDEX_BEG; i < PIZZA_INDEX_BEG + nOrderedPizzas; i++) {
            pizza = &pizzas[i];
            printf("%d vs %d\n", (int) pizza->coord.x + (pizza_dough->w / 2), TOMATO_LINE_X);
            switch ((int) pizza->coord.x + pizza_dough->w / 2) {
                case TOMATO_LINE_X:
                    if (strstr(pizza->ingredients, "t") != NULL) {
                        if (rand() % 2) {
                            printf("Tomato machine error: no such ingredient for %d\n", i);
                            break;
                        }
                        pizza->ingr_already[0] = 't';
                        draw_sprite(pizza->pizza_with_ingr, ingr_tomato, 6, 8);
                    }
                    break;
                case CHEESE_LINE_X:
                    if (strstr(pizza->ingredients, "c") != NULL) {
                        if (rand() % 2) {
                            printf("Cheese machine error: no such ingredient for %d\n",i);
                            break;
                        }
                        pizza->ingr_already[1] = 'c';
                        draw_sprite(pizza->pizza_with_ingr, ingr_cheese, 6, 10);
                        printf("pizza now has %s\n", pizza->ingr_already);
                    }
                    break;
                case MUSHROOM_LINE_X:
                    if (strstr(pizza->ingredients, "m") != NULL) {
                        if (rand() % 2) {
                            printf("Mushroom machine error: no such ingredient\n");
                            break;
                        }
                        pizza->ingr_already[2] = 'm';
                        draw_sprite(pizza->pizza_with_ingr, ingr_mushroom, 25, 25);
                    }
                    break;
                case HAM_LINE_X:
                    if (strstr(pizza->ingredients, "h") != NULL) {
                        if (rand() % 2) {
                            printf("Ham machine error: no such ingredient\n");
                            break;
                        }
                        pizza->ingr_already[3] = 'h';
                        draw_sprite(pizza->pizza_with_ingr, ingr_ham, 25, 13);
                    }
                    break;
                case OLIVE_LINE_X:
                    if (strstr(pizza->ingredients, "o") != NULL) {
                        if (rand() % 2) {
                            printf("Olive machine error: no such ingredient\n");
                            break;
                        }
                        pizza->ingr_already[4] = 'o';
                        draw_sprite(pizza->pizza_with_ingr, ingr_olive, 35, 36);
                    }
                    break;
                case ARTICHOKE_LINE_X:
                    if (strstr(pizza->ingredients, "a") != NULL) {
                        if (rand() % 2) {
                            printf("Artichoke machine error: no such ingredient\n");
                            break;
                        }
                        pizza->ingr_already[5] = 'a';
                        draw_sprite(pizza->pizza_with_ingr, ingr_artichoke, 7, 23);
                    }
                    break;
                default: break;
            }
        }

        wait_for_period(id);
    } // end while
}

//------------------------------------------------------------------------------------- Pizzas tasks

/**
 * Draw a pizza
 * @param index pizza index
 */
void draw_pizza(int index) {
    struct pizza pizza = pizzas[index];
    float x       = pizza.coord.x;
    float y       = pizza.coord.y;

    draw_sprite(screen, pizza.pizza_with_ingr, x, y);
}

/**
 * Task to control a pizza motion
 * @param args task args
 * @return nothing
 */
void* pizza_motion(void* arg) {
    int id = get_task_index(arg);
    float dt = TSCALE * (float) get_task_period(arg) / 1000;
    struct pizza *pizza= &pizzas[id];

    pizza->coord.x = PIZZA_H_X;
    pizza->coord.y = PIZZA_H_Y;
    set_next_activation(id);

    while (!end) {
        pizza->coord.x += speed * dt;

        if (pizza->coord.x >= XWIN - 30) {
            pizza->shipped = 1;
            nOrderedPizzas--;
            break;
        }

        wait_for_period(id);
    }
}

/**
 * Task deciding whether to put a new pizza on the assembly line.
 * @param arg task args
 * @return nothing
 */
void* new_orders(void* arg) {
    int id = get_task_index(arg);
    int new_pizza_id;
    char ingredients[INGREDIENTS_NUM] = "";
    struct pizza *pizza;

    set_next_activation(id);

    while (!end) {
        if (index_last_queue > -1) { // if there are pizzas in queue
            if (nOrderedPizzas == 0 || (pizzas[lastPizzaID].coord.x + pizza_dough->w) / 2 >= CHEESE_LINE_X) {
                // if there is no pizza in production or the last one is at cheese at lease, make it immediately
                printf("Putting new pizza on the assembly line");
                sem_wait(&sem_queue);
                    new_pizza_id = PIZZA_INDEX_BEG + nOrderedPizzas;
                    strncpy(ingredients, ordered_pizzas_queue[index_last_queue], INGREDIENTS_NUM);
                    index_last_queue--;
                sem_post(&sem_queue);

                printf(" with ID %d\n", new_pizza_id);

                pizza = &pizzas[new_pizza_id];
                strcpy(pizza->ingredients, ingredients);
                strncpy(pizza->ingr_already, "", INGREDIENTS_NUM);
                pizza->shipped = 0;
                pizza->ugly = 0;
                pizza->pizza_with_ingr = create_bitmap(pizza_dough->w, pizza_dough->h);
                // copy pizza dough
                BITMAP *buffer = create_bitmap(pizza_dough->w, pizza_dough->h);
                draw_sprite(buffer, pizza_dough, 0, 0);
                draw_sprite(pizza->pizza_with_ingr, buffer, 0, 0);

                task_create(pizza_motion, new_pizza_id, PIZZA_TASK_PER, PIZZA_TASK_PER, PIZZA_TASK_PRIORITY);
                lastPizzaID = new_pizza_id;
                nOrderedPizzas++;
            }

        }

        wait_for_period(id);
    }
}

/**
 * Decides whether a new pizza can enqueued or rejected
 * @param ingredients ingredients of new pizza
 */
void manageOrders(const char *ingredients) {
    //printf("ilq %d VS QL %d\n", index_last_queue,QUEUE_LENGTH);
    if(index_last_queue + 1 >= QUEUE_LENGTH) { // todo eliminare max_pizzas macro
        printf("Sorry, pizza cannot be ordered.\n");
        return;
    }

    // enqueue pizza
    sem_wait(&sem_queue);

    index_last_queue++;
    strcpy(ordered_pizzas_queue[index_last_queue], ingredients);

    sem_post(&sem_queue);
}

//------------------------------------------------------------------------------------- User task

/**
 * Manages user keyboard inputs
 * @param arg task args
 * @return nothing
 */
void* user_inputs(void* arg) {
    int id = get_task_index(arg);
    char scan;
    char ingredients[INGREDIENTS_NUM] = { ' ' };
    int curIngredient = 0; // number of ingredients the user has chosen

    set_next_activation(id);
    do {
        scan = get_scancode();
        switch (scan) {
            case KEY_UP:
                speed += 1;
                break;
            case KEY_DOWN:
                speed -= 1;
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
                if (curIngredient == 0) // then user has only pressed ENTER => generate random ingredients
                    generate_random_pizza(ingredients);

                printf("Ordering pizza with: %s...\n", ingredients);
                manageOrders(ingredients);

                curIngredient = 0;
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

//------------------------------------------------------------------------------------- Monitor window (quality checks)

void draw_monitor() {
    draw_sprite(screen, monitor_bmp, MONITOR_X, MONITOR_Y);
}

/**
 * Gets the first pizza on the assembly line for quality check
 * @param arg task args
 * @return nothing
 */
void* monitor(void* arg) {
    int id = get_task_index(arg);
    int i;
    struct pizza *pizza = NULL;
    int pizza_id = -1;
    monitor_bmp = create_bitmap(MONITOR_WIDTH, MONITOR_HEIGHT);


    set_next_activation(id);

    while (!end) {
        // get first pizza on the assembly line
        if (nOrderedPizzas == 0)
            continue;

        for (i = PIZZA_INDEX_BEG; i < PIZZA_INDEX_BEG + nOrderedPizzas; i++) {
            if (!pizzas[i].shipped && pizzas[i].coord.x >= TOMATO_LINE_X) {
                pizza = &pizzas[i];
                pizza_id = i;
            }
        }

        if (pizza != NULL && pizza->coord.x >= CAMERA_X) {
            // build zoomed pizza
            stretch_sprite(monitor_bmp, pizza->pizza_with_ingr, 0, 0, MONITOR_WIDTH, MONITOR_HEIGHT);

            // check if it contains all ingredients it should have
            for (i = 0; i < strlen(pizza->ingredients); i++)
                if (!str_contains(pizza->ingr_already, pizza->ingredients[i])) {
                    pizza->ugly = 1;
                    printf("Pizza ID %d doesn't contain %c (%s VS %s)\n", pizza_id, pizza->ingredients[i], pizza->ingredients, pizza->ingr_already);
                    break;
                }

            // promote or discard pizza
            if (pizza->ugly)
                textout_ex(monitor_bmp, font, "x", 0, 0, 0, 255);
            else
                textout_ex(monitor_bmp, font, "v", 0, 0, 0, 255);

        }
        wait_for_period(id);
    }
}

//------------------------------------------------------------------------------------- Support logic (global management)

void draw_lines() {
    line(screen, TOMATO_LINE_X, CB_PIECE_H_Y, TOMATO_LINE_X, CB_PIECE_H_Y + 130, 255);
    line(screen, CHEESE_LINE_X, CB_PIECE_H_Y, CHEESE_LINE_X, CB_PIECE_H_Y + 130, 255);
    line(screen, MUSHROOM_LINE_X, CB_PIECE_H_Y, MUSHROOM_LINE_X, CB_PIECE_H_Y + 130, 255);
    line(screen, HAM_LINE_X, CB_PIECE_H_Y, HAM_LINE_X, CB_PIECE_H_Y + 130, 255);
    line(screen, OLIVE_LINE_X, CB_PIECE_H_Y, OLIVE_LINE_X, CB_PIECE_H_Y + 130, 255);
    line(screen, ARTICHOKE_LINE_X, CB_PIECE_H_Y, ARTICHOKE_LINE_X, CB_PIECE_H_Y + 130, 255);
    line(screen, OVEN_X + 32, CB_PIECE_H_Y, OVEN_X + 32, CB_PIECE_H_Y + 130, 255);
    line(screen, CAMERA_LINE_X, CB_PIECE_H_Y, CAMERA_LINE_X, CB_PIECE_H_Y + 130, 255);
}


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

		draw_monitor();

		draw_lines();

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