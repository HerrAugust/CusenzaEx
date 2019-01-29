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

char msg[96] = ""; // for debug


enum Signal getSignal(SWatch2018_U_plusbutton, SWatch2018_U_minusbutton,
        SWatch2018_U_Timemode, SWatch2018_U_Timesetmode, SWatch2018_U_Alarmsetmode, SWatch2018_U_Swatchmode) {
    enum Signal signal = -1;

    if(SWatch2018_U_plusbutton) {
        signal = SIG_PLUSBUTTON;
    } else if(SWatch2018_U_minusbutton) {
        signal = SIG_MINUSBUTTON;
    } else if(SWatch2018_U_Timemode) {
        signal = SIG_TIMEMODE;
    } else if(SWatch2018_U_Timesetmode) {
        signal = SIG_TIMESETMODE;
    } else if(SWatch2018_U_Alarmsetmode) {
        signal = SIG_ALARMSETMODE;
    } else if(SWatch2018_U_Swatchmode) {
        signal = SIG_SWATCHMODE;
    }

    return signal;
}

/**
 * Get state as string
 */
void getStateName(struct FSM *fsm) {
	switch(fsm->curState) {
	case INIT:
		strcpy(fsm->curStateName, "INIT");
		break;
	case TIMEDISPLAY:
		strcpy(fsm->curStateName, "TIMEDISPLAY");
		break;
	case TIMESET:
		strcpy(fsm->curStateName, "TIMESET");
		break;
	case ALARMSET:
		strcpy(fsm->curStateName, "ALARMSET");
		break;
	case STOPWATCH:
		strcpy(fsm->curStateName, "STOPWATCH");
		break;
	case ALARMSET_SETHOURS:
		strcpy(fsm->curStateName, "ALARMSET_SETHOURS");
		break;
	case ALARMSET_SETMINUTES:
		strcpy(fsm->curStateName, "ALARMSET_SETMINUTES");
		break;
	case ALARMSET_ALARMFINALLYSET:
		strcpy(fsm->curStateName, "INITALARMSET_ALARMFINALLYSET");
		break;
	case ALARMSET_INIT:
		strcpy(fsm->curStateName, "ALARMSET_INIT");
		break;
	case TIMESET_SETHOURS:
		strcpy(fsm->curStateName, "TIMESET_SETHOURS");
		break;
	case TIMESET_SETMINUTES:
		strcpy(fsm->curStateName, "TIMESET_SETMINUTES");
		break;
	case TIMECOUNT_COUNT:
		strcpy(fsm->curStateName, "TIMECOUNT_COUNT");
		break;
	case ALARMMANAGEMENT_SILENT:
		strcpy(fsm->curStateName, "ALARMMANAGEMENT_SILENT");
		break;
	case ALARMMANAGEMENT_BUZZING:
		strcpy(fsm->curStateName, "ALARMMANAGEMENT_BUZZING");
		break;
	case TIMECOUNTSTOPWATCH_BEGIN:
		strcpy(fsm->curStateName, "TIMECOUNTSTOPWATCH_BEGIN");
		break;
	case TIMECOUNTSTOPWATCH_COUNT:
		strcpy(fsm->curStateName, "TIMECOUNTSTOPWATCH_COUNT");
		break;
	default:
		strcpy(fsm->curStateName, "?");
		break;
	}
}

/**
 * Updates time (timedisplay)
 */
void updateTime(){
    tenths = (tenths+1) % 10;

    if(tenths == 0){
        seconds = (seconds+1) % 60;
        if(seconds == 0){
            minutes = (minutes+1) % 60;
            if(minutes == 0)
                hours = (hours+1) % 24;
        }
    }
    //printf("updateTime %d %d %d\n", seconds, minutes, hours);
}

/**
 * Updates the stopwatch counter
 */
void updateTimeStopwatch(){
    Stenths = (Stenths+1) % 10;

    if(Stenths == 0){
        Sseconds = (Sseconds+1) % 60;
        if(Sseconds == 0){
            Sminutes=(Sminutes+1) % 60;
            if(Sminutes == 0)
                Shours = (Shours+1) % 24;
        }
    }
}

/**
 * for debugging states
 */
void state2str(char* msg) {
	switch(curHighestLvState) {
	case INIT:
		strcpy(msg, "INIT");
		break;
	case TIMEDISPLAY:
		strcpy(msg, "TIMEDISPLAY");
		break;
	case TIMESET:
		strcpy(msg, "TIMESET");
		break;
	case ALARMSET:
		strcpy(msg, "ALARMSET");
		break;
	case STOPWATCH:
		strcpy(msg, "STOPWATCH");
		break;
	default:
		strcpy(msg, "other");
		break;
	}
}

//----------------------------------------------------------- TimeSet

void manageTimeSet_SETHOURS(struct FSM *fsm, enum Signal signal, uint8_T *SWatch2018_Y_hours,
        uint8_T *SWatch2018_Y_minutes, uint8_T *SWatch2018_Y_seconds, uint8_T *SWatch2018_Y_tenths,
        uint8_T *SWatch2018_Y_mode) {
	enum State  functionsState = TIMESET_SETHOURS;  // the state of this function
	uint8_T     statesMode = 0;                 	// the state mode
	if(!fsm->isEntryDone) {
		printf2UART("Init manageTimeSet_SETHOURS\r\n");

		//en:
		SWatch2018_Y_mode = statesMode;

		fsm->isEntryDone = 1;
		return;
	}
	DEBUG("a %d\r\n", curHighestLvState);
	if(curHighestLvState != TIMESET)
    	return;
	DEBUG("curHighestLvState is TIMESET(%d)\r\n", curHighestLvState);

	// handle signals:
	switch(signal) {
	case SIG_PLUSBUTTON:
		printf2UART("manageTimeSet_SETHOURS received a SIG_+\r\n");
		if(hours == 23)
			hours = 0;
		else
			hours++;
		break;
	case SIG_MINUSBUTTON:
		printf2UART("manageTimeSet_SETHOURS received a SIG_-\r\n");
		if(hours == 0)
			hours = 23;
		else
			hours--;
		break;
	case SIG_TIMESETMODE:
		printf2UART("manageTimeSet_SETHOURS received a SIG_{Å,T,TS}\r\n");
		tranFSM(fsm, TIMESET_SETMINUTES);
		break;
	default:
		//du:
		DEBUG("DU %u %u\r\n", hours, minutes);
		*SWatch2018_Y_hours 	= hours;
		*SWatch2018_Y_minutes 	= minutes;
		break;
	}
}

void manageTimeSet_SETMINUTES(struct FSM *fsm, enum Signal signal, uint8_T *SWatch2018_Y_hours,
        uint8_T *SWatch2018_Y_minutes, uint8_T *SWatch2018_Y_seconds, uint8_T *SWatch2018_Y_tenths,
        uint8_T *SWatch2018_Y_mode) {
	enum State  functionsState = TIMESET_SETMINUTES;   // the state of this function
	if(!fsm->isEntryDone) {
		//printf2UART("Init manTimeSet_SETMINUTES\r\n");

		fsm->isEntryDone = 1;
		return;
	}

	if(curHighestLvState != TIMESET)
    	return;

	// handle signals:
	switch(signal) {
	case SIG_PLUSBUTTON:
		//printf2UART("manTimeSet_SETMIN received a SIG_+\r\n");
		if(minutes == 59)
			minutes = 0;
		else
			minutes++;
		break;
	case SIG_MINUSBUTTON:
		//printf2UART("manTimeSet_SETMIN received a SIG_-\r\n");
		if(minutes == 0)
			minutes = 59;
		else
			minutes--;
		break;
	case SIG_TIMESETMODE:
		//printf2UART("manTimeSet_SETMIN received a SIG_TIMESETMODE\r\n");
		tranFSM(fsm, TIMESET_SETHOURS);
		break;
	default:
		//du:
		*SWatch2018_Y_hours 	= hours;
		*SWatch2018_Y_minutes 	= minutes;
		break;
	}
}

//----------------------------------------------------------- AlarmSet FSM

void manageAlarmSet_ALARMFINALLYSET(struct FSM *fsm, enum Signal signal, uint8_T *SWatch2018_Y_hours,
        uint8_T *SWatch2018_Y_minutes, uint8_T *SWatch2018_Y_seconds, uint8_T *SWatch2018_Y_tenths,
        uint8_T *SWatch2018_Y_mode) {
	enum State  functionsState = ALARMSET_ALARMFINALLYSET;   // the state of this function
	if(!fsm->isEntryDone) {
		//printf2UART("Init manAlarmSet_ALARMFINALLYSET. Waiting before to buzz...\r\n");

		// en:
		AalarmIsSet = 1;

		fsm->isEntryDone = 1;
		return;
	}

	// handle signals:
	switch(signal) {
	case SIG_ALARMSETMODE:
		//printf2UART("manageAlarmSet_ALARMFINALLYSET received a SIG_ALARMSETMODE\r\n");
		tranFSM(fsm, ALARMSET_SETHOURS);
		break;
	default:
		//du:
		break;
	}
}

void manageAlarmSet_SETHOURS(struct FSM *fsm, enum Signal signal, uint8_T *SWatch2018_Y_hours,
        uint8_T *SWatch2018_Y_minutes, uint8_T *SWatch2018_Y_seconds, uint8_T *SWatch2018_Y_tenths,
        uint8_T *SWatch2018_Y_mode) {
	enum State  functionsState = ALARMSET_SETHOURS;   // the state of this function
	if(!fsm->isEntryDone) {
		//printf2UART("Init manageAlarmSet_SETHOURS\r\n");

		fsm->isEntryDone = 1;
		return;
	}

	if(curHighestLvState != ALARMSET)
    	return;

	// handle signals:
	switch(signal) {
	case SIG_PLUSBUTTON:
		//printf2UART("manageAlarmSet_SETHOURS received a SIG_+\r\n");
		if(Ahours == 23)
			Ahours = 0;
		else
			Ahours++;
		break;
	case SIG_MINUSBUTTON:
		//printf2UART("manageAlarmSet_SETHOURS received a SIG_-\r\n");
		if(Ahours == 0)
			Ahours = 23;
		else
			Ahours--;
		break;
	case SIG_ALARMSETMODE:
		//printf2UART("manageAlarmSet_SETHOURS received a SIG_ALARMSETMODE\r\n");
		tranFSM(fsm, ALARMSET_SETMINUTES);
		Aminutes = minutes;
		break;
	default:
		//du:
		*SWatch2018_Y_hours 	= Ahours;
		*SWatch2018_Y_minutes 	= minutes;
		*SWatch2018_Y_seconds 	= 0;
		break;
	}
}

void manageAlarmSet_SETMINUTES(struct FSM *fsm, enum Signal signal, uint8_T *SWatch2018_Y_hours,
        uint8_T *SWatch2018_Y_minutes, uint8_T *SWatch2018_Y_seconds, uint8_T *SWatch2018_Y_tenths,
        uint8_T *SWatch2018_Y_mode) {
	enum State  functionsState = ALARMSET_SETMINUTES;   // the state of this function
	if(!fsm->isEntryDone) {
		//printf2UART("Init manageAlarmSet_SETMINUTES\r\n");

		fsm->isEntryDone = 1;
		return;
	}

	if(curHighestLvState != ALARMSET)
    	return;

	// handle signals:
	switch(signal) {
	case SIG_PLUSBUTTON:
		//printf2UART("manageAlarmSet_SETMINUTES received a SIG_+\r\n");
		if(Aminutes == 59)
			Aminutes = 0;
		else
			Aminutes++;
		break;
	case SIG_MINUSBUTTON:
		//printf2UART("manageAlarmSet_SETMINUTES received a SIG_-\r\n");
		if(Aminutes == 0)
			Aminutes = 59;
		else
			Aminutes--;
		break;
	case SIG_ALARMSETMODE:
		//printf2UART("manageAlarmSet_SETMINUTES received a SIG_ALARMSETMODE\r\n");
		tranFSM(fsm, ALARMSET_ALARMFINALLYSET);
		break;
	default:
		//du:
		*SWatch2018_Y_hours 	= hours;
		*SWatch2018_Y_minutes 	= Aminutes;
		break;
	}
}

//----------------------------------------------------------- TimeCountStopwatch FSM

void manageTimeCountStopwatch_BEGIN(struct FSM *fsm, enum Signal signal, uint8_T *SWatch2018_Y_hours,
        uint8_T *SWatch2018_Y_minutes, uint8_T *SWatch2018_Y_seconds, uint8_T *SWatch2018_Y_tenths,
        uint8_T *SWatch2018_Y_mode) {
	// en.
	enum State  functionsState = TIMECOUNTSTOPWATCH_BEGIN;   // the state of this function                 // the state mode
	printf2UART("ciao\r\n");
	if(!fsm->isEntryDone) {
		Stenths 	= 0;
		Sseconds 	= 0;
		Sminutes 	= 0;
		Shours 		= 0;

		printf2UART("Init manageTimeCountStopwatch_BEGIN\r\n");

		fsm->isEntryDone = 1;
		return;
	}

	printf2UART("manageTimeCountStopwatch_BEGIN\r\n");

	if(curHighestLvState != STOPWATCH)
    	return;

	sprintf(msg,"manageTimeCountStopwatch_BEGIN (FSM %s)\r\n", fsm->name);
	printf2UART(msg);

	// handle signals:
	switch(signal) {
	case SIG_SWATCHMODE:
		// begin to count
		printf2UART("manageTimeCountStopwatch_BEGIN received a SIG_SWATCHMODE\r\n");
		tranFSM(fsm, TIMECOUNTSTOPWATCH_COUNT);
		break;
	case SIG_ALARMSETMODE:
	case SIG_TIMESETMODE:
	case SIG_TIMEMODE:
		printf2UART("manageTimeCountStopwatch_BEGIN received a SIG_{Å,T,TS}\r\n");
		tranFSM(fsm, TIMECOUNTSTOPWATCH_BEGIN);
		break;
	default:
		break;
	}
}

void manageTimeCountStopwatch_COUNT(struct FSM *fsm, enum Signal signal, uint8_T *SWatch2018_Y_hours,
        uint8_T *SWatch2018_Y_minutes, uint8_T *SWatch2018_Y_seconds, uint8_T *SWatch2018_Y_tenths,
        uint8_T *SWatch2018_Y_mode) {
	// en.
	enum State  functionsState = TIMECOUNTSTOPWATCH_COUNT;   // the state of this function                 // the state mode
	if(!fsm->isEntryDone) {
		printf2UART("Init manageTimeCountStopwatch_COUNT\r\n");
		fsm->isEntryDone = 1;
		return;
	}

	if(curHighestLvState != STOPWATCH)
    	return;

	updateTimeStopwatch();

	// handle signals:
	switch(signal) {
	case SIG_SWATCHMODE:
		DEBUG( "manageTimeCountStopwatch_COUNT received a SIG_SWATCHMODE (FSM %s)\r\n", fsm->name);
		break;
	case SIG_ALARMSETMODE:
	case SIG_TIMESETMODE:
	case SIG_TIMEMODE:
		DEBUG("manageTimeCountStopwatch_COUNT received a SIG_{Å,T,TS} (FSM %s)\r\n", fsm->name);
		tranFSM(fsm, TIMECOUNTSTOPWATCH_BEGIN);
		// shouldn't be necessary, but without them the SW stops...
		*SWatch2018_Y_hours = hours;
		*SWatch2018_Y_minutes = minutes;
		*SWatch2018_Y_seconds = seconds;
		//DEBUG("per sicur %d %d %d %u %u %u\r\n", hours, minutes, seconds, *SWatch2018_Y_hours, *SWatch2018_Y_minutes, *SWatch2018_Y_seconds);
		break;
	default:
		break;
	}
}

//-----------------------------------------------------------Highest level FSM (Interface)

void manageTIMEDISPLAY(struct FSM *fsm, enum Signal signal, uint8_T *SWatch2018_Y_hours,
                       uint8_T *SWatch2018_Y_minutes, uint8_T *SWatch2018_Y_seconds, uint8_T *SWatch2018_Y_tenths,
                       uint8_T *SWatch2018_Y_mode) {
    // en:
    enum State  functionsState = TIMEDISPLAY;   // the state of this function
    uint8_T     statesMode = 0;                 // the state mode
    *SWatch2018_Y_mode = statesMode;
    if(!fsm->isEntryDone) {
    	//printf2UART("Initializing manageTIMEDISPLAY\r\n");
        *SWatch2018_Y_mode = statesMode;
        fsm->isEntryDone = 1;
        return;
    }

    // handle signals:
    switch(signal) {
        case SIG_TIMEMODE:
        	printf2UART("manageTIMEDISPLAY(). Received SIG_TIMEMODE (=goto time display)\r\n");
            tranFSM(fsm, TIMEDISPLAY);
            curHighestLvState = TIMEDISPLAY;
            break;
        case SIG_TIMESETMODE:
        	printf2UART("manageTIMEDISPLAY(). Received SIG_TIMESETMODE\r\n");
            tranFSM(fsm, TIMESET);
            curHighestLvState = TIMESET;
            break;
        case SIG_ALARMSETMODE:
        	printf2UART("manageTIMEDISPLAY(). Received SIG_ALARMSETMODE\r\n");
            tranFSM(fsm, ALARMSET);
            curHighestLvState = ALARMSET;
            break;
        case SIG_SWATCHMODE:
        	printf2UART("manageTIMEDISPLAY(). Received SIG_SWATCHMODE (=timer)\r\n");
            tranFSM(fsm, STOPWATCH);
            curHighestLvState = STOPWATCH;
            break;
        default:
            // du:
            *SWatch2018_Y_hours = hours;
            *SWatch2018_Y_minutes = minutes;
            *SWatch2018_Y_seconds = seconds;
            *SWatch2018_Y_tenths = 0;
            break;
    }
}

void manageSTOPWATCH(struct FSM *fsm, enum Signal signal, uint8_T *SWatch2018_Y_hours,
                       uint8_T *SWatch2018_Y_minutes, uint8_T *SWatch2018_Y_seconds, uint8_T *SWatch2018_Y_tenths,
                       uint8_T *SWatch2018_Y_mode) {
    // en:
    enum State  functionsState = STOPWATCH;   // the state of this function
    uint8_T     statesMode = 3;               // the state mode
    *SWatch2018_Y_mode = statesMode;
    if(!fsm->isEntryDone) {
    	//printf2UART("Init manSTOPWATCH\r\n");
        *SWatch2018_Y_mode = statesMode;
        *SWatch2018_Y_hours = 0;
		*SWatch2018_Y_minutes = 0;
		*SWatch2018_Y_seconds = 0;

        fsm->isEntryDone = 1;
        return;
    }

    // handle signals:
    switch(signal) {
        case SIG_TIMEMODE:
        	//printf2UART("manSTOPWATCH(). Received SIG_TIMEMODE\r\n");
            tranFSM(fsm, TIMEDISPLAY);
            curHighestLvState = TIMEDISPLAY;
            break;
        case SIG_TIMESETMODE:
        	//printf2UART("manSTOPWATCH(). Received SIG_TIMESETMODE\r\n");
            tranFSM(fsm, TIMESET);
            curHighestLvState = TIMESET;
            break;
        case SIG_ALARMSETMODE:
        	//printf2UART("manSTOPWATCH(). Received SIG_ALARMSETMODE\r\n");
            tranFSM(fsm, ALARMSET);
            curHighestLvState = ALARMSET;
            break;
        case SIG_SWATCHMODE:
        	//printf2UART("manSTOPWATCH(). Received SIG_SWATCHMODE\r\n");
            tranFSM(fsm, STOPWATCH);
            curHighestLvState = STOPWATCH;
            break;
        default:
            // du:
            *SWatch2018_Y_hours = Shours;
            *SWatch2018_Y_minutes = Sminutes;
            *SWatch2018_Y_seconds = Sseconds;
            *SWatch2018_Y_tenths = Stenths;
            break;
    }
}

void manageTIMESET(struct FSM *fsm, enum Signal signal, uint8_T *SWatch2018_Y_hours,
                       uint8_T *SWatch2018_Y_minutes, uint8_T *SWatch2018_Y_seconds, uint8_T *SWatch2018_Y_tenths,
                       uint8_T *SWatch2018_Y_mode) {
    // en:
    enum State  functionsState 	= TIMESET;   // the state of this function
    uint8_T     statesMode 		= 1;         // the state mode
    *SWatch2018_Y_mode = statesMode;
    if(!fsm->isEntryDone) {
    	//printf2UART("Init manTIMESET\r\n");

        fsm->isEntryDone = 1;
        return;
    }

    // handle signals:
    switch(signal) {
        case SIG_TIMEMODE:
        	//printf2UART("manTIMESET(). Received SIG_TIMEMODE\r\n");
            tranFSM(fsm, TIMEDISPLAY);
            curHighestLvState = TIMEDISPLAY;
            break;
        case SIG_TIMESETMODE:
        	//printf2UART("manTIMESET(). Received SIG_TIMESETMODE\r\n");
            tranFSM(fsm, TIMESET);
            curHighestLvState = TIMESET;
            break;
        case SIG_ALARMSETMODE:
        	//printf2UART("manTIMESET(). Received SIG_ALARMSETMODE\r\n");
            tranFSM(fsm, ALARMSET);
            curHighestLvState = ALARMSET;
            break;
        case SIG_SWATCHMODE:
        	//printf2UART("manTIMESET(). Received SIG_SWATCHMODE\r\n");
            tranFSM(fsm, STOPWATCH);
            curHighestLvState = STOPWATCH;
            break;
        default:
            // du:
            break;
    }
}

void manageALARMSET(struct FSM *fsm, enum Signal signal, uint8_T *SWatch2018_Y_hours,
                       uint8_T *SWatch2018_Y_minutes, uint8_T *SWatch2018_Y_seconds, uint8_T *SWatch2018_Y_tenths,
                       uint8_T *SWatch2018_Y_mode) {
    // en:
    enum State  functionsState = ALARMSET;   // the state of this function
    uint8_T     statesMode 		= 2;         // the state mode
    *SWatch2018_Y_mode = statesMode;
    if(!fsm->isEntryDone) {
    	//printf2UART("Init manageALARMSET (highest-lv state)\r\n");

        fsm->isEntryDone = 1;
        return;
    }

    // handle signals:
    switch(signal) {
        case SIG_TIMEMODE:
        	//printf2UART("manALARMSET(). Received SIG_TIMEMODE\r\n");
            tranFSM(fsm, TIMEDISPLAY);
            break;
        case SIG_TIMESETMODE:
        	//printf2UART("manALARMSET(). Received SIG_TIMESETMODE\r\n");
            tranFSM(fsm, TIMESET);
            break;
        case SIG_ALARMSETMODE:
        	//printf2UART("manALARMSET(). Received SIG_ALARMSETMODE\r\n");
            tranFSM(fsm, ALARMSET);
            break;
        case SIG_SWATCHMODE:
        	//printf2UART("manALARMSET(). Received SIG_SWATCHMODE\r\n");
            tranFSM(fsm, STOPWATCH);
            break;
        default:
            // du:
            break;
    }
}

void manageTimeCountStopwatch(struct FSM *fsm, enum Signal signal, uint8_T *SWatch2018_Y_hours,
                       uint8_T *SWatch2018_Y_minutes, uint8_T *SWatch2018_Y_seconds, uint8_T *SWatch2018_Y_tenths,
                       uint8_T *SWatch2018_Y_mode) {
    // en:           // the state mode
    if(!fsm->isEntryDone) {
        Stenths 	= 0;
        Sseconds 	= 0;
		Sminutes 	= 0;
		Shours 		= 0;

        fsm->isEntryDone = 1;
        return;
    }

    // handle signals:
    switch(signal) {
        case SIG_TIMEMODE:
        	//printf2UART("manageTimeCountStopwatch(). Received SIG_TIMEMODE\r\n");
            tranFSM(fsm, TIMEDISPLAY);
            break;
        case SIG_TIMESETMODE:
        	//printf2UART("manageTimeCountStopwatch(). Received SIG_TIMESETMODE\r\n");
            tranFSM(fsm, TIMESET);
            break;
        case SIG_ALARMSETMODE:
        	//printf2UART("manageTimeCountStopwatch(). Received SIG_ALARMSETMODE\r\n");
            tranFSM(fsm, ALARMSET);
            break;
        case SIG_SWATCHMODE:
        	//printf2UART("manageTimeCountStopwatch(). Received SIG_SWATCHMODE\r\n");
            tranFSM(fsm, TIMECOUNTSTOPWATCH_COUNT);
            break;
        default:
            // du:
            *SWatch2018_Y_hours = Shours;
            *SWatch2018_Y_minutes = Sminutes;
            *SWatch2018_Y_seconds = Sseconds;
            *SWatch2018_Y_tenths = Stenths;
            break;
    }
}

/**
 * Given the current state, decide what must be done or the transition to do, in the Finite State Machine.
 * Here, booleans are passed to see what button has been clicked.
 */
void dispatchFSM(struct FSM *fsm,
              boolean_T SWatch2018_U_plusbutton, boolean_T SWatch2018_U_minusbutton,
              boolean_T SWatch2018_U_Timemode, boolean_T SWatch2018_U_Timesetmode, boolean_T SWatch2018_U_Alarmsetmode, boolean_T SWatch2018_U_Swatchmode, uint8_T *SWatch2018_Y_hours,
              uint8_T *SWatch2018_Y_minutes, uint8_T *SWatch2018_Y_seconds, uint8_T *SWatch2018_Y_tenths,
              uint8_T *SWatch2018_Y_mode) {

	char msg[40] = ""; //debug
	enum Signal signal = -1;

    // aggregate signals to make it possible to use nested switches
    signal = getSignal(SWatch2018_U_plusbutton, SWatch2018_U_minusbutton,
                       SWatch2018_U_Timemode, SWatch2018_U_Timesetmode, SWatch2018_U_Alarmsetmode, SWatch2018_U_Swatchmode);

    DEBUG("FSM %s entra in stato %s\r\n", fsm->name, fsm->curStateName);
    // the current state must be reinitialized also when the user clicks something
    //fsm->isEntryDone = SWatch2018_U_plusbutton || SWatch2018_U_minusbutton ||
    //        SWatch2018_U_Timemode || SWatch2018_U_Timesetmode || SWatch2018_U_Alarmsetmode || SWatch2018_U_Swatchmode;

    // find the current state and manage it
    switch(fsm->curState) {
    	// Highest level FSM
        case INIT:
            *SWatch2018_Y_hours = *SWatch2018_Y_minutes = *SWatch2018_Y_seconds = *SWatch2018_Y_tenths = 0;
            tranFSM(fsm, TIMEDISPLAY);
            break;
        case TIMEDISPLAY:
        	// time always goes on, no matter if user clicks or not GUI buttons
        	updateTime();

            manageTIMEDISPLAY(fsm, signal, SWatch2018_Y_hours, SWatch2018_Y_minutes, SWatch2018_Y_seconds, SWatch2018_Y_tenths, SWatch2018_Y_mode);
            break;
        case STOPWATCH:
        	// time always goes on, no matter if user clicks or not GUI buttons
        	updateTime();

        	manageSTOPWATCH(fsm, signal, SWatch2018_Y_hours, SWatch2018_Y_minutes, SWatch2018_Y_seconds, SWatch2018_Y_tenths, SWatch2018_Y_mode);
        	break;
        case TIMESET:
        	// time always goes on, no matter if user clicks or not GUI buttons
        	updateTime();

        	manageTIMESET(fsm, signal, SWatch2018_Y_hours, SWatch2018_Y_minutes, SWatch2018_Y_seconds, SWatch2018_Y_tenths, SWatch2018_Y_mode);
        	break;
        case ALARMSET:
        	// time always goes on, no matter if user clicks or not GUI buttons
        	updateTime();

        	DEBUG("displatchFSM. ALARMSET\r\n");
        	manageALARMSET(fsm, signal, SWatch2018_Y_hours, SWatch2018_Y_minutes, SWatch2018_Y_seconds, SWatch2018_Y_tenths, SWatch2018_Y_mode);
        	break;

		// TimeCountStopwatch FSM
		case TIMECOUNTSTOPWATCH_BEGIN:
			DEBUG("displatchFSM. TIMECOUNTSTOPWATCH_BEGIN\r\n");
			manageTimeCountStopwatch_BEGIN(fsm, signal, SWatch2018_Y_hours, SWatch2018_Y_minutes, SWatch2018_Y_seconds, SWatch2018_Y_tenths, SWatch2018_Y_mode);
			break;
		case TIMECOUNTSTOPWATCH_COUNT:
			DEBUG("displatchFSM. TIMECOUNTSTOPWATCH_COUNT\r\n");
			manageTimeCountStopwatch_COUNT(fsm, signal, SWatch2018_Y_hours, SWatch2018_Y_minutes, SWatch2018_Y_seconds, SWatch2018_Y_tenths, SWatch2018_Y_mode);
			DEBUG("HHO\r\n");
			break;

		// TimeSet FSM
		case TIMESET_SETHOURS:
			printf2UART("displatchFSM. TIMESET_SETHOURS\r\n");
			manageTimeSet_SETHOURS(fsm, signal, SWatch2018_Y_hours, SWatch2018_Y_minutes, SWatch2018_Y_seconds, SWatch2018_Y_tenths, SWatch2018_Y_mode);
			DEBUG("%u %u %u\r\n", *SWatch2018_Y_hours, *SWatch2018_Y_minutes, *SWatch2018_Y_seconds);
			break;
		case TIMESET_SETMINUTES:
			printf2UART("displatchFSM. TIMESET_SETMINUTES\r\n");
			manageTimeSet_SETMINUTES(fsm, signal, SWatch2018_Y_hours, SWatch2018_Y_minutes, SWatch2018_Y_seconds, SWatch2018_Y_tenths, SWatch2018_Y_mode);
			break;

		// AlarmManagement FSM
		case ALARMMANAGEMENT_SILENT:
			printf2UART("displatchFSM. ALARMMANAGEMENT_SILENT\r\n");
			if(Ahours == hours && Aminutes == minutes && AalarmIsSet)
				tranFSM(fsm, ALARMMANAGEMENT_BUZZING);
			break;
		case ALARMMANAGEMENT_BUZZING:
			printf2UART("displatchFSM. ALARMMANAGEMENT_BUZZING\r\n");
			if(minutes <= Aminutes - 2) {
				printf2UART("ALARM BUZZING!!\r\n");
			}
			if(Ahours != hours || Aminutes != minutes) {
				tranFSM(fsm, ALARMMANAGEMENT_SILENT);
				printf("ALARM going back silent\r\n");
			}
			break;

		// AlarmSet FSM
		case ALARMSET_INIT:
			printf2UART("displatchFSM. ALARMSET_INIT\r\n");
			Ahours = hours;
			*SWatch2018_Y_minutes = minutes;
			AalarmIsSet = 0;
			tranFSM(fsm, ALARMSET_SETHOURS);
			break;
		case ALARMSET_SETHOURS:
			printf2UART("displatchFSM. ALARMSET_SETHOURS\r\n");
			manageAlarmSet_SETHOURS(fsm, signal, SWatch2018_Y_hours, SWatch2018_Y_minutes, SWatch2018_Y_seconds, SWatch2018_Y_tenths, SWatch2018_Y_mode);
			DEBUG("%u %u %u\r\n", *SWatch2018_Y_hours, *SWatch2018_Y_minutes, *SWatch2018_Y_seconds);
			break;
		case ALARMSET_SETMINUTES:
			printf2UART("displatchFSM. ALARMSET_SETMINUTES\r\n");
			manageAlarmSet_SETMINUTES(fsm, signal, SWatch2018_Y_hours, SWatch2018_Y_minutes, SWatch2018_Y_seconds, SWatch2018_Y_tenths, SWatch2018_Y_mode);
			break;
		case ALARMSET_ALARMFINALLYSET:
			printf2UART("displatchFSM. ALARMSET_ALARMFINALLYSET\r\n");
			manageAlarmSet_ALARMFINALLYSET(fsm, signal, SWatch2018_Y_hours, SWatch2018_Y_minutes, SWatch2018_Y_seconds, SWatch2018_Y_tenths, SWatch2018_Y_mode);
			break;
        default:
            break;
    }
}

/**
 * Executes transition to state "dest" in Finite State Machine fsm
 */
void tranFSM(struct FSM* fsm, enum State dest) {
    fsm->curState = dest;
    fsm->isEntryDone = 0;
    getStateName(fsm);
}

/**
 * Initialize Finite State Machine
 */
void initFSM(struct FSM *fsm, enum Subcomponent sc, char* name) {
    switch(sc) {
    case SC_NONE:
    	fsm->curState = INIT;
    	strcpy(fsm->curStateName, "INIT");
    	break;
    case SC_TIMECOUNTSTOPWATCH:
    	fsm->curState = TIMECOUNTSTOPWATCH_BEGIN;
    	strcpy(fsm->curStateName, "TIMECOUNTSTOPWATCH_BEGIN");
    	break;
    case SC_TIMESET:
    	fsm->curState = TIMESET_SETHOURS;
    	strcpy(fsm->curStateName, "TIMESET_SETHOURS");
    	break;
    case SC_ALARMSET:
    	fsm->curState = ALARMSET_INIT;
    	strcpy(fsm->curStateName, "ALARMSET_INIT");
    	break;
    case SC_ALARMMANAGEMENT:
    	fsm->curState = ALARMMANAGEMENT_SILENT;
    	strcpy(fsm->curStateName, "ALARMMANAGEMENT_SILENT");
    	break;
    default:
    	break;
    }

    fsm->isEntryDone = 0;
    strcpy(fsm->name, name);

}
