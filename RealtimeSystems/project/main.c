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
#include <semaphore.h>
#include "ptask.h" // a lib for periodic tasks

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

#define GUI_TASKS_PER               25 /* period of the GUI redrawing task */
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

#define COLOR_INGR_TOMATO           makecol(215,24,24) /* RGB color characterizing this ingredient (got with Gimp) */
#define COLOR_INGR_CHEESE           makecol(255,243,207)
#define COLOR_INGR_MUSHROOM         makecol(101,101,101)
#define COLOR_INGR_OLIVE            makecol(24,24,24)
#define COLOR_INGR_HAM              makecol(255,0,0)
#define COLOR_INGR_ARTICHOKE        makecol(81,235,48)

//------------------------------------------------------------- Monitor window

#define MONITOR_WIDTH               200
#define MONITOR_HEIGHT              200
#define MONITOR_X                   XWIN / 2
#define MONITOR_Y                   200

//------------------------------------------------------------- Asides

#define DEADLINE_MISS_X             XWIN - 150  /* Aside box with all deadline misses */
#define DEADLINE_MISS_Y             0

//------------------------------------------------------------- Functions

void* display(void*);
void* conveyor_belt(void*);
void  draw_conveyor_belt(int i);
void  draw_ingr_icons();
void* user_inputs(void*);
void* ingredient(void*);
void* new_orders(void* arg) ;
void* monitor(void* arg);
void* pizza_motion(void* arg) ;

//------------------------------------------------------------- Global vars

int     end = 0;                            // End of program flag

int     nCurTasks = 0, nPizzasOnCB = 0;     // Counters of currently active tasks and pizzas on the assembly line
int     lastPizzaID = PIZZA_INDEX_BEG;      // Last pizza ID
float   speed = INITIAL_SPEED;            // Pizzas and conveyor belt pieces speed
BITMAP* pizza_dough, *cb_piece, *ingr_tomato, *ingr_cheese, *ingr_mushroom, *ingr_ham, *ingr_olive, *ingr_artichoke, *monitor_bmp;
BITMAP* videocam, *oven, *tomato, *cheese, *mushroom, *ham, *olive, *artichoke; // never moving objects

char    ordered_pizzas_queue[QUEUE_LENGTH][INGREDIENTS_NUM];
int     index_last_queue = -1;
sem_t   sem_queue;

struct coordinates {
    float x;
    float y;
};

struct pizza {
    struct coordinates  coord;
    char                ingredients[INGREDIENTS_NUM];   // Ingredients of pizza
    char                ingr_already[INGREDIENTS_NUM];  // Ingredients already on the pizza. For tests
    int                 shipped;                        // 1 if pizza can be destroyed and space left to the next one
    BITMAP*             pizza_with_ingr;                // pizza dough with its ingredients
    int                 ingr_done[INGREDIENTS_NUM];     // 1 if ingredient machine has already operated on this pizza
    int                 checked;                        // 1 if camera has checked pizza quality
} pizzas[MAX_PIZZAS] = {};

struct cb_piece {
    struct coordinates coord;
    BITMAP*  bitmap;
} cb_pieces[CB_PIECES_NUM] = { 0.0, 0.0, NULL };

//------------------------------------------------------------- Utility functions

/**
 * Shows a string on screen
 * @param string the string to be shown
 * @param x x coordinate
 * @param y y coordinate
 * @param color color
 */
void show_string(const char string[80], const int x, const int y, const int color) {
	textout_ex(screen, font, string, x, y, color, BKG);
}

/**
 * True if str contains character to_check
 * @param str string to test
 * @param to_check character you look for
 * @return true if str contains char to_check
 */
int str_contains(const char *str, const char to_check) {
    char    buf[2] = "";
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
    char    list_ingr[] = "tcmhoa";
    int     i;

    strncpy(ingredients, "", INGREDIENTS_NUM);

    for (i = 0; i < INGREDIENTS_NUM; i++)
        if (rand() % 2)
            ingredients[i] = list_ingr[i];

    if(!strncmp(ingredients, "", INGREDIENTS_NUM))
        ingredients[0] = 'o'; // White pizza with only oil. I'm not hungry anymore...
}

/**
 * Wait for all tasks end (destroy tasks)
 */
void wait_for_tasks_end() {
    int     i, totalTasksNum = nCurTasks + nPizzasOnCB;

    for (i = 0; i < totalTasksNum; i++)
        destroy_task(i);
}

/**
 * Allegro initialization
 */
void init() {
    int     i;

	allegro_init();
    set_color_depth(32); // set max color depth
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, XWIN, YWIN, 0, 0);
	clear_to_color(screen, BKG);
	install_keyboard();
    srand(time(NULL));
    set_trans_blender(128, 128, 128, 128); // for draw_trans_sprite()
    sem_init(&sem_queue, 0, 1); // binary semaphore

    if (MAX_PIZZAS > NUM_TASKS) {
        perror("Error: MAX_PIZZAS > NUM_TASKS\n");
        end = 1;
    }

    for (i = 0; i < MAX_PIZZAS; i++)
        pizzas[i].shipped = 1;

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

    // create tasks to control the various parts of the program
    task_create(conveyor_belt, nCurTasks++, CB_TASK_PERIOD, CB_TASK_PERIOD, CB_TASKS_PRIORITY);
    task_create(display, nCurTasks++, GUI_TASKS_PER, GUI_TASKS_PER, GUI_TASKS_PRIORITY);
    task_create(user_inputs, nCurTasks++, USER_TASK_PER, USER_TASK_PER, USER_TASK_PRIORITY);
    for (i = 0; i < INGREDIENTS_NUM; i++) {
        nCurTasks++;
        setIngredient(nCurTasks, i);
        task_create(ingredient, nCurTasks, INGR_TASK_PER, INGR_TASK_PER, INGR_TASK_PRIORITY);
    }
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
	int     id, i, initial_piece_index = 0; // task index
	float   dt = TSCALE * (float) get_task_period(arg) / 1000;
	float   movement;

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
        has_deadline_miss(id);
		wait_for_period(id);
	}
}

/**
 * Draw conveyor belt piece
 * @param index conveyor belt piece index
 */
void draw_conveyor_belt(const int index) {
    BITMAP* b = cb_pieces[index].bitmap;
    float   x = cb_pieces[index].coord.x;
    float   y = cb_pieces[index].coord.y;

    draw_sprite(screen, b, x, y);
}

//------------------------------------------------------------------------------------- Ingredients tasks

/**
 * General function to manage ingredient machines, which put ingredients
 * @param xb where the ingredient sensor begins
 * @param xe where the ingredient sensor ends
 * @param ingr_name ingredient name (lower case)
 * @param ingr_id ingredient ID from 0-5
 * @param ingr_sprite ingredient bitmap
 * @param ingr_x ingredient x offset on pizza
 * @param ingr_y ingredient y offset on pizza
 */
void manageIngr(const int xb, const int xe, const char* ingr_name, int ingr_id, BITMAP* ingr_sprite, int ingr_x, int ingr_y) {
    int             i;
    struct pizza*   pizza;

    for (i = PIZZA_INDEX_BEG; i < PIZZA_INDEX_BEG + MAX_PIZZAS; i++) {
        pizza = &pizzas[i - PIZZA_INDEX_BEG];
        if (!pizza->shipped && pizza->coord.x >= xb && pizza->coord.x <= xe &&
            str_contains(pizza->ingredients, ingr_name[0]) && !pizza->ingr_done[ingr_id]) {

            pizza->ingr_done[ingr_id] = 1;

            // don't put ingredient - machine error (thus quality check)...
            if (rand() % 2) {
                printf("%s - pump skips it for %d ([%d])\n", ingr_name, i, i - PIZZA_INDEX_BEG);
                break;
            }

            // ...or put it
            pizza->ingr_already[ingr_id] = ingr_name[0];
            printf("%s - pizza %d ([%d]) now has %s (ingr_id %d)\n", ingr_name, i, i - PIZZA_INDEX_BEG, pizza->ingr_already, ingr_id);
            draw_sprite(pizza->pizza_with_ingr, ingr_sprite, ingr_x, ingr_y);
        }
    }
}

/**
 * Manages each ingredient machine, putting the ingredient when needed
 * @param arg task attributes
 * @return nothing
 */
void* ingredient(void* arg) {
    int     id, my_ingr; // task index

    // Init conveyor belt pieces
    id      = get_task_index(arg);
    my_ingr = getIngredient(id);
    set_next_activation(id);

    while (!end) {
        switch(my_ingr) {
            case 0:
                manageIngr(TOMATO_X, TOMATO_LINE_X, "tomato", 0, ingr_tomato, 6, 8);
                break;
            case 1:
                manageIngr(CHEESE_X, CHEESE_LINE_X, "cheese", 1, ingr_cheese, 6, 10);
                break;
            case 2:
                manageIngr(MUSHROOM_X, MUSHROOM_LINE_X, "mushroom", 2, ingr_mushroom, 25, 25);
                break;
            case 3:
                manageIngr(HAM_X, HAM_LINE_X, "ham", 3, ingr_ham, 25, 13);
                break;
            case 4:
                manageIngr(OLIVE_X, OLIVE_LINE_X, "olive", 4, ingr_olive, 36, 36);
                break;
            case 5:
                manageIngr(ARTICHOKE_X, ARTICHOKE_LINE_X, "artichoke", 5, ingr_artichoke, 7, 23);
                break;
            default: break;
        }
        has_deadline_miss(id);
        wait_for_period(id);
    } // end while
}

//------------------------------------------------------------------------------------- Pizzas tasks

/**
 * Draw a pizza
 * @param task_index pizza task index
 */
void draw_pizza(int task_index) {
    struct pizza    pizza = pizzas[task_index - PIZZA_INDEX_BEG];
    float           x = pizza.coord.x;
    float           y = pizza.coord.y;

    draw_sprite(screen, pizza.pizza_with_ingr, x, y);
}

/**
 * Task to control a pizza motion
 * @param args task args
 * @return nothing
 */
void* pizza_motion(void* arg) {
    int             id = get_task_index(arg);
    float           dt = TSCALE * (float) get_task_period(arg) / 1000;
    struct pizza*   pizza = &pizzas[id - PIZZA_INDEX_BEG];

    pizza->coord.x = PIZZA_H_X;
    pizza->coord.y = PIZZA_H_Y;
    set_next_activation(id);

    while (!end) {
        if (!pizza->shipped)
            pizza->coord.x += speed * dt;

        if (pizza->coord.x >= XWIN - 30) {
            pizza->shipped = 1;
            nPizzasOnCB--; // # pizzas on conveyor belt -= 1
            destroy_bitmap(pizza->pizza_with_ingr);
            printf("Destroyed pizza ID %d\n", id);
            destroy_task(id);
            break;
        }
        has_deadline_miss(id);
        wait_for_period(id);
    }
}

void init_pizza(struct pizza *pizza, char* ingredients) {
    int     i;

    for (i = 0; i < INGREDIENTS_NUM; i++)
        pizza->ingr_done[i] = 0;
    pizza->coord.x = 0.0; pizza->coord.y = 0.0;
    strcpy(pizza->ingredients, ingredients);
    strncpy(pizza->ingr_already, "        ", INGREDIENTS_NUM);
    pizza->shipped = 0;
    pizza->checked = 0;
    pizza->pizza_with_ingr = create_bitmap(pizza_dough->w, pizza_dough->h);
    // copy pizza dough
    BITMAP *buffer = create_bitmap(pizza_dough->w, pizza_dough->h);
    draw_sprite(buffer, pizza_dough, 0, 0);
    draw_sprite(pizza->pizza_with_ingr, buffer, 0, 0);
}

/**
 * Task deciding whether to put a new pizza on the assembly line.
 * @param arg task args
 * @return nothing
 */
void* new_orders(void* arg) {
    int             i, id = get_task_index(arg);
    int             new_pizza_id = -1;
    char            ingredients[INGREDIENTS_NUM] = "";
    struct pizza*   pizza;

    set_next_activation(id);

    while (!end) {
        if (index_last_queue > -1) { // if there are pizzas in queue
            if (nPizzasOnCB == 0 || pizzas[lastPizzaID - PIZZA_INDEX_BEG].coord.x + pizza_dough->w / 2 >= TOMATO_LINE_X) {
                // there is no pizza in production or the last one is at cheese at least, so make it immediately

                // decide new pizza ID
                for (i = PIZZA_INDEX_BEG + nPizzasOnCB; i < PIZZA_INDEX_BEG + MAX_PIZZAS; i++) {
                    if (pizzas[i - PIZZA_INDEX_BEG].shipped) {
                        new_pizza_id = i;
                        break;
                    }
                }

                if (new_pizza_id != -1) {
                    // initialize pizza
                    sem_wait(&sem_queue);
                    strncpy(ingredients, ordered_pizzas_queue[index_last_queue], INGREDIENTS_NUM);
                    index_last_queue--;
                    sem_post(&sem_queue);
                    printf("Putting new pizza on the assembly line with ID %d (pizzas[%d] - %s)\n", new_pizza_id, i - PIZZA_INDEX_BEG, ingredients);

                    pizza = &pizzas[new_pizza_id - PIZZA_INDEX_BEG];
                    init_pizza(pizza, ingredients);

                    task_create(pizza_motion, new_pizza_id, PIZZA_TASK_PER, PIZZA_TASK_PER, PIZZA_TASK_PRIORITY);
                    lastPizzaID = new_pizza_id;
                    nPizzasOnCB++;
                    new_pizza_id = -1;
                }
            }

        }

        has_deadline_miss(id);
        wait_for_period(id);
    }
}

/**
 * Decides whether a new pizza can enqueued or rejected
 * @param ingredients ingredients of new pizza
 */
void manageOrders(const char *ingredients) {
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
    int     id = get_task_index(arg);
    char    scan;
    char    ingredients[INGREDIENTS_NUM] = { ' ' };
    int     curIngredient = 0; // number of ingredients the user has chosen

    set_next_activation(id);
    do {
        scan = get_scancode();
        switch (scan) {
            case KEY_UP:
                if (speed + 1 <= MAX_SPEED) {
                    speed += 1;
                    printf("Speed is now %f\n", speed);
                } else printf("Cannot increase speed further\n");
                break;
            case KEY_DOWN:
                if (speed - 1 >= MIN_SPEED) {
                    speed -= 1;
                    printf("Speed is now %f\n", speed);
                } else printf("Cannot decrease speed further\n");
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
        has_deadline_miss(id);
        wait_for_period(id);
    } while (scan != KEY_ESC);
}

//------------------------------------------------------------------------------------- Monitor window (quality checks)

void draw_monitor() {
    draw_sprite(screen, monitor_bmp, MONITOR_X, MONITOR_Y);
}

/**
 * Returns the RGB color corresponding to an ingredient
 * @param ingr ingredient intial letter
 * @return RGB color for ingredient
 */
int get_color_for_ingr(char ingr) {
    int     col;

    switch(ingr) {
        case 't':
            col = COLOR_INGR_TOMATO;
            break;
        case 'c':
            col = COLOR_INGR_CHEESE;
            break;
        case 'm':
            col = COLOR_INGR_MUSHROOM;
            break;
        case 'h':
            col = COLOR_INGR_HAM;
            break;
        case 'o':
            col = COLOR_INGR_OLIVE;
            break;
        case 'a':
            col = COLOR_INGR_ARTICHOKE;
            break;
        default: col = 0; break;
    }
    return col;
}

/**
 * Algorithm to check quality of pizzas
 */
void check_quality(struct pizza* pizza, int pizza_id, BITMAP* image)  {
    int     x, y, c, i, searched_col, is_quality = 1;

    // look for clues of each ingredient the pizza should have got
    for (i = 0; i < strlen(pizza->ingredients); i++) {
        searched_col = get_color_for_ingr(pizza->ingredients[i]);
        for (x = 0; x < image->w; x++) {
            for (y = 0; y < image->h; y++) {
                c = getpixel(image, x, y);
                if (c == searched_col) {
                    y = image->h; // ingredient found, check next one
                    x = image->w;
                    //printf("found %c at (%d,%d)\n", pizza->ingredients[i], x,y);
                }
            }
        }

        // if ingredient not found, that's a bad quality pizza
        if (x == image->w && y == image->h) {
            printf("Monitor - %c not found on %d ([%d])\n", pizza->ingredients[i], pizza_id, pizza_id - PIZZA_INDEX_BEG);
            is_quality = 0;
            break;
        }
    }

    // if pizza has all its ingredient, its quality is ok
    if(is_quality)
        textout_ex(monitor_bmp, font, "ok", 0, 0, 0, 255);
    else
        textout_ex(monitor_bmp, font, "x", 0, 0, 0, 255);
}

/**
 * Gets the first pizza on the assembly line for quality check
 * @param arg task args
 * @return nothing
 */
void* monitor(void* arg) {
    int             i, id = get_task_index(arg), pizza_id = -1;
    struct pizza*   pizza = NULL;
    BITMAP*         photo = create_bitmap(pizza_dough->w, pizza_dough->h);

    monitor_bmp = create_bitmap(MONITOR_WIDTH, MONITOR_HEIGHT);
    clear_to_color(monitor_bmp, 255);

    set_next_activation(id);
    while (!end) {

        // if there are pizzas on the conveyor belt
        if (nPizzasOnCB != 0) {
            blit(screen, photo, CAMERA_X, PIZZA_H_Y, 0, 0, pizza_dough->w, pizza_dough->h);

            // get first pizza on the assembly line, at the camera, if there exists
            for (i = PIZZA_INDEX_BEG; i < PIZZA_INDEX_BEG + MAX_PIZZAS; i++) {
                pizza = &pizzas[i - PIZZA_INDEX_BEG];
                if (!pizza->shipped && pizza->coord.x >= CAMERA_X && pizza->coord.x <= CAMERA_LINE_X && !pizza->checked) {
                    pizza_id = i;
                    printf("Monitor - identified pizza %d at camera\n", pizza_id);
                    pizza->checked = 1;
                    break;
                }
            }

            if (pizza != NULL && !pizza->shipped) {
                // build zoomed pizza & check quality
                stretch_sprite(monitor_bmp, photo, 0, 0, MONITOR_WIDTH, MONITOR_HEIGHT);
                check_quality(pizza, pizza_id, photo);
            }
            pizza = NULL;
        }

        has_deadline_miss(id);
        wait_for_period(id);
    }
}

//------------------------------------------------------------------------------------- Support logic (global management)

/**
 * Draws lines of each ingredient
 */
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

void draw_dl_miss(int task_id) {
    static char b[40] = "";

    sprintf(b, "Task %d: %d DLM", task_id, get_deadline_miss(task_id));
    show_string(b, DEADLINE_MISS_X, DEADLINE_MISS_Y + 20 * task_id, 255);
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

/**
 * Task refreshing the GUI
 * @param arg its argument
 * @return nothing
 */
void* display(void* arg) {
	int     id, i;

	id = get_task_index(arg);

	set_next_activation(id);
	while (!end) {
		rectfill(screen, 0, 0, XWIN - 1, YWIN - 1, BKG);
		for (i = 0; i < CB_PIECES_NUM; i++) {
            draw_conveyor_belt(i);
		}

		for (i = 0; i < nCurTasks; i++)
		    draw_dl_miss(i);

        line(screen, DEADLINE_MISS_X, 220, XWIN, 220, 255);

		for (i = PIZZA_INDEX_BEG; i < PIZZA_INDEX_BEG + MAX_PIZZAS; i++) {
            if (!pizzas[i - PIZZA_INDEX_BEG].shipped) {
                draw_pizza(i);
                draw_dl_miss(i);
            }
        }

        draw_instructions();
        draw_lines();
        draw_ingr_icons();

        draw_monitor();

        has_deadline_miss(id);
        wait_for_period(id);
	}
}



int main(void) {
    init();

    while (!end);

    wait_for_tasks_end();
    allegro_exit();

    return 0;
}