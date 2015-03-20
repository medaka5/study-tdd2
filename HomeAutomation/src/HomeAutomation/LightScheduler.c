#include <stdbool.h>
#include "LightScheduler.h"
#include "LightController.h"
#include "TimeService.h"

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
static ScheduledLightEvent scheduledEvent;

void LightScheduler_Create(void) {
    scheduledEvent.id = UNUSED;

    TimeService_SetPeriodicAlarmInSeconds(60, LightScheduler_Wakeup);
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

    processEventDueNow(&time, &scheduledEvent);
}
static void scheduleEvent(int id, int dayOfWeek, int minuteOfDay, int event) {
    scheduledEvent.id = id;
    scheduledEvent.dayOfWeek = dayOfWeek;
    scheduledEvent.minuteOfDay = minuteOfDay;
    scheduledEvent.event = event;
}
void LightScheduler_ScheduleTurnOn(int id, int day, int minuteOfDay) {
    scheduleEvent(id, day, minuteOfDay, TURN_ON);
}
void LightScheduler_ScheduleTurnOff(int id, int day, int minuteOfDay) {
    scheduleEvent(id, day, minuteOfDay, TURN_OFF);
}
