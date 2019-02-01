/**
  * CUnit test. To run test:
  * gcc tests.c SWatch2018.c  -o tests -Wall -I/home/agost/di_natale/code_c/CUnit-2.0-1/CUnit/Headers/ -lcunit && ./tests
  */


#include <CUnit/Automated.h>
#include <CUnit/CUnit.h> 
#include "SWatch2018.h"
#include <stdio.h>



uint8_T Swatch2018_Y_hours=0, Swatch2018_Y_minutes=0, Swatch2018_Y_seconds=0, Swatch2018_Y_tenths=0, Swatch2018_Y_mode;
boolean_T Swatch2018_U_plusbutton, Swatch2018_U_minusbutton, Swatch2018_U_timemode, Swatch2018_U_timesetmode, Swatch2018_U_alarmmode, Swatch2018_U_swatchmode;
struct FSM fsm, fsmTimeCountStopwatch, fsmAlarmManagement, fsmAlarmSet, fsmTimeSet;



/**
  * Test if timesetmode works well, setting appropriately minutes
  */
void test_minutes() {
	int plusbutton = 1, timesetmode = 1;
	int i = 0;

	// goto timeset minutes
	dispatchFSM(&fsm, Swatch2018_U_plusbutton, Swatch2018_U_minusbutton, Swatch2018_U_timemode,
			timesetmode, Swatch2018_U_alarmmode, Swatch2018_U_swatchmode, &Swatch2018_Y_hours,
			&Swatch2018_Y_minutes, &Swatch2018_Y_seconds, &Swatch2018_Y_tenths, &Swatch2018_Y_mode);
	dispatchFSM(&fsmTimeSet, Swatch2018_U_plusbutton, Swatch2018_U_minusbutton, Swatch2018_U_timemode,
			timesetmode, Swatch2018_U_alarmmode, Swatch2018_U_swatchmode, &Swatch2018_Y_hours,
			&Swatch2018_Y_minutes, &Swatch2018_Y_seconds, &Swatch2018_Y_tenths, &Swatch2018_Y_mode);
	dispatchFSM(&fsmTimeSet, Swatch2018_U_plusbutton, Swatch2018_U_minusbutton, Swatch2018_U_timemode,
			timesetmode, Swatch2018_U_alarmmode, Swatch2018_U_swatchmode, &Swatch2018_Y_hours,
			&Swatch2018_Y_minutes, &Swatch2018_Y_seconds, &Swatch2018_Y_tenths, &Swatch2018_Y_mode);

	for(i = 0; i < 57; i++) {
		dispatchFSM(&fsmTimeSet, plusbutton, Swatch2018_U_minusbutton, Swatch2018_U_timemode,
			Swatch2018_U_timesetmode, Swatch2018_U_alarmmode, Swatch2018_U_swatchmode, &Swatch2018_Y_hours,
			&Swatch2018_Y_minutes, &Swatch2018_Y_seconds, &Swatch2018_Y_tenths, &Swatch2018_Y_mode);
	}
	
	printf("test_minutes(). Minutes are now %d\n", Swatch2018_Y_minutes);

	// switch back to timemode and see the minutes
	dispatchFSM(&fsmTimeSet, Swatch2018_U_plusbutton, Swatch2018_U_minusbutton, 1,
			Swatch2018_U_timesetmode, Swatch2018_U_alarmmode, Swatch2018_U_swatchmode, &Swatch2018_Y_hours,
			&Swatch2018_Y_minutes, &Swatch2018_Y_seconds, &Swatch2018_Y_tenths, &Swatch2018_Y_mode);

	printf("test_minutes(). Hours %d (VS 0); Minutes %d (VS %d)\n", Swatch2018_Y_hours, Swatch2018_Y_minutes, i - 1);
	CU_ASSERT(Swatch2018_Y_minutes == 59);
	CU_ASSERT(Swatch2018_Y_hours == 0);
}

/**
  * Test if, when minutes get 60, you get 1 hour
  */
void test_hours() {
	int i = 0;
	printf("------------------------- test_hours()\n");

	// goto timemode
	dispatchFSM(&fsm, Swatch2018_U_plusbutton, Swatch2018_U_minusbutton, 1,
			Swatch2018_U_timesetmode, Swatch2018_U_alarmmode, Swatch2018_U_swatchmode, &Swatch2018_Y_hours,
			&Swatch2018_Y_minutes, &Swatch2018_Y_seconds, &Swatch2018_Y_tenths, &Swatch2018_Y_mode);

	printf("h %d m %d s %d\n", Swatch2018_Y_hours, Swatch2018_Y_minutes, Swatch2018_Y_seconds);

	// get at least 60 minutes
	for(i = 0; i < 60*60*10; i++) {
		dispatchFSM(&fsm, Swatch2018_U_plusbutton, Swatch2018_U_minusbutton, 1,
			Swatch2018_U_timesetmode, Swatch2018_U_alarmmode, Swatch2018_U_swatchmode, &Swatch2018_Y_hours,
			&Swatch2018_Y_minutes, &Swatch2018_Y_seconds, &Swatch2018_Y_tenths, &Swatch2018_Y_mode);
	}
	
	printf("test_hours(). Minutes are now %d\n", Swatch2018_Y_minutes);

	// switch back to timemode and see the minutes
	dispatchFSM(&fsm, 1, Swatch2018_U_minusbutton, Swatch2018_U_timemode,
			Swatch2018_U_timesetmode, Swatch2018_U_alarmmode, Swatch2018_U_swatchmode, &Swatch2018_Y_hours,
			&Swatch2018_Y_minutes, &Swatch2018_Y_seconds, &Swatch2018_Y_tenths, &Swatch2018_Y_mode);

	printf("test_hours(). Hours %d (VS 1); Minutes %d (VS 0 <= x < 60)\n", Swatch2018_Y_hours, Swatch2018_Y_minutes);
	CU_ASSERT(Swatch2018_Y_hours == 1);
	CU_ASSERT(Swatch2018_Y_minutes >= 0 && Swatch2018_Y_minutes < 60);
}



int init_suite_SWatch2018() {
	printf("init suite\n");
	initFSM(&fsm, SC_NONE);
  	initFSM(&fsmTimeCountStopwatch, SC_TIMECOUNTSTOPWATCH);
  	initFSM(&fsmAlarmManagement, SC_ALARMMANAGEMENT);
  	initFSM(&fsmAlarmSet, SC_ALARMSET);
  	initFSM(&fsmTimeSet, SC_TIMESET);

  	// since fsm and fsmalarmset have a fake begin state INIT:
  	dispatchFSM(&fsm, Swatch2018_U_plusbutton, Swatch2018_U_minusbutton, Swatch2018_U_timemode,
			Swatch2018_U_timesetmode, Swatch2018_U_alarmmode, Swatch2018_U_swatchmode, &Swatch2018_Y_hours,
			&Swatch2018_Y_minutes, &Swatch2018_Y_seconds, &Swatch2018_Y_tenths, &Swatch2018_Y_mode);
  	dispatchFSM(&fsmAlarmSet, Swatch2018_U_plusbutton, Swatch2018_U_minusbutton, Swatch2018_U_timemode,
			Swatch2018_U_timesetmode, Swatch2018_U_alarmmode, Swatch2018_U_swatchmode, &Swatch2018_Y_hours,
			&Swatch2018_Y_minutes, &Swatch2018_Y_seconds, &Swatch2018_Y_tenths, &Swatch2018_Y_mode);

	return 0;
}

int main() {
	// create a suite
	CU_pSuite pSuite = NULL;
	/* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry())
	  return CU_get_error();

	/* add a suite to the registry */
	pSuite = CU_add_suite("Suite_1", init_suite_SWatch2018, NULL);
	if (NULL == pSuite) {
	  CU_cleanup_registry();
	  return CU_get_error();
	}

	/* add the tests to the suite */
	if (
	   (NULL == CU_add_test(pSuite, "test of test_minutes()", test_minutes)) 
	   )
	{
	  CU_cleanup_registry();
	  return CU_get_error();
	}

	// ----------------------------------- other suite
	pSuite = CU_add_suite("Suite_2", init_suite_SWatch2018, NULL);
	if (NULL == pSuite) {
	  CU_cleanup_registry();
	  return CU_get_error();
	}

	/* add the tests to the suite */
	if (
	   (NULL == CU_add_test(pSuite, "test of test_hours()", test_hours)) 
	   )
	{
	  CU_cleanup_registry();
	  return CU_get_error();
	}

	/* Run all tests using the CUnit Basic interface */
	init_suite_SWatch2018();

	CU_automated_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}

