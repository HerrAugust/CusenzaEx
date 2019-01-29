/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: SWatch2018.c
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

#include "SWatch2018.h"
#include "SWatch2018_private.h"

/* Named constants for Chart: '<S1>/SWatch2018' */
#define SWatch2018_IN_AlarmSet         ((uint8_T)1U)
#define SWatch2018_IN_Buzzing          ((uint8_T)1U)
#define SWatch2018_IN_CounterSwatch    ((uint8_T)1U)
#define SWatch2018_IN_DisplayLap       ((uint8_T)1U)
#define SWatch2018_IN_DisplaySwatch    ((uint8_T)2U)
#define SWatch2018_IN_NO_ACTIVE_CHILD  ((uint8_T)0U)
#define SWatch2018_IN_SetHours         ((uint8_T)1U)
#define SWatch2018_IN_SetMinutes       ((uint8_T)2U)
#define SWatch2018_IN_Silent           ((uint8_T)2U)
#define SWatch2018_IN_Stop             ((uint8_T)2U)
#define SWatch2018_IN_Stopwatch        ((uint8_T)2U)
#define SWatch2018_IN_TimeDisplay      ((uint8_T)3U)
#define SWatch2018_IN_TimeSet          ((uint8_T)4U)
#define SWatch2018_event_Alarmsetmode  (5)
#define SWatch2018_event_Swatchmode    (6)
#define SWatch2018_event_Tick          (0)
#define SWatch2018_event_Timemode      (3)
#define SWatch2018_event_Timesetmode   (4)
#define SWatch2018_event_minusbutton   (2)
#define SWatch2018_event_plusbutton    (1)

/* Forward declaration for local functions */
static void SWatch2018_Interface(const int32_T *sfEvent, uint8_T
  *SWatch2018_Y_hours, uint8_T *SWatch2018_Y_minutes, uint8_T
  *SWatch2018_Y_seconds, uint8_T *SWatch2018_Y_tenths, uint8_T
  *SWatch2018_Y_mode, DW_SWatch2018_T *SWatch2018_DW);
static void SWatch2_chartstep_c3_SWatch2018(const int32_T *sfEvent, uint8_T
  *SWatch2018_Y_hours, uint8_T *SWatch2018_Y_minutes, uint8_T
  *SWatch2018_Y_seconds, uint8_T *SWatch2018_Y_tenths, uint8_T
  *SWatch2018_Y_mode, DW_SWatch2018_T *SWatch2018_DW);

/* Function for Chart: '<S1>/SWatch2018' */
static void SWatch2018_Interface(const int32_T *sfEvent, uint8_T
  *SWatch2018_Y_hours, uint8_T *SWatch2018_Y_minutes, uint8_T
  *SWatch2018_Y_seconds, uint8_T *SWatch2018_Y_tenths, uint8_T
  *SWatch2018_Y_mode, DW_SWatch2018_T *SWatch2018_DW)
{
  uint8_T x;
  int32_T tmp;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  if (*sfEvent == SWatch2018_event_Timemode) {
    SWatch2018_DW->is_AlarmSet = SWatch2018_IN_NO_ACTIVE_CHILD;
    SWatch2018_DW->is_Stopwatch = SWatch2018_IN_NO_ACTIVE_CHILD;
    SWatch2018_DW->is_TimeSet = SWatch2018_IN_NO_ACTIVE_CHILD;
    SWatch2018_DW->is_Interface = SWatch2018_IN_TimeDisplay;

    /* Outport: '<Root>/mode' */
    *SWatch2018_Y_mode = 0U;
  } else {
    guard1 = false;
    guard2 = false;
    switch (SWatch2018_DW->is_Interface) {
     case SWatch2018_IN_AlarmSet:
      if (*sfEvent == SWatch2018_event_Timesetmode) {
        SWatch2018_DW->is_AlarmSet = SWatch2018_IN_NO_ACTIVE_CHILD;
        SWatch2018_DW->is_Interface = SWatch2018_IN_TimeSet;

        /* Outport: '<Root>/mode' */
        *SWatch2018_Y_mode = 1U;
        SWatch2018_DW->is_TimeSet = SWatch2018_IN_SetHours;
      } else if (*sfEvent == SWatch2018_event_Swatchmode) {
        SWatch2018_DW->is_AlarmSet = SWatch2018_IN_NO_ACTIVE_CHILD;
        SWatch2018_DW->is_Interface = SWatch2018_IN_Stopwatch;

        /* Outport: '<Root>/mode' */
        *SWatch2018_Y_mode = 3U;
        SWatch2018_DW->is_Stopwatch = SWatch2018_IN_DisplaySwatch;
      } else {
        switch (SWatch2018_DW->is_AlarmSet) {
         case SWatch2018_IN_SetHours:
          if (*sfEvent == SWatch2018_event_plusbutton) {
            tmp = (int32_T)(SWatch2018_DW->Ahours + 1U);
            if ((uint32_T)tmp > 255U) {
              tmp = 255;
            }

            SWatch2018_DW->Ahours = (uint8_T)((uint32_T)(uint8_T)tmp - (uint8_T)
              ((uint8_T)tmp / 24U * 24U));
            guard2 = true;
          } else if (*sfEvent == SWatch2018_event_minusbutton) {
            tmp = (int32_T)(SWatch2018_DW->Ahours + 24U);
            if ((uint32_T)tmp > 255U) {
              tmp = 255;
            }

            x = (uint8_T)(tmp - 1);
            SWatch2018_DW->Ahours = (uint8_T)((uint32_T)x - (uint8_T)(x / 24U *
              24U));
            guard2 = true;
          } else {
            if (*sfEvent == SWatch2018_event_Alarmsetmode) {
              SWatch2018_DW->is_AlarmSet = SWatch2018_IN_SetMinutes;

              /* Outport: '<Root>/hours' */
              *SWatch2018_Y_hours = SWatch2018_DW->Ahours;

              /* Outport: '<Root>/minutes' */
              *SWatch2018_Y_minutes = SWatch2018_DW->Aminutes;
            }
          }
          break;

         default:
          if (*sfEvent == SWatch2018_event_minusbutton) {
            tmp = (int32_T)(SWatch2018_DW->Aminutes + 60U);
            if ((uint32_T)tmp > 255U) {
              tmp = 255;
            }

            x = (uint8_T)(tmp - 1);
            SWatch2018_DW->Aminutes = (uint8_T)((uint32_T)x - (uint8_T)(x / 60U *
              60U));
            guard1 = true;
          } else if (*sfEvent == SWatch2018_event_plusbutton) {
            tmp = (int32_T)(SWatch2018_DW->Aminutes + 1U);
            if ((uint32_T)tmp > 255U) {
              tmp = 255;
            }

            SWatch2018_DW->Aminutes = (uint8_T)((uint32_T)(uint8_T)tmp -
              (uint8_T)((uint8_T)tmp / 24U * 24U));
            guard1 = true;
          } else {
            if (*sfEvent == SWatch2018_event_Alarmsetmode) {
              SWatch2018_DW->is_AlarmSet = SWatch2018_IN_SetHours;

              /* Outport: '<Root>/hours' */
              *SWatch2018_Y_hours = SWatch2018_DW->Ahours;

              /* Outport: '<Root>/minutes' */
              *SWatch2018_Y_minutes = SWatch2018_DW->Aminutes;
            }
          }
          break;
        }
      }
      break;

     case SWatch2018_IN_Stopwatch:
      switch (*sfEvent) {
       case SWatch2018_event_Timesetmode:
        SWatch2018_DW->is_Stopwatch = SWatch2018_IN_NO_ACTIVE_CHILD;
        SWatch2018_DW->is_Interface = SWatch2018_IN_TimeSet;

        /* Outport: '<Root>/mode' */
        *SWatch2018_Y_mode = 1U;
        SWatch2018_DW->is_TimeSet = SWatch2018_IN_SetHours;
        break;

       case SWatch2018_event_Alarmsetmode:
        SWatch2018_DW->is_Stopwatch = SWatch2018_IN_NO_ACTIVE_CHILD;
        SWatch2018_DW->is_Interface = SWatch2018_IN_AlarmSet;

        /* Outport: '<Root>/mode' */
        *SWatch2018_Y_mode = 2U;
        SWatch2018_DW->is_AlarmSet = SWatch2018_IN_SetHours;

        /* Outport: '<Root>/hours' */
        *SWatch2018_Y_hours = SWatch2018_DW->Ahours;

        /* Outport: '<Root>/minutes' */
        *SWatch2018_Y_minutes = SWatch2018_DW->Aminutes;
        break;

       default:
        if (SWatch2018_DW->is_Stopwatch == SWatch2018_IN_DisplayLap) {
          if (*sfEvent == SWatch2018_event_plusbutton) {
            SWatch2018_DW->is_Stopwatch = SWatch2018_IN_DisplaySwatch;
          }
        } else if (*sfEvent == SWatch2018_event_plusbutton) {
          SWatch2018_DW->is_Stopwatch = SWatch2018_IN_DisplayLap;
        } else {
          /* Outport: '<Root>/hours' */
          *SWatch2018_Y_hours = SWatch2018_DW->Shours;

          /* Outport: '<Root>/minutes' */
          *SWatch2018_Y_minutes = SWatch2018_DW->Sminutes;

          /* Outport: '<Root>/seconds' */
          *SWatch2018_Y_seconds = SWatch2018_DW->Sseconds;

          /* Outport: '<Root>/tenths' */
          *SWatch2018_Y_tenths = SWatch2018_DW->Stenths;
        }
        break;
      }
      break;

     case SWatch2018_IN_TimeDisplay:
      switch (*sfEvent) {
       case SWatch2018_event_Timesetmode:
        SWatch2018_DW->is_Interface = SWatch2018_IN_TimeSet;

        /* Outport: '<Root>/mode' */
        *SWatch2018_Y_mode = 1U;
        SWatch2018_DW->is_TimeSet = SWatch2018_IN_SetHours;
        break;

       case SWatch2018_event_Alarmsetmode:
        SWatch2018_DW->is_Interface = SWatch2018_IN_AlarmSet;

        /* Outport: '<Root>/mode' */
        *SWatch2018_Y_mode = 2U;
        SWatch2018_DW->is_AlarmSet = SWatch2018_IN_SetHours;

        /* Outport: '<Root>/hours' */
        *SWatch2018_Y_hours = SWatch2018_DW->Ahours;

        /* Outport: '<Root>/minutes' */
        *SWatch2018_Y_minutes = SWatch2018_DW->Aminutes;
        break;

       case SWatch2018_event_Swatchmode:
        SWatch2018_DW->is_Interface = SWatch2018_IN_Stopwatch;

        /* Outport: '<Root>/mode' */
        *SWatch2018_Y_mode = 3U;
        SWatch2018_DW->is_Stopwatch = SWatch2018_IN_DisplaySwatch;
        break;

       default:
        /* Outport: '<Root>/hours' */
        *SWatch2018_Y_hours = SWatch2018_DW->hours;

        /* Outport: '<Root>/minutes' */
        *SWatch2018_Y_minutes = SWatch2018_DW->minutes;

        /* Outport: '<Root>/seconds' */
        *SWatch2018_Y_seconds = SWatch2018_DW->seconds;
        break;
      }
      break;

     default:
      switch (*sfEvent) {
       case SWatch2018_event_Alarmsetmode:
        SWatch2018_DW->is_TimeSet = SWatch2018_IN_NO_ACTIVE_CHILD;
        SWatch2018_DW->is_Interface = SWatch2018_IN_AlarmSet;

        /* Outport: '<Root>/mode' */
        *SWatch2018_Y_mode = 2U;
        SWatch2018_DW->is_AlarmSet = SWatch2018_IN_SetHours;

        /* Outport: '<Root>/hours' */
        *SWatch2018_Y_hours = SWatch2018_DW->Ahours;

        /* Outport: '<Root>/minutes' */
        *SWatch2018_Y_minutes = SWatch2018_DW->Aminutes;
        break;

       case SWatch2018_event_Swatchmode:
        SWatch2018_DW->is_TimeSet = SWatch2018_IN_NO_ACTIVE_CHILD;
        SWatch2018_DW->is_Interface = SWatch2018_IN_Stopwatch;

        /* Outport: '<Root>/mode' */
        *SWatch2018_Y_mode = 3U;
        SWatch2018_DW->is_Stopwatch = SWatch2018_IN_DisplaySwatch;
        break;

       default:
        if (SWatch2018_DW->is_TimeSet == SWatch2018_IN_SetHours) {
          switch (*sfEvent) {
           case SWatch2018_event_plusbutton:
            tmp = (int32_T)(SWatch2018_DW->hours + 1U);
            if ((uint32_T)tmp > 255U) {
              tmp = 255;
            }

            SWatch2018_DW->hours = (uint8_T)((uint32_T)(uint8_T)tmp - (uint8_T)
              ((uint8_T)tmp / 24U * 24U));
            SWatch2018_DW->is_TimeSet = SWatch2018_IN_SetHours;
            break;

           case SWatch2018_event_Timesetmode:
            SWatch2018_DW->is_TimeSet = SWatch2018_IN_SetMinutes;
            break;

           case SWatch2018_event_minusbutton:
            tmp = (int32_T)(SWatch2018_DW->hours + 24U);
            if ((uint32_T)tmp > 255U) {
              tmp = 255;
            }

            x = (uint8_T)(tmp - 1);
            SWatch2018_DW->hours = (uint8_T)((uint32_T)x - (uint8_T)(x / 24U *
              24U));
            SWatch2018_DW->is_TimeSet = SWatch2018_IN_SetHours;
            break;

           default:
            /* Outport: '<Root>/hours' */
            *SWatch2018_Y_hours = SWatch2018_DW->hours;

            /* Outport: '<Root>/minutes' */
            *SWatch2018_Y_minutes = SWatch2018_DW->minutes;
            break;
          }
        } else {
          switch (*sfEvent) {
           case SWatch2018_event_plusbutton:
            tmp = (int32_T)(SWatch2018_DW->minutes + 1U);
            if ((uint32_T)tmp > 255U) {
              tmp = 255;
            }

            SWatch2018_DW->minutes = (uint8_T)((uint32_T)(uint8_T)tmp - (uint8_T)
              ((uint8_T)tmp / 24U * 24U));
            SWatch2018_DW->is_TimeSet = SWatch2018_IN_SetMinutes;
            break;

           case SWatch2018_event_minusbutton:
            tmp = (int32_T)(SWatch2018_DW->minutes + 60U);
            if ((uint32_T)tmp > 255U) {
              tmp = 255;
            }

            x = (uint8_T)(tmp - 1);
            SWatch2018_DW->minutes = (uint8_T)((uint32_T)x - (uint8_T)(x / 60U *
              60U));
            SWatch2018_DW->is_TimeSet = SWatch2018_IN_SetMinutes;
            break;

           case SWatch2018_event_Timesetmode:
            SWatch2018_DW->is_TimeSet = SWatch2018_IN_SetHours;
            break;

           default:
            /* Outport: '<Root>/hours' */
            *SWatch2018_Y_hours = SWatch2018_DW->hours;

            /* Outport: '<Root>/minutes' */
            *SWatch2018_Y_minutes = SWatch2018_DW->minutes;
            break;
          }
        }
        break;
      }
      break;
    }

    if (guard2) {
      SWatch2018_DW->is_AlarmSet = SWatch2018_IN_SetHours;

      /* Outport: '<Root>/hours' */
      *SWatch2018_Y_hours = SWatch2018_DW->Ahours;

      /* Outport: '<Root>/minutes' */
      *SWatch2018_Y_minutes = SWatch2018_DW->Aminutes;
    }

    if (guard1) {
      SWatch2018_DW->is_AlarmSet = SWatch2018_IN_SetMinutes;

      /* Outport: '<Root>/hours' */
      *SWatch2018_Y_hours = SWatch2018_DW->Ahours;

      /* Outport: '<Root>/minutes' */
      *SWatch2018_Y_minutes = SWatch2018_DW->Aminutes;
    }
  }
}

/* Function for Chart: '<S1>/SWatch2018' */
static void SWatch2_chartstep_c3_SWatch2018(const int32_T *sfEvent, uint8_T
  *SWatch2018_Y_hours, uint8_T *SWatch2018_Y_minutes, uint8_T
  *SWatch2018_Y_seconds, uint8_T *SWatch2018_Y_tenths, uint8_T
  *SWatch2018_Y_mode, DW_SWatch2018_T *SWatch2018_DW)
{
  int32_T tmp;

  /* Chart: '<S1>/SWatch2018' */
  if (SWatch2018_DW->is_active_c3_SWatch2018 == 0U) {
    SWatch2018_DW->is_active_c3_SWatch2018 = 1U;
    SWatch2018_DW->hours = 0U;
    SWatch2018_DW->minutes = 0U;
    SWatch2018_DW->seconds = 0U;
    SWatch2018_DW->Ahours = 0U;
    SWatch2018_DW->Aminutes = 0U;
    SWatch2018_DW->is_Interface = SWatch2018_IN_TimeDisplay;

    /* Outport: '<Root>/mode' */
    *SWatch2018_Y_mode = 0U;

    /* Outport: '<Root>/tenths' */
    *SWatch2018_Y_tenths = 0U;
    SWatch2018_DW->tenths = 0U;
    SWatch2018_DW->is_CountSwatch = SWatch2018_IN_Stop;
    SWatch2018_DW->Shours = 0U;
    SWatch2018_DW->Sminutes = 0U;
    SWatch2018_DW->Sseconds = 0U;
    SWatch2018_DW->Stenths = 0U;
    SWatch2018_DW->is_Alarm = SWatch2018_IN_Silent;
  } else {
    SWatch2018_Interface(sfEvent, SWatch2018_Y_hours, SWatch2018_Y_minutes,
                         SWatch2018_Y_seconds, SWatch2018_Y_tenths,
                         SWatch2018_Y_mode, SWatch2018_DW);
    if (*sfEvent == SWatch2018_event_Tick) {
      if (SWatch2018_DW->tenths == 9) {
        SWatch2018_DW->tenths = 0U;
        if (SWatch2018_DW->seconds == 59) {
          SWatch2018_DW->seconds = 0U;
          if (SWatch2018_DW->minutes == 59) {
            SWatch2018_DW->minutes = 0U;
            tmp = (int32_T)(SWatch2018_DW->hours + 1U);
            if ((uint32_T)tmp > 255U) {
              tmp = 255;
            }

            SWatch2018_DW->hours = (uint8_T)((uint32_T)(uint8_T)tmp - (uint8_T)
              ((uint8_T)tmp / 24U * 24U));
          } else {
            tmp = (int32_T)(SWatch2018_DW->minutes + 1U);
            if ((uint32_T)tmp > 255U) {
              tmp = 255;
            }

            SWatch2018_DW->minutes = (uint8_T)tmp;
          }
        } else {
          tmp = (int32_T)(SWatch2018_DW->seconds + 1U);
          if ((uint32_T)tmp > 255U) {
            tmp = 255;
          }

          SWatch2018_DW->seconds = (uint8_T)tmp;
        }
      } else {
        tmp = (int32_T)(SWatch2018_DW->tenths + 1U);
        if ((uint32_T)tmp > 255U) {
          tmp = 255;
        }

        SWatch2018_DW->tenths = (uint8_T)tmp;
      }
    }

    if (SWatch2018_DW->is_CountSwatch == SWatch2018_IN_CounterSwatch) {
      switch (*sfEvent) {
       case SWatch2018_event_minusbutton:
        SWatch2018_DW->is_CountSwatch = SWatch2018_IN_Stop;
        SWatch2018_DW->Shours = 0U;
        SWatch2018_DW->Sminutes = 0U;
        SWatch2018_DW->Sseconds = 0U;
        SWatch2018_DW->Stenths = 0U;
        break;

       case SWatch2018_event_Tick:
        if (SWatch2018_DW->Stenths == 9) {
          SWatch2018_DW->Stenths = 0U;
          if (SWatch2018_DW->Sseconds == 59) {
            SWatch2018_DW->Sseconds = 0U;
            if (SWatch2018_DW->Sminutes == 59) {
              SWatch2018_DW->Sminutes = 0U;
              tmp = (int32_T)(SWatch2018_DW->Shours + 1U);
              if ((uint32_T)tmp > 255U) {
                tmp = 255;
              }

              SWatch2018_DW->Shours = (uint8_T)((uint32_T)(uint8_T)tmp -
                (uint8_T)((uint8_T)tmp / 24U * 24U));
            } else {
              tmp = (int32_T)(SWatch2018_DW->Sminutes + 1U);
              if ((uint32_T)tmp > 255U) {
                tmp = 255;
              }

              SWatch2018_DW->Sminutes = (uint8_T)tmp;
            }
          } else {
            tmp = (int32_T)(SWatch2018_DW->Sseconds + 1U);
            if ((uint32_T)tmp > 255U) {
              tmp = 255;
            }

            SWatch2018_DW->Sseconds = (uint8_T)tmp;
          }
        } else {
          tmp = (int32_T)(SWatch2018_DW->Stenths + 1U);
          if ((uint32_T)tmp > 255U) {
            tmp = 255;
          }

          SWatch2018_DW->Stenths = (uint8_T)tmp;
        }

        SWatch2018_DW->is_CountSwatch = SWatch2018_IN_CounterSwatch;
        break;
      }
    } else {
      if (*sfEvent == SWatch2018_event_Swatchmode) {
        SWatch2018_DW->is_CountSwatch = SWatch2018_IN_CounterSwatch;
      }
    }

    if (SWatch2018_DW->is_Alarm == SWatch2018_IN_Buzzing) {
      if ((SWatch2018_DW->Ahours != SWatch2018_DW->hours) ||
          (SWatch2018_DW->Aminutes != SWatch2018_DW->minutes)) {
        SWatch2018_DW->is_Alarm = SWatch2018_IN_Silent;
      }
    } else {
      if ((SWatch2018_DW->Ahours == SWatch2018_DW->hours) &&
          (SWatch2018_DW->Aminutes == SWatch2018_DW->minutes)) {
        SWatch2018_DW->is_Alarm = SWatch2018_IN_Buzzing;
      }
    }
  }

  /* End of Chart: '<S1>/SWatch2018' */
}

/* Model step function */
void SWatch2018_step(RT_MODEL_SWatch2018_T *const SWatch2018_M, boolean_T
                     SWatch2018_U_plusbutton, boolean_T SWatch2018_U_minusbutton,
                     boolean_T SWatch2018_U_Timemode, boolean_T
                     SWatch2018_U_Timesetmode, boolean_T
                     SWatch2018_U_Alarmsetmode, boolean_T
                     SWatch2018_U_Swatchmode, uint8_T *SWatch2018_Y_hours,
                     uint8_T *SWatch2018_Y_minutes, uint8_T
                     *SWatch2018_Y_seconds, uint8_T *SWatch2018_Y_tenths,
                     uint8_T *SWatch2018_Y_mode)
{
  DW_SWatch2018_T *SWatch2018_DW = ((DW_SWatch2018_T *) SWatch2018_M->dwork);
  PrevZCX_SWatch2018_T *SWatch2018_PrevZCX = ((PrevZCX_SWatch2018_T *)
    SWatch2018_M->prevZCSigState);
  boolean_T zcEvent[7];
  int32_T sfEvent;
  boolean_T zcEvent_0;

  /* Chart: '<S1>/SWatch2018' incorporates:
   *  TriggerPort: '<S3>/input events'
   */
  /* DataTypeConversion: '<S1>/Data Type Conversion' incorporates:
   *  UnitDelay: '<S2>/Output'
   */
  zcEvent[0] = (((SWatch2018_DW->Output_DSTATE != 0) !=
                 (SWatch2018_PrevZCX->SWatch2018_Trig_ZCE[0] == POS_ZCSIG)) &&
                (SWatch2018_PrevZCX->SWatch2018_Trig_ZCE[0] !=
                 UNINITIALIZED_ZCSIG));

  /* Inport: '<Root>/plusbutton' */
  zcEvent[1] = (((SWatch2018_PrevZCX->SWatch2018_Trig_ZCE[1] == POS_ZCSIG) !=
                 (int32_T)SWatch2018_U_plusbutton) &&
                (SWatch2018_PrevZCX->SWatch2018_Trig_ZCE[1] !=
                 UNINITIALIZED_ZCSIG));

  /* Inport: '<Root>/minusbutton' */
  zcEvent[2] = (((SWatch2018_PrevZCX->SWatch2018_Trig_ZCE[2] == POS_ZCSIG) !=
                 (int32_T)SWatch2018_U_minusbutton) &&
                (SWatch2018_PrevZCX->SWatch2018_Trig_ZCE[2] !=
                 UNINITIALIZED_ZCSIG));

  /* Inport: '<Root>/Timemode' */
  zcEvent[3] = (((SWatch2018_PrevZCX->SWatch2018_Trig_ZCE[3] == POS_ZCSIG) !=
                 (int32_T)SWatch2018_U_Timemode) &&
                (SWatch2018_PrevZCX->SWatch2018_Trig_ZCE[3] !=
                 UNINITIALIZED_ZCSIG));

  /* Inport: '<Root>/Timesetmode' */
  zcEvent[4] = (((SWatch2018_PrevZCX->SWatch2018_Trig_ZCE[4] == POS_ZCSIG) !=
                 (int32_T)SWatch2018_U_Timesetmode) &&
                (SWatch2018_PrevZCX->SWatch2018_Trig_ZCE[4] !=
                 UNINITIALIZED_ZCSIG));

  /* Inport: '<Root>/Alarmsetmode' */
  zcEvent[5] = (((SWatch2018_PrevZCX->SWatch2018_Trig_ZCE[5] == POS_ZCSIG) !=
                 (int32_T)SWatch2018_U_Alarmsetmode) &&
                (SWatch2018_PrevZCX->SWatch2018_Trig_ZCE[5] !=
                 UNINITIALIZED_ZCSIG));

  /* Inport: '<Root>/Swatchmode' */
  zcEvent[6] = (((SWatch2018_PrevZCX->SWatch2018_Trig_ZCE[6] == POS_ZCSIG) !=
                 (int32_T)SWatch2018_U_Swatchmode) &&
                (SWatch2018_PrevZCX->SWatch2018_Trig_ZCE[6] !=
                 UNINITIALIZED_ZCSIG));
  zcEvent_0 = false;
  for (sfEvent = 0; sfEvent < 7; sfEvent++) {
    zcEvent_0 = (zcEvent_0 || zcEvent[sfEvent]);
  }

  if (zcEvent_0) {
    /* DataTypeConversion: '<S1>/Data Type Conversion' incorporates:
     *  UnitDelay: '<S2>/Output'
     */
    if ((int8_T)(zcEvent[0] ? SWatch2018_DW->Output_DSTATE != 0 ? RISING_ZCEVENT
                 : FALLING_ZCEVENT : NO_ZCEVENT) != 0) {
      sfEvent = SWatch2018_event_Tick;
      SWatch2_chartstep_c3_SWatch2018(&sfEvent, SWatch2018_Y_hours,
        SWatch2018_Y_minutes, SWatch2018_Y_seconds, SWatch2018_Y_tenths,
        SWatch2018_Y_mode, SWatch2018_DW);
    }

    /* Inport: '<Root>/plusbutton' */
    if ((int8_T)(zcEvent[1] ? SWatch2018_U_plusbutton ? RISING_ZCEVENT :
                 FALLING_ZCEVENT : NO_ZCEVENT) == 1) {
      sfEvent = SWatch2018_event_plusbutton;
      SWatch2_chartstep_c3_SWatch2018(&sfEvent, SWatch2018_Y_hours,
        SWatch2018_Y_minutes, SWatch2018_Y_seconds, SWatch2018_Y_tenths,
        SWatch2018_Y_mode, SWatch2018_DW);
    }

    /* Inport: '<Root>/minusbutton' */
    if ((int8_T)(zcEvent[2] ? SWatch2018_U_minusbutton ? RISING_ZCEVENT :
                 FALLING_ZCEVENT : NO_ZCEVENT) == 1) {
      sfEvent = SWatch2018_event_minusbutton;
      SWatch2_chartstep_c3_SWatch2018(&sfEvent, SWatch2018_Y_hours,
        SWatch2018_Y_minutes, SWatch2018_Y_seconds, SWatch2018_Y_tenths,
        SWatch2018_Y_mode, SWatch2018_DW);
    }

    /* Inport: '<Root>/Timemode' */
    if ((int8_T)(zcEvent[3] ? SWatch2018_U_Timemode ? RISING_ZCEVENT :
                 FALLING_ZCEVENT : NO_ZCEVENT) == 1) {
      sfEvent = SWatch2018_event_Timemode;
      SWatch2_chartstep_c3_SWatch2018(&sfEvent, SWatch2018_Y_hours,
        SWatch2018_Y_minutes, SWatch2018_Y_seconds, SWatch2018_Y_tenths,
        SWatch2018_Y_mode, SWatch2018_DW);
    }

    /* Inport: '<Root>/Timesetmode' */
    if ((int8_T)(zcEvent[4] ? SWatch2018_U_Timesetmode ? RISING_ZCEVENT :
                 FALLING_ZCEVENT : NO_ZCEVENT) == 1) {
      sfEvent = SWatch2018_event_Timesetmode;
      SWatch2_chartstep_c3_SWatch2018(&sfEvent, SWatch2018_Y_hours,
        SWatch2018_Y_minutes, SWatch2018_Y_seconds, SWatch2018_Y_tenths,
        SWatch2018_Y_mode, SWatch2018_DW);
    }

    /* Inport: '<Root>/Alarmsetmode' */
    if ((int8_T)(zcEvent[5] ? SWatch2018_U_Alarmsetmode ? RISING_ZCEVENT :
                 FALLING_ZCEVENT : NO_ZCEVENT) == 1) {
      sfEvent = SWatch2018_event_Alarmsetmode;
      SWatch2_chartstep_c3_SWatch2018(&sfEvent, SWatch2018_Y_hours,
        SWatch2018_Y_minutes, SWatch2018_Y_seconds, SWatch2018_Y_tenths,
        SWatch2018_Y_mode, SWatch2018_DW);
    }

    /* Inport: '<Root>/Swatchmode' */
    if ((int8_T)(zcEvent[6] ? SWatch2018_U_Swatchmode ? RISING_ZCEVENT :
                 FALLING_ZCEVENT : NO_ZCEVENT) == 1) {
      sfEvent = SWatch2018_event_Swatchmode;
      SWatch2_chartstep_c3_SWatch2018(&sfEvent, SWatch2018_Y_hours,
        SWatch2018_Y_minutes, SWatch2018_Y_seconds, SWatch2018_Y_tenths,
        SWatch2018_Y_mode, SWatch2018_DW);
    }
  }

  /* DataTypeConversion: '<S1>/Data Type Conversion' incorporates:
   *  UnitDelay: '<S2>/Output'
   */
  SWatch2018_PrevZCX->SWatch2018_Trig_ZCE[0] = (ZCSigState)
    (SWatch2018_DW->Output_DSTATE != 0);

  /* Inport: '<Root>/plusbutton' */
  SWatch2018_PrevZCX->SWatch2018_Trig_ZCE[1] = SWatch2018_U_plusbutton;

  /* Inport: '<Root>/minusbutton' */
  SWatch2018_PrevZCX->SWatch2018_Trig_ZCE[2] = SWatch2018_U_minusbutton;

  /* Inport: '<Root>/Timemode' */
  SWatch2018_PrevZCX->SWatch2018_Trig_ZCE[3] = SWatch2018_U_Timemode;

  /* Inport: '<Root>/Timesetmode' */
  SWatch2018_PrevZCX->SWatch2018_Trig_ZCE[4] = SWatch2018_U_Timesetmode;

  /* Inport: '<Root>/Alarmsetmode' */
  SWatch2018_PrevZCX->SWatch2018_Trig_ZCE[5] = SWatch2018_U_Alarmsetmode;

  /* Inport: '<Root>/Swatchmode' */
  SWatch2018_PrevZCX->SWatch2018_Trig_ZCE[6] = SWatch2018_U_Swatchmode;

  /* Sum: '<S4>/FixPt Sum1' incorporates:
   *  Constant: '<S4>/FixPt Constant'
   *  UnitDelay: '<S2>/Output'
   */
  SWatch2018_DW->Output_DSTATE++;

  /* Switch: '<S5>/FixPt Switch' incorporates:
   *  Constant: '<S5>/Constant'
   *  UnitDelay: '<S2>/Output'
   */
  if (SWatch2018_DW->Output_DSTATE > 1) {
    SWatch2018_DW->Output_DSTATE = 0U;
  }

  /* End of Switch: '<S5>/FixPt Switch' */
}

/* Model initialize function */
void SWatch2018_initialize(RT_MODEL_SWatch2018_T *const SWatch2018_M, boolean_T *
  SWatch2018_U_plusbutton, boolean_T *SWatch2018_U_minusbutton, boolean_T
  *SWatch2018_U_Timemode, boolean_T *SWatch2018_U_Timesetmode, boolean_T
  *SWatch2018_U_Alarmsetmode, boolean_T *SWatch2018_U_Swatchmode, uint8_T
  *SWatch2018_Y_hours, uint8_T *SWatch2018_Y_minutes, uint8_T
  *SWatch2018_Y_seconds, uint8_T *SWatch2018_Y_tenths, uint8_T
  *SWatch2018_Y_mode)
{
  DW_SWatch2018_T *SWatch2018_DW = ((DW_SWatch2018_T *) SWatch2018_M->dwork);
  PrevZCX_SWatch2018_T *SWatch2018_PrevZCX = ((PrevZCX_SWatch2018_T *)
    SWatch2018_M->prevZCSigState);

  {
    int32_T i;
    for (i = 0; i < 7; i++) {
      SWatch2018_PrevZCX->SWatch2018_Trig_ZCE[i] = UNINITIALIZED_ZCSIG;
    }

    /* SystemInitialize for Chart: '<S1>/SWatch2018' */
    SWatch2018_DW->is_Alarm = SWatch2018_IN_NO_ACTIVE_CHILD;
    SWatch2018_DW->is_Interface = SWatch2018_IN_NO_ACTIVE_CHILD;
    SWatch2018_DW->is_AlarmSet = SWatch2018_IN_NO_ACTIVE_CHILD;
    SWatch2018_DW->is_Stopwatch = SWatch2018_IN_NO_ACTIVE_CHILD;
    SWatch2018_DW->is_TimeSet = SWatch2018_IN_NO_ACTIVE_CHILD;
    SWatch2018_DW->is_CountSwatch = SWatch2018_IN_NO_ACTIVE_CHILD;
    SWatch2018_DW->is_active_c3_SWatch2018 = 0U;
  }
}

/* Model data allocation function */
RT_MODEL_SWatch2018_T *SWatch2018(boolean_T *SWatch2018_U_plusbutton, boolean_T *
  SWatch2018_U_minusbutton, boolean_T *SWatch2018_U_Timemode, boolean_T
  *SWatch2018_U_Timesetmode, boolean_T *SWatch2018_U_Alarmsetmode, boolean_T
  *SWatch2018_U_Swatchmode, uint8_T *SWatch2018_Y_hours, uint8_T
  *SWatch2018_Y_minutes, uint8_T *SWatch2018_Y_seconds, uint8_T
  *SWatch2018_Y_tenths, uint8_T *SWatch2018_Y_mode)
{
  RT_MODEL_SWatch2018_T *SWatch2018_M;
  SWatch2018_M = (RT_MODEL_SWatch2018_T *) malloc(sizeof(RT_MODEL_SWatch2018_T));
  if (SWatch2018_M == NULL) {
    return NULL;
  }

  (void) memset((char *)SWatch2018_M, 0,
                sizeof(RT_MODEL_SWatch2018_T));

  /* states (dwork) */
  {
    DW_SWatch2018_T *dwork = (DW_SWatch2018_T *) malloc(sizeof(DW_SWatch2018_T));
    rt_VALIDATE_MEMORY(SWatch2018_M,dwork);
    SWatch2018_M->dwork = (dwork);
  }

  /* previous zero-crossing states */
  {
    PrevZCX_SWatch2018_T *zc = (PrevZCX_SWatch2018_T *) malloc(sizeof
      (PrevZCX_SWatch2018_T));
    rt_VALIDATE_MEMORY(SWatch2018_M,zc);
    SWatch2018_M->prevZCSigState = (zc);
  }

  {
    DW_SWatch2018_T *SWatch2018_DW = ((DW_SWatch2018_T *) SWatch2018_M->dwork);
    PrevZCX_SWatch2018_T *SWatch2018_PrevZCX = ((PrevZCX_SWatch2018_T *)
      SWatch2018_M->prevZCSigState);

    /* states (dwork) */
    (void) memset((void *)SWatch2018_DW, 0,
                  sizeof(DW_SWatch2018_T));

    /* external inputs */
    *SWatch2018_U_plusbutton = false;
    *SWatch2018_U_minusbutton = false;
    *SWatch2018_U_Timemode = false;
    *SWatch2018_U_Timesetmode = false;
    *SWatch2018_U_Alarmsetmode = false;
    *SWatch2018_U_Swatchmode = false;

    /* external outputs */
    (*SWatch2018_Y_hours) = 0U;
    (*SWatch2018_Y_minutes) = 0U;
    (*SWatch2018_Y_seconds) = 0U;
    (*SWatch2018_Y_tenths) = 0U;
    (*SWatch2018_Y_mode) = 0U;

    /* previous zero-crossing states */
    {
    }
  }

  return SWatch2018_M;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
