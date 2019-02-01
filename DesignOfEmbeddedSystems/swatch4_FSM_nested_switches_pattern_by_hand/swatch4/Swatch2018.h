/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Swatch2018.h
 *
 * Code generated for Simulink model 'Swatch2018'.
 *
 * Model version                  : 1.88
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Thu Dec 13 14:42:05 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Swatch2018_h_
#define RTW_HEADER_Swatch2018_h_
#include <stddef.h>
#include <string.h>
#ifndef Swatch2018_COMMON_INCLUDES_
# define Swatch2018_COMMON_INCLUDES_
#include <stdlib.h>
#include "rtwtypes.h"
#include "zero_crossing_types.h"
#endif                                 /* Swatch2018_COMMON_INCLUDES_ */

#include "Swatch2018_types.h"

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

#define Swatch2018_M_TYPE              RT_MODEL_Swatch2018_T

/* Block states (default storage) for system '<Root>' */
typedef struct {
  uint8_T Output_DSTATE;               /* '<S2>/Output' */
  uint8_T is_TimeCountStopwatch;       /* '<S1>/SWatch2018' */
  uint8_T is_Interface;                /* '<S1>/SWatch2018' */
  uint8_T is_TimeSet;                  /* '<S1>/SWatch2018' */
  uint8_T is_AlarmSet;                 /* '<S1>/SWatch2018' */
  uint8_T is_AlarmManagement;          /* '<S1>/SWatch2018' */
  uint8_T Ahours;                      /* '<S1>/SWatch2018' */
  uint8_T Aminutes;                    /* '<S1>/SWatch2018' */
  uint8_T hours;                       /* '<S1>/SWatch2018' */
  uint8_T minutes;                     /* '<S1>/SWatch2018' */
  uint8_T seconds;                     /* '<S1>/SWatch2018' */
  uint8_T tenths;                      /* '<S1>/SWatch2018' */
  uint8_T Shours;                      /* '<S1>/SWatch2018' */
  uint8_T Sminutes;                    /* '<S1>/SWatch2018' */
  uint8_T Sseconds;                    /* '<S1>/SWatch2018' */
  uint8_T Stenths;                     /* '<S1>/SWatch2018' */
  uint8_T AalarmIsSet;                 /* '<S1>/SWatch2018' */
} DW_Swatch2018_T;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState SWatch2018_Trig_ZCE[7];   /* '<S1>/SWatch2018' */
} PrevZCX_Swatch2018_T;

/* Real-time Model Data Structure */
struct tag_RTM_Swatch2018_T {
  const char_T *errorStatus;
  PrevZCX_Swatch2018_T *prevZCSigState;
  DW_Swatch2018_T *dwork;
};

/* External data declarations for dependent source files */
extern const char *RT_MEMORY_ALLOCATION_ERROR;

/* Model entry point functions */
extern RT_MODEL_Swatch2018_T *Swatch2018(boolean_T *Swatch2018_U_plusbutton,
  boolean_T *Swatch2018_U_minusbutton, boolean_T *Swatch2018_U_timemode,
  boolean_T *Swatch2018_U_timesetmode, boolean_T *Swatch2018_U_alarmmode,
  boolean_T *Swatch2018_U_swatchmode, uint8_T *Swatch2018_Y_hours, uint8_T
  *Swatch2018_Y_minutes, uint8_T *Swatch2018_Y_seconds, uint8_T
  *Swatch2018_Y_tenths, uint8_T *Swatch2018_Y_mode);
extern void Swatch2018_initialize(RT_MODEL_Swatch2018_T *const Swatch2018_M,
  boolean_T *Swatch2018_U_plusbutton, boolean_T *Swatch2018_U_minusbutton,
  boolean_T *Swatch2018_U_timemode, boolean_T *Swatch2018_U_timesetmode,
  boolean_T *Swatch2018_U_alarmmode, boolean_T *Swatch2018_U_swatchmode, uint8_T
  *Swatch2018_Y_hours, uint8_T *Swatch2018_Y_minutes, uint8_T
  *Swatch2018_Y_seconds, uint8_T *Swatch2018_Y_tenths, uint8_T
  *Swatch2018_Y_mode);
extern void Swatch2018_step(RT_MODEL_Swatch2018_T *const Swatch2018_M, boolean_T
  Swatch2018_U_plusbutton, boolean_T Swatch2018_U_minusbutton, boolean_T
  Swatch2018_U_timemode, boolean_T Swatch2018_U_timesetmode, boolean_T
  Swatch2018_U_alarmmode, boolean_T Swatch2018_U_swatchmode, uint8_T
  *Swatch2018_Y_hours, uint8_T *Swatch2018_Y_minutes, uint8_T
  *Swatch2018_Y_seconds, uint8_T *Swatch2018_Y_tenths, uint8_T
  *Swatch2018_Y_mode);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S2>/Data Type Propagation' : Unused code path elimination
 * Block '<S4>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S5>/FixPt Data Type Duplicate1' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('stopwatch2018/Swatch2018')    - opens subsystem stopwatch2018/Swatch2018
 * hilite_system('stopwatch2018/Swatch2018/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'stopwatch2018'
 * '<S1>'   : 'stopwatch2018/Swatch2018'
 * '<S2>'   : 'stopwatch2018/Swatch2018/Counter Limited'
 * '<S3>'   : 'stopwatch2018/Swatch2018/SWatch2018'
 * '<S4>'   : 'stopwatch2018/Swatch2018/Counter Limited/Increment Real World'
 * '<S5>'   : 'stopwatch2018/Swatch2018/Counter Limited/Wrap To Zero'
 */
#endif                                 /* RTW_HEADER_Swatch2018_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
