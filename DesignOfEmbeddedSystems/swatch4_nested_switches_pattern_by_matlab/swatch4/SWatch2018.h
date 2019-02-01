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

/* Block states (default storage) for system '<Root>' */
typedef struct {
  uint8_T Output_DSTATE;               /* '<S2>/Output' */
  uint8_T is_active_c3_SWatch2018;     /* '<S1>/SWatch2018' */
  uint8_T is_Interface;                /* '<S1>/SWatch2018' */
  uint8_T is_Stopwatch;                /* '<S1>/SWatch2018' */
  uint8_T is_TimeSet;                  /* '<S1>/SWatch2018' */
  uint8_T is_AlarmSet;                 /* '<S1>/SWatch2018' */
  uint8_T is_CountSwatch;              /* '<S1>/SWatch2018' */
  uint8_T is_Alarm;                    /* '<S1>/SWatch2018' */
  uint8_T hours;                       /* '<S1>/SWatch2018' */
  uint8_T minutes;                     /* '<S1>/SWatch2018' */
  uint8_T seconds;                     /* '<S1>/SWatch2018' */
  uint8_T tenths;                      /* '<S1>/SWatch2018' */
  uint8_T Ahours;                      /* '<S1>/SWatch2018' */
  uint8_T Aminutes;                    /* '<S1>/SWatch2018' */
  uint8_T Stenths;                     /* '<S1>/SWatch2018' */
  uint8_T Sseconds;                    /* '<S1>/SWatch2018' */
  uint8_T Sminutes;                    /* '<S1>/SWatch2018' */
  uint8_T Shours;                      /* '<S1>/SWatch2018' */
} DW_SWatch2018_T;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState SWatch2018_Trig_ZCE[7];   /* '<S1>/SWatch2018' */
} PrevZCX_SWatch2018_T;

/* Real-time Model Data Structure */
struct tag_RTM_SWatch2018_T {
  const char_T *errorStatus;
  PrevZCX_SWatch2018_T *prevZCSigState;
  DW_SWatch2018_T *dwork;
};

/* External data declarations for dependent source files */
const char *RT_MEMORY_ALLOCATION_ERROR;

/* Model entry point functions */
extern RT_MODEL_SWatch2018_T *SWatch2018(boolean_T *SWatch2018_U_plusbutton,
  boolean_T *SWatch2018_U_minusbutton, boolean_T *SWatch2018_U_Timemode,
  boolean_T *SWatch2018_U_Timesetmode, boolean_T *SWatch2018_U_Alarmsetmode,
  boolean_T *SWatch2018_U_Swatchmode, uint8_T *SWatch2018_Y_hours, uint8_T
  *SWatch2018_Y_minutes, uint8_T *SWatch2018_Y_seconds, uint8_T
  *SWatch2018_Y_tenths, uint8_T *SWatch2018_Y_mode);
extern void SWatch2018_initialize(RT_MODEL_SWatch2018_T *const SWatch2018_M,
  boolean_T *SWatch2018_U_plusbutton, boolean_T *SWatch2018_U_minusbutton,
  boolean_T *SWatch2018_U_Timemode, boolean_T *SWatch2018_U_Timesetmode,
  boolean_T *SWatch2018_U_Alarmsetmode, boolean_T *SWatch2018_U_Swatchmode,
  uint8_T *SWatch2018_Y_hours, uint8_T *SWatch2018_Y_minutes, uint8_T
  *SWatch2018_Y_seconds, uint8_T *SWatch2018_Y_tenths, uint8_T
  *SWatch2018_Y_mode);
extern void SWatch2018_step(RT_MODEL_SWatch2018_T *const SWatch2018_M, boolean_T
  SWatch2018_U_plusbutton, boolean_T SWatch2018_U_minusbutton, boolean_T
  SWatch2018_U_Timemode, boolean_T SWatch2018_U_Timesetmode, boolean_T
  SWatch2018_U_Alarmsetmode, boolean_T SWatch2018_U_Swatchmode, uint8_T
  *SWatch2018_Y_hours, uint8_T *SWatch2018_Y_minutes, uint8_T
  *SWatch2018_Y_seconds, uint8_T *SWatch2018_Y_tenths, uint8_T
  *SWatch2018_Y_mode);

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
 * hilite_system('stop/SWatch2018')    - opens subsystem stop/SWatch2018
 * hilite_system('stop/SWatch2018/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'stop'
 * '<S1>'   : 'stop/SWatch2018'
 * '<S2>'   : 'stop/SWatch2018/Counter Limited'
 * '<S3>'   : 'stop/SWatch2018/SWatch2018'
 * '<S4>'   : 'stop/SWatch2018/Counter Limited/Increment Real World'
 * '<S5>'   : 'stop/SWatch2018/Counter Limited/Wrap To Zero'
 */
#endif                                 /* RTW_HEADER_SWatch2018_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
