/*
 * Author: Agostino Mascitti <agostino690@gmail.com>
 * Copyright (c) 2015 Intel Corporation.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * @file
 * @ingroup grove
 * @brief Morse interpreter using Internet example
 *
 * This project shows how to use Grove Touch or Button sensor to read a string
 * and than pass it to your computer through Internet.
 *
 * @hardware Sensors used:
 * Grove Touch (GroveTouch)
 * Grove Button (GroveButton)
 *
 * @ld -lupm-grove
 *
 * @date 24/ott/2015
 */

#include "mraa.hpp"
#include "client.h"

#include <iostream>
#include <time.h>
#include <grove.h>

using namespace std;


/*
 * Grove Starter Kit example
 *
 * Demonstrate the usage of Grove Touch or Button using the UPM library.
 *
 * - digital in: Grove Touch or Button sensor connected to the Grove Base Shield Port D2
 *
 * Additional linker flags: -lupm-grove
 */

#define DEBUG 1 /*Enables or disables debug mode. This could make the program slower because cout are performed.*/
#define TOUCHPIN 2 /*Defines where the Grove Touch (Button) sensor is plugged in - default is D2*/
#define DOTSINCHAR 10 /*Defines the quantity of dots and dashes there are in a single character*/

//Grove Touch or Button sensor object (Digital pin 2)
upm::GroveButton *touch = new upm::GroveButton(TOUCHPIN);

/*
 * This function "understands" if the click on Grove Touch is a long or a short one.
 * This is done by mesuring the time Touch is clicked.
 * If more than (default) 2.0 seconds, it is a long click (so true); otherwise it is a short one (so false).
 */
bool isLongClick() {
	clock_t beg,end;

	beg = clock();
	//while value of touch is not 0, ie clicked
	while(touch->value());
	end = clock();

	double duration = (end-beg) / (double) CLOCKS_PER_SEC;
#ifdef DEBUG
	cout << "click duration: " << duration << " sec. => " << (duration >= 2.0 ? "LONG." : "SHORT.") << endl;
#endif

	if(duration >= 2.0)
		return true;
	else
		return false;
}

/*
 * Returns how much time Touch is not clicked, in seconds.
 */
double getSilenceDuration() {
	clock_t beg,end;

	beg = clock();
	while(!touch->value()); //while value of touch is 0, ie not clicked
	end = clock();

	double durationSeconds = (end-beg) / (double) CLOCKS_PER_SEC;
#ifdef DEBUG
	cout << "silence duration: " << durationSeconds << endl;
#endif
	return durationSeconds;
}

/*
 * Decodes the sequence of clicks on Grove Touch, returning the corrisponding character (alphabet or digit).
 */
char decode(bool* ch, int len) {
	char c = '?';

	if(!ch[0] && ch[1] && len == 2)
		c = 'A';
	else if(ch[0] && !ch[1] && !ch[2] && !ch[3] && len == 4)
		c = 'B';
	else if(ch[0] && !ch[1] && ch[2] && !ch[3] && len == 4)
		c = 'C';
	else if(ch[0] && !ch[1] && !ch[2] && len == 3)
		c = 'D';
	else if(!ch[0] && len == 1)
		c = 'E';
	else if(!ch[0] && !ch[1] && ch[2] && !ch[3] && len == 4)
		c = 'F';
	else if(ch[0] && ch[1] && !ch[2] && len == 3)
		c = 'G';
	else if(!ch[0] && !ch[1] && !ch[2] && !ch[3] && len == 4)
		c = 'H';
	else if(!ch[0] && !ch[1] && len == 2)
		c = 'I';
	else if(!ch[0] && ch[1] && ch[2] && ch[3] && len == 4)
		c = 'J';
	else if(ch[0] && !ch[1] && ch[2] && len == 3)
		c = 'K';
	else if(!ch[0] && ch[1] && !ch[2] && !ch[3] && len == 4)
		c = 'L';
	else if(ch[0] && ch[1] && len == 2)
		c = 'M';
	else if(ch[0] && !ch[1] && len == 2)
		c = 'N';
	else if(ch[0] && ch[1] && ch[2] && len == 3)
		c = 'O';
	else if(!ch[0] && ch[1] && ch[2] && !ch[3] && len == 4)
		c = 'P';
	else if(ch[0] && ch[1] && !ch[2] && ch[3] && len == 4)
		c = 'Q';
	else if(!ch[0] && ch[1] && !ch[2] && len == 3)
		c = 'R';
	else if(!ch[0] && !ch[1] && !ch[2] && len == 3)
		c = 'S';
	else if(ch[0] && len == 1)
		c = 'T';
	else if(!ch[0] && !ch[1] && ch[2] && len == 3)
		c = 'U';
	else if(!ch[0] && !ch[1] && !ch[2] && ch[3] && len == 4)
		c = 'V';
	else if(!ch[0] && ch[1] && ch[2] && len == 3)
		c = 'W';
	else if(ch[0] && !ch[1] && !ch[2] && ch[3] && len == 4)
		c = 'X';
	else if(ch[0] && !ch[1] && ch[2] && ch[3] && len == 4)
		c = 'Y';
	else if(ch[0] && ch[1] && !ch[2] && !ch[3] && len == 4)
		c = 'Z';
	else if(!ch[0] && ch[1] && ch[2] && ch[3] && ch[4] && len == 5)
		c = '1';
	else if(!ch[0] && !ch[1] && ch[2] && ch[3] && ch[4] && len == 5)
		c = '2';
	else if(!ch[0] && !ch[1] && !ch[2] && ch[3] && ch[4] && len == 5)
		c = '3';
	else if(!ch[0] && !ch[1] && !ch[2] && !ch[3] && ch[4] && len == 5)
		c = '4';
	else if(!ch[0] && !ch[1] && !ch[2] && !ch[3] && !ch[4] && len == 5)
		c = '5';
	else if(ch[0] && !ch[1] && !ch[2] && !ch[3] && !ch[4] && len == 5)
		c = '6';
	else if(ch[0] && ch[1] && !ch[2] && !ch[3] && !ch[4] && len == 5)
			c = '7';
	else if(ch[0] && ch[1] && ch[2] && !ch[3] && !ch[4] && len == 5)
			c = '8';
	else if(ch[0] && ch[1] && ch[2] && ch[3] && !ch[4] && len == 5)
			c = '9';
	else if(ch[0] && ch[1] && ch[2] && ch[3] && ch[4] && len == 5)
			c = '0';

#ifdef DEBUG
	for(int i = 0; i < 10; i++)
		cout << "\tch.at " << i << ": " << ch[i] << endl;
	cout << "Decode: " << c << "; len = " << len << endl;
#endif

	return c;
}

/*
 * Waits for clicks on Grove Touch and manages other functions.
 * If pause between a click and the following is minor than 1 sec => do nothing;
 * If pause between a click and the following is 1 <= pause time < 2 sec => decode this sequence of clicks and add it to the string;
 * If pause between a click and the following is 2 <= pause time < 3 sec => add a space to the string;
 * Otherwise end the string and send it to the computer.
 */
int main()
{
	double duration;
	string message = "";
	bool clicksHistory[DOTSINCHAR] = {false};
	int currentClick = 0;
	if(touch == NULL) {
		cerr << "touch is NULL" << endl;
		return mraa::ERROR_NO_RESOURCES;
	}

	//check that we are running on Galileo or Edison
	mraa_platform_t platform = mraa_get_platform_type();
	if ((platform != MRAA_INTEL_GALILEO_GEN1) &&
			(platform != MRAA_INTEL_GALILEO_GEN2) &&
			(platform != MRAA_INTEL_EDISON_FAB_C)) {
		std::cerr << "Unsupported platform, exiting" << std::endl;
		return MRAA_ERROR_INVALID_PLATFORM;
	}


	//wait for the first click
	while(touch->value() == 0);

	//snippet to manage long and short clicks on Grove Touch or Button sensor
	for(;;) {
		if(touch->value()) { //click event
			clicksHistory[currentClick++] = isLongClick();
			if(currentClick > 10) {
				cerr << "Error: you inserted a sequence of dot and dahs longer than the possible." << endl;
				return 0;
			}
		}
		else { //silence period
#ifdef DEBUG
			cout << "Silence zone entered" << endl;
#endif
			duration = getSilenceDuration();

			//If duration is minor than 1.0, ignore it (user is inserting a letter)
			if(duration < 1.0)
			{
				continue;
			}
			else
			{
				switch( (int) duration) {
					//case 2 seconds of silence
					case 2: //SPACE: end current char and add space
#ifdef DEBUG
						cout << "SPACE" << endl;
#endif
					//case 1 second of silence
					case 1: //ECHAR: end of current char
#ifdef DEBUG
						cout << "ECHAR" << endl;
#endif
						message += decode(clicksHistory, currentClick);
#ifdef DEBUG
						for(int i = 0; i < DOTSINCHAR; i++)
							clicksHistory[i] = false;
#endif
						currentClick = 0;
						if( (int) duration == 1) //if ECHAR
							break;
						//otherwise add a space, duration == 2
						message += ' ';
						break;

					//more than 2 seconds of silence
					default: //EMSG: end current message
						message += decode(clicksHistory, currentClick);
						cout << "Message finished: " << message << "." << endl;

						//Send the message that you inserted to your computer. See client.cpp
						if(!sendToComputer(message.c_str()))
							cerr << "Errore: impossibile contattare il computer." << endl;

#ifdef DEBUG
						for(int i = 0; i < 10;i++)
							cout << i << ": " << clicksHistory[i] << endl;
#endif
						delete touch;
						return mraa::SUCCESS;
				}
			}
		}
	}

	delete touch;
	return mraa::ERROR_UNSPECIFIED; //Unexpected error
}
