/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: SWatch2018.h
 *
 * Code generated for Simulink model 'SWatch2018'.
 *
 * Model version                  : 1.20
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Tue Nov 27 10:23:14 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_SWatch2018_h_
#define RTW_HEADER_SWatch2018_h_
#include <stddef.h>
#include <string.h>
#ifndef SWatch2018_COMMON_INCLUDES_
# define SWatch2018_COMMON_INCLUDES_
#include <stdlib.h>
#include "rtwtypes.h"
#include "zero_crossing_types.h"
#endif                                 /* SWatch2018_COMMON_INCLUDES_ */

#include "SWatch2018_types.h"
#include <stdio.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetPrevZCSigState
# define rtmGetPrevZCSigState(rtm)     ((rtm)->prevZCSigState)
#endif

#ifndef rtmSetPrevZCSigState
# define rtmSetPrevZCSigState(rtm, val) ((rtm)->prevZCSigState = (val))
#endif

#ifndef rtmGetRootDWork
# define rtmGetRootDWork(rtm)          ((rtm)->dwork)
#endif

#ifndef rtmSetRootDWork
# define rtmSetRootDWork(rtm, val)     ((rtm)->dwork = (val))
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#define SWatch2018_M_TYPE              RT_MODEL_SWatch2018_T

// @agost code
static enum State { INIT, TIMEDISPLAY, TIMESET, ALARMSET, STOPWATCH, ALARMSET_SETHOURS, ALARMSET_SETMINUTES, ALARMSET_ALARMFINALLYSET, ALARMSET_INIT,
    TIMESET_SETHOURS, TIMESET_SETMINUTES, TIMECOUNT_COUNT,
    ALARMMANAGEMENT_SILENT, ALARMMANAGEMENT_BUZZING, TIMECOUNTSTOPWATCH_BEGIN, TIMECOUNTSTOPWATCH_COUNT };
static enum Signal { SIG_TIMEMODE, SIG_TIMESETMODE, SIG_ALARMSETMODE, SIG_SWATCHMODE, SIG_PLUSBUTTON, SIG_MINUSBUTTON, SIG_TICK };

static enum Subcomponent { SC_TIMECOUNTSTOPWATCH, SC_ALARMMANAGEMENT, SC_TIMESET, SC_ALARMSET, SC_NONE }; // NONE representing the high-lv one

struct FSM {
    enum State 	curState;
    enum State 	prevState; // todo cancellare, inutile
    int  		isEntryDone; // true when entry code has been executed once
};

static enum State curHighestLvState = TIMEDISPLAY; // the current highest level Statechart state

uint8_T hours;                       /* '<S1>/SWatch2018' */
uint8_T minutes;                     /* '<S1>/SWatch2018' */
uint8_T seconds;                     /* '<S1>/SWatch2018' */
uint8_T tenths;                      /* '<S1>/SWatch2018' */
uint8_T Ahours;                      /* '<S1>/SWatch2018' */
uint8_T Aminutes;                    /* '<S1>/SWatch2018' */
uint8_T Stenths;                     /* '<S1>/SWatch2018' */
uint8_T Sseconds;                    /* '<S1>/SWatch2018' */
uint8_T Sminutes;                    /* '<S1>/SWatch2018' */
uint8_T Shours;
int AalarmIsSet;


static void tranFSM(struct FSM *fsm, enum State dest);

void initFSM(struct FSM *fsm, enum Subcomponent sc);

void dispatchFSM(struct FSM *fsm,
                 boolean_T SWatch2018_U_plusbutton, boolean_T SWatch2018_U_minusbutton,
                 boolean_T SWatch2018_U_Timemode, boolean_T SWatch2018_U_Timesetmode, boolean_T SWatch2018_U_Alarmsetmode, boolean_T SWatch2018_U_Swatchmode, uint8_T *SWatch2018_Y_hours,
                 uint8_T *SWatch2018_Y_minutes, uint8_T *SWatch2018_Y_seconds, uint8_T *SWatch2018_Y_tenths,
                 uint8_T *SWatch2018_Y_mode);

// end @agost code

#endif                                 /* RTW_HEADER_SWatch2018_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
