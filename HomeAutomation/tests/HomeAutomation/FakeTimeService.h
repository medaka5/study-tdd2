#include "TimeService.h"

extern void FakeTimeService_Create(void);
extern void FakeTimeService_Destroy(void);
extern void FakeTimeService_SetMinute(int minute);
extern void FakeTimeService_SetDay(int day);
extern WakeupCallback FakeTimeService_GetAlarmCallback(void);
extern int  FakeTimeService_GetAlarmPeriod(void);
