#include "TimeService.h"
#include "FakeTimeService.h"

static Time savedTime;
static int period = 0;
static WakeupCallback callback = NULL;

void FakeTimeService_Create(void) {
    savedTime.minuteOfDay = TIME_UNKNOWN;
    savedTime.dayOfWeek   = TIME_UNKNOWN;
}
void FakeTimeService_Destroy(void) {
}

void TimeService_GetTime(Time *time) {

    time->minuteOfDay = savedTime.minuteOfDay;
    time->dayOfWeek = savedTime.dayOfWeek;
}

void FakeTimeService_SetMinute(int minute) {
    savedTime.minuteOfDay = minute;

}
void FakeTimeService_SetDay(int day) {
    savedTime.dayOfWeek = day;
}

#include <stdio.h>

void TimeService_SetPeriodicAlarmInSeconds(int seconds, WakeupCallback cb) {
    callback = cb;
    period = seconds;
}
void TimeService_CancelPeriodicAlarmInSeconds(int seconds, WakeupCallback cb) {
    if(cb == callback && period == seconds) {
        callback = NULL;
        period = 0;
    }
}

WakeupCallback FakeTimeService_GetAlarmCallback(void) {
    return callback;
}
int FakeTimeService_GetAlarmPeriod(void) {
    return period;
}
