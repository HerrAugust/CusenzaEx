//-----------------------------------------------------
// HELLO.C: SIMPLE DEMO WHERE EACH PERIODIC TASK
// DISPLAYS A CHARACTER AT EVERY PERIOD
//-----------------------------------------------------
#include <stdlib.h> // include standard lib first
#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <allegro.h>
#include "ptask.h" // a lib for periodic tasks

//-------------------------------------------------------------
// GLOBAL CONSTANTS
//-------------------------------------------------------------
#define XWIN 640 // window x resolution
#define YWIN 480 // window y resolution
#define XBASE 40 // X start for the message
#define YBASE 50 // Y level for the first task
#define YINC 30 // Y increment for the other tasks
#define BKG 0 // background color
//-------------------------------------------------------------
#define MAXT 10 // max number of tasks
#define LEN 80 // max message length
#define PER 30 // base period
#define PINC 20 // period increment
//-------------------------------------------------------------
// GLOBAL VARIABLES
//-------------------------------------------------------------
int end = 0; // end flag
char mes[MAXT][LEN+1]; // buf for MAXT mes of length LEN

void init(void)
{
	char s[LEN];
	allegro_init();
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, XWIN, YWIN, 0, 0);
	clear_to_color(screen, BKG);
	install_keyboard();
	ptask_init(SCHED_FIFO);
	sprintf(s, "Press SPACE to create a task");
	textout_ex(screen, font, s, 10, 10, 14, BKG);
}

void* hello(void* arg)
{
	int i, k = 0; // task and character index
	int x, y;
	char buf[2]; // temp buffer for 1 character string
	i = task_argument(arg);
	sprintf(mes[i], "I'M TASK %d, T = %d", i, task_period(i));
	
	while (!end) {
		x = XBASE + k*8;
		y = YBASE + i*YINC;
		sprintf(buf, "%c", mes[i][k]);
		textout_ex(screen, font, buf, x, y, 2+i, BKG);

		k = k + 1;
		if (mes[i][k] == '\0') {
			k = 0;
			textout_ex(screen, font, mes[i], XBASE, y, BKG, BKG);
		}
		wait_for_period(i);
	}
}

int main(void)
{
	int i;
	char scan;
	init();
	do {
		scan = 0;
		if (keypressed()) scan = readkey() >> 8;
		if (scan == KEY_SPACE && i < MAXT) {
			task_create(i, hello, PER+i*PINC, PER+i*PINC, 50, ACT);
			i++;
		}
	} while (scan != KEY_ESC);
	end = 1;
	for (i=0; i<=MAXT; i++) wait_for_task_end(i);
	allegro_exit();
	return 0;
