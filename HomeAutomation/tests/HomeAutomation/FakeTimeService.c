#include "TimeService.h"
#include "FakeTimeService.h"

static Time savedTime;

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
    
