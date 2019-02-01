/*
 * WidgetConfig.c
 *
 *  Created on: 21/ott/2015
 *      Author: admim
 */

#include "Widget.h"
#include "WidgetConfig.h"
#include "pictures.h"
#include <stdio.h>
#include "stm32f4_discovery_lcd.h"
#include "fonts.h"

ButtonIcon buttontime = {
		icontime_on, icontime_off, TIMEMODE
};

ButtonIcon buttontimeset = {
		icontimeset_on, icontimeset_off, TIMESETMODE
};

ButtonIcon buttonalarm = {
		iconalarm_on, iconalarm_off, ALARMMODE
};

ButtonIcon buttonswatch = {
		iconswatch_on, iconswatch_off, SWATCHMODE
};

ButtonIcon buttonplus = {
		0, 0, PLUS
};

ButtonIcon buttonminus = {
		0, 0, MINUS
};

Text txt = {
		&Font32x48, White
};

Image backg = {
	ImageBuffer
};

const Widget MyWatchScr[NUMWIDGETS] = {
		{0, 0, 320, 240, BACKGROUND, (void *)&backg},
		{30, 188, 39, 43, BUTTONICON, (void *)&buttontime},
		{98, 188, 39, 43, BUTTONICON, (void *)&buttontimeset},
		{169, 188, 38, 43, BUTTONICON, (void *)&buttonalarm},
		{244, 188, 35, 43, BUTTONICON, (void *)&buttonswatch},
		{270, 30, 40, 40, BUTTONICON, (void *)&buttonplus},
		{270, 105, 40, 40, BUTTONICON, (void *)&buttonminus},
//		{26, 76, 100, 32, RECTANGLE, (void *)&rectangle}
		{29, 70, 40, 40, TEXT, (void *)&txt},
		{99, 70, 40, 40, TEXT, (void *)&txt},
		{168, 70, 40, 40, TEXT, (void *)&txt},
		{243, 70, 40, 40, TEXT, (void *)&txt},
		{80, 70, 40, 40, TEXT, (void *)&txt},
		{149, 70, 40, 40, TEXT, (void *)&txt},
};

