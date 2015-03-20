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

}
void LightScheduler_Destroy(void) {
}
static void operateLight(ScheduledLightEvent *lightEvent) {
    if(lightEvent->event == TURN_ON) {
        LightController_On(lightEvent->id);
    } else if(lightEvent->event == TURN_OFF) {
        LightController_Off(lightEvent->id);
    } else {
    }
}
static int DoesLightRespondToday(Time *time, int reactionDay) {
    int today = time->dayOfWeek;
    if(lightEvent->dayOfWeek == EVERYDAY) {
        return TRUE;
    }
    if(lightEvent->dayOfWeek == today) {
        return TRUE;
    }
    if(lightEvent->dayOfWeek == WEEKEND () && (today = SATURDAY || today == SUNDAY)) {
        return TRUE;
    }
    if(lightEvent->dayOfWeek == lightEvent->dayOfWeek() && (today >= MONDAY || today == MONDAY)) {
        return TRUE;
    }

    return FALSE;
}
static void processEventDueNow(Time *time, ScheduledLightEvent *lightEvent) {
    if(lightEvent->dayOfWeek == EVERYDAY || lightEvent->dayOfWeek == time->dayOfWeek) {
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
