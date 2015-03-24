#include <stdbool.h>

#include "LightScheduler.h"
#include "LightController.h"
#include "TimeService.h"
#include "RandomMinute.h"

typedef struct 
{
    int id;
    int minuteOfDay;
    int dayOfWeek;
    int event;
} ScheduledLightEvent;

enum {
    UNUSED = -1,
    TURN_ON = 1,
    TURN_OFF = 2,
};
static ScheduledLightEvent scheduledEvents[MAX_EVENT];

void LightScheduler_Create(void) {
    for(int i = 0; i < MAX_EVENT; i++) {
    	scheduledEvents[i].id = UNUSED;
    }
    TimeService_SetPeriodicAlarmInSeconds(60, LightScheduler_Wakeup);
    RandomMinute_Create(30);

}
void LightScheduler_Destroy(void) {
    TimeService_CancelPeriodicAlarmInSeconds(60, LightScheduler_Wakeup);
}
static void operateLight(ScheduledLightEvent *lightEvent) {
    if(lightEvent->event == TURN_ON) {
        LightController_On(lightEvent->id);
    } else if(lightEvent->event == TURN_OFF) {
        LightController_Off(lightEvent->id);
    } else {
    }
}
static int DoesLightRespondToday(ScheduledLightEvent *lightEvent, Time *time) {
    int today = time->dayOfWeek;

    if(lightEvent->id == UNUSED) {
    	return false;
    }
    if(lightEvent->dayOfWeek == EVERYDAY) {
        return true;
    }
    if(lightEvent->dayOfWeek == today) {
        return true;
    }
    if(lightEvent->dayOfWeek == WEEKEND && (today == SATURDAY || today == SUNDAY)) {
        return true;
    }
    if(lightEvent->dayOfWeek == WEEKDAY && (today >= MONDAY && today <= FRIDAY)) {
        return true;
    }

    return false;
}
static void processEventDueNow(Time *time, ScheduledLightEvent *lightEvent) {
    if(DoesLightRespondToday(lightEvent, time)) {
        if(time->minuteOfDay == lightEvent->minuteOfDay) {
            operateLight(lightEvent);
        }
    }
}
void LightScheduler_Wakeup(void) {
    Time time;
    TimeService_GetTime(&time);

    for(int i = 0; i < MAX_EVENT; i++) {
	    processEventDueNow(&time, &scheduledEvents[i]);
    }
}
static int scheduleEvent(int id, int dayOfWeek, int minuteOfDay, int event) {

	if(id < 0 || id > 31) {
		return LS_OUT_OF_BOUNDS;
	}

	int i;
    for(i = 0; i < MAX_EVENT; i++) {
    	if(scheduledEvents[i].id == UNUSED) {
    		scheduledEvents[i].id = id;
    		scheduledEvents[i].dayOfWeek = dayOfWeek;
    		scheduledEvents[i].minuteOfDay = minuteOfDay;
    		scheduledEvents[i].event = event;
    		break;
    	}
    }
    if(i >= MAX_EVENT) {
    	return LS_TOO_MANY_EVENTS;
    } else {
    	return LS_OK;
    }
}
int LightScheduler_ScheduleTurnOn(int id, int day, int minuteOfDay) {
    return scheduleEvent(id, day, minuteOfDay, TURN_ON);
}
int LightScheduler_ScheduleTurnOff(int id, int day, int minuteOfDay) {
    return scheduleEvent(id, day, minuteOfDay, TURN_OFF);
}
void LightScheduler_ScheduleRemove(int id, int day, int minuteOfDay) {
	int i;
    for(i = 0; i < MAX_EVENT; i++) {
    	if(scheduledEvents[i].id == id &&
    	  scheduledEvents[i].dayOfWeek == day &&
		  scheduledEvents[i].minuteOfDay == minuteOfDay) {
    		scheduledEvents[i].id = UNUSED;
    		break;
    	}
    }
}
void LightScheduler_Randomize(int id, int day, int minuteOfDay) {
	int i;
    for(i = 0; i < MAX_EVENT; i++) {
    	if(scheduledEvents[i].id == id) {
    	  scheduledEvents[i].dayOfWeek = day;
		  scheduledEvents[i].minuteOfDay = minuteOfDay + RandomMinute_Get();
    	}
    }
}

