/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2013  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation,
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

#include "ee.h"
#include "ee_irq.h"
#include <stdio.h>
#include "stm32f4xx_conf.h"
#include "stm32f4_discovery.h"
#include "stm32f4_discovery_lcd.h"
#include "stm32f4xx.h"

#include "STMPE811QTR.h"
#include "pictures.h"
#include "Widget.h"
#include "WidgetConfig.h"
#include "Touch.h"
#include "Event.h"
#include "SWatch2018.h"
#include "lcd_add.h"
#include "fonts.h"
#include "debug.h"

//boolean_T tick, button[4], buzzer;
uint8_T Swatch2018_Y_hours=0, Swatch2018_Y_minutes=0, Swatch2018_Y_seconds=0, Swatch2018_Y_tenths=0, Swatch2018_Y_mode;

//RT_MODEL_SWatch2018_T *Swatch2018_M;

boolean_T Swatch2018_U_plusbutton, Swatch2018_U_minusbutton, Swatch2018_U_timemode,
	Swatch2018_U_timesetmode, Swatch2018_U_alarmmode, Swatch2018_U_swatchmode;

struct FSM fsm, fsmTimeCountStopwatch, fsmAlarmManagement, fsmAlarmSet, fsmTimeSet;

char msg[96];

//---------------------------------------------------------- UART

void printf2UART(char* msg) {
	EE_INT32 i;
	int len = strlen(msg);

	for (i = 0; i < len; i++) {
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART */
		USART_SendData(EVAL_COM1, (uint8_t) msg[i]);
	/* Loop until the end of transmission */
		while (USART_GetFlagStatus(EVAL_COM1, USART_FLAG_TC) == RESET);
	}

	return len;
}


USART_InitTypeDef USART_InitStructure;

/**
 * Init UART on COM1 of board
 */
void initUART() {
	USART_InitStructure.USART_BaudRate = 115200; // baud
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; // 8 bits
	USART_InitStructure.USART_StopBits = USART_StopBits_1; // 1 stop bit
	USART_InitStructure.USART_Parity = USART_Parity_No; // no parity
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // HW control flow disabled
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; // receive & tx enabled

	STM_EVAL_COMInit(COM1, &USART_InitStructure);
}

//---------------------------------------------------------- Tasks

/*
 * SysTick ISR2
 */
ISR2(systick_handler)
{
	/* count the interrupts, waking up expired alarms */
	CounterTick(myCounter);
}

/*
 * TASK LCD
 */
TASK(TaskLCD)
{
	unsigned int px, py;
	TPoint p;
	if (GetTouch_SC_Async(&px, &py)) {
		p.x = px;
		p.y = py;
		OnTouch(MyWatchScr, &p);
	}
}

void setTimeString(char *watchstr, uint8_T hours, uint8_T minutes, uint8_T seconds, uint8_T tenths, uint8_T mode)
{
	sprintf(watchstr, "%2d:%2d:%2d", hours, minutes, seconds);
}

/*
 * TASK Clock
 */
unsigned char IsUpdateTime()
{
	unsigned char res;
	static unsigned char oh=0, om=0, os=0;
	if (Swatch2018_Y_hours!=oh || Swatch2018_Y_minutes!=om || Swatch2018_Y_seconds!= os)
		res = 1;
	else
		res = 0;
	oh = Swatch2018_Y_hours;
	om = Swatch2018_Y_minutes;
	os = Swatch2018_Y_seconds;
	return res;
}

void UpdateTime()
{
	unsigned char watchstr[20];
	setTimeString(watchstr, Swatch2018_Y_hours, Swatch2018_Y_minutes, Swatch2018_Y_seconds, Swatch2018_Y_tenths, Swatch2018_Y_mode);

	LCD_SetTextColor(Black);
	LCD_SetBackColor(Black);
	LCD_DrawFullRect(30, 76, 160, 32);

/*	WPrint(&MyWatchScr[TIMESTR], watchstr); */
}

void UpdateMode(unsigned char om, unsigned char m)
{
	switch(om) {
	case 2:
		DrawOff(&MyWatchScr[BALARM]);
		break;
	case 1:
		DrawOff(&MyWatchScr[BTIMESET]);
		break;
	case 0:
		DrawOff(&MyWatchScr[BTIME]);
		break;
	case 3:
		DrawOff(&MyWatchScr[BSWATCH]);
		break;
	}
	switch(m) {
	case 2:
		DrawOn(&MyWatchScr[BALARM]);
		break;
	case 1:
		DrawOn(&MyWatchScr[BTIMESET]);
		break;
	case 0:
		DrawOn(&MyWatchScr[BTIME]);
		break;
	case 3:
		DrawOn(&MyWatchScr[BSWATCH]);
		break;
	}
}

void strencode2digit(char *str, int digit)
{
	str[2]=0;
	str[0]=digit/10+'0';
	str[1]=digit%10+'0';
}

TASK(TaskClock)
{
	unsigned char i;
	static int oldmode=8;
	static unsigned char oh=99, om=99, os=99;
	char tstr[3];

	if IsEvent (TIMEMODE) Swatch2018_U_timemode=1; else Swatch2018_U_timemode=0;
	if IsEvent (TIMESETMODE) Swatch2018_U_timesetmode=1; else Swatch2018_U_timesetmode=0;
	if IsEvent (ALARMMODE) Swatch2018_U_alarmmode=1; else Swatch2018_U_alarmmode=0;
	if IsEvent (SWATCHMODE) Swatch2018_U_swatchmode=1; else Swatch2018_U_swatchmode=0;
	if IsEvent (PLUS) Swatch2018_U_plusbutton=1; else Swatch2018_U_plusbutton=0;
	if IsEvent (MINUS) Swatch2018_U_minusbutton=1; else Swatch2018_U_minusbutton=0;

	// TODO CORREGGERE: TIMEDISPLAY->TIMESET_SETHOURS->TIMESET_SETMINUTES->TIMEDISPLAY->TIMESET NON TORNA IN TIMESET_SETHOURS
	dispatchFSM(&fsmTimeSet, Swatch2018_U_plusbutton, Swatch2018_U_minusbutton, Swatch2018_U_timemode,\
					Swatch2018_U_timesetmode, Swatch2018_U_alarmmode, Swatch2018_U_swatchmode, &Swatch2018_Y_hours,\
					&Swatch2018_Y_minutes, &Swatch2018_Y_seconds, &Swatch2018_Y_tenths, &Swatch2018_Y_mode);
	DEBUG("%s (fsmTimeSet) esce in state %s\r\n", fsmTimeSet.name, fsmTimeSet.curStateName);
	dispatchFSM(&fsm, Swatch2018_U_plusbutton, Swatch2018_U_minusbutton, Swatch2018_U_timemode,
					Swatch2018_U_timesetmode, Swatch2018_U_alarmmode, Swatch2018_U_swatchmode, &Swatch2018_Y_hours,
					&Swatch2018_Y_minutes, &Swatch2018_Y_seconds, &Swatch2018_Y_tenths, &Swatch2018_Y_mode);
	DEBUG("%s (fsm) esce in stato %s\r\n", fsm.name, fsm.curStateName);
	dispatchFSM(&fsmTimeCountStopwatch, Swatch2018_U_plusbutton, Swatch2018_U_minusbutton, Swatch2018_U_timemode,
					Swatch2018_U_timesetmode, Swatch2018_U_alarmmode, Swatch2018_U_swatchmode, &Swatch2018_Y_hours,
					&Swatch2018_Y_minutes, &Swatch2018_Y_seconds, &Swatch2018_Y_tenths, &Swatch2018_Y_mode);
	DEBUG("fsmTimeCountStopwatch esce in stato %s\r\n", fsmTimeCountStopwatch.curStateName);

	/*
	dispatchFSM(&fsmAlarmSet, Swatch2018_U_plusbutton, Swatch2018_U_minusbutton, Swatch2018_U_timemode,\
						Swatch2018_U_timesetmode, Swatch2018_U_alarmmode, Swatch2018_U_swatchmode, &Swatch2018_Y_hours,\
						&Swatch2018_Y_minutes, &Swatch2018_Y_seconds, &Swatch2018_Y_tenths, &Swatch2018_Y_mode);
	DEBUG("fsmAlarmSet esce in state %s\r\n", fsmAlarmSet.curStateName);
	dispatchFSM(&fsmAlarmManagement, Swatch2018_U_plusbutton, Swatch2018_U_minusbutton, Swatch2018_U_timemode,\
						Swatch2018_U_timesetmode, Swatch2018_U_alarmmode, Swatch2018_U_swatchmode, &Swatch2018_Y_hours,\
						&Swatch2018_Y_minutes, &Swatch2018_Y_seconds, &Swatch2018_Y_tenths, &Swatch2018_Y_mode);
	DEBUG("fsmAlarmManagement esce in state %s\r\n", fsmAlarmManagement.curStateName);
	DEBUG( "uscito %u %u %u\r\n", Swatch2018_Y_hours, Swatch2018_Y_minutes, Swatch2018_Y_seconds);
	/*SWatch2018_step( SWatch2018_M, plusbutton, minusbutton, Timemode, Timesetmode,
	//	Alarmsetmode, Swatchmode, &hours, &minutes, &seconds, &tenths, &mode);
	/* seconds = seconds+1; */

	ClearEvents();
	//for (i=0;i<4;i++) button[i]=0;

	if (Swatch2018_Y_hours!=oh) {
		//DEBUG("uscito1 %u\r\n", Swatch2018_Y_hours);
		strencode2digit(tstr, Swatch2018_Y_hours);
		LCD_SetTextColor(Black);
		LCD_SetBackColor(Black);
		LCD_DrawFullRect(29, 70, 62, 48);
		WPrint(&MyWatchScr[HRSSTR], tstr);
		oh=Swatch2018_Y_hours;
	}
	if (Swatch2018_Y_minutes!=om) {
		strencode2digit(tstr, Swatch2018_Y_minutes);
		LCD_SetTextColor(Black);
		LCD_SetBackColor(Black);
		LCD_DrawFullRect(99, 70, 62, 48);
		WPrint(&MyWatchScr[MINSTR], tstr);
		om=Swatch2018_Y_minutes;
	}

	if (Swatch2018_Y_seconds!= os) {
		strencode2digit(tstr, Swatch2018_Y_seconds);
		LCD_SetTextColor(Black);
		LCD_SetBackColor(Black);
		LCD_DrawFullRect(168, 70, 62, 48);
		WPrint(&MyWatchScr[SECSTR], tstr);
		os=Swatch2018_Y_seconds;
	}

	if (Swatch2018_Y_mode != oldmode) {
		UpdateMode(oldmode, Swatch2018_Y_mode);
		oldmode = Swatch2018_Y_mode;
	}

}

/*
 * MAIN TASK
 */
int main(void)
{
	//GPIO_InitTypeDef GPIO_InitStructure;

	SystemInit();
  /*Initializes Erika related stuffs*/
	EE_system_init();

  /* init state machine */
  	initFSM(&fsm, SC_NONE, "Interface");
  	initFSM(&fsmTimeCountStopwatch, SC_TIMECOUNTSTOPWATCH, "TimeCountSW");
  	initFSM(&fsmAlarmManagement, SC_ALARMMANAGEMENT, "AlarmManag");
  	initFSM(&fsmAlarmSet, SC_ALARMSET, "AlarmSet");
  	initFSM(&fsmTimeSet, SC_TIMESET, "TimeSet");

  	initUART();
  	printf2UART("---------------------------------\r\n");

	/*Initialize systick */
	EE_systick_set_period(MILLISECONDS_TO_TICKS(1, SystemCoreClock));
	EE_systick_enable_int();
	EE_systick_start();

	/* Initializes LCD and touchscreen */
	IOE_Config();
	/* Initialize the LCD */
	STM32f4_Discovery_LCD_Init();
	LCD_LOG_Init();

//	LCD_Clear(White);

	/* Set the LCD Text size */
	//LCD_SetFont(&Font8x12);
//	Lcd_Touch_Calibration();
	InitTouch(-0.102, 0.0656, -335, 10);
	//InitTouch(-0.09, 0.0656, -353, 10);

	/* Draw the background */
	DrawInit(MyWatchScr);
	LCD_SetTextColor(Black);
	LCD_SetBackColor(Black);
	LCD_DrawFullRect(28, 62, 200, 56);
	WPrint(&MyWatchScr[SEP1STR], ":");
	WPrint(&MyWatchScr[SEP2STR], ":");

	/* Program cyclic alarms which will fire after an initial offset,
	 * and after that periodically
	 * */
	SetRelAlarm(AlarmTaskLCD, 10, 50);
	SetRelAlarm(AlarmTaskClock, 10, 100);

  /* Forever loop: background activities (if any) should go here */
	for (;;) { 
	}

}


