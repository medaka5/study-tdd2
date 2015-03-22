
#include "CppUTest/TestHarness.h"
extern "C" {
#include "LightControllerSpy.h"
#include "TimeService.h"
#include "FakeTimeService.h"
#include "LightScheduler.h"
}

TEST_GROUP(LightScheduler)
{
    void setup()
    {
        LightController_Create();
        LightScheduler_Create();
    }

    void teardown()
    {
        LightController_Destroy();
        LightScheduler_Destroy();
    }
    void setTimeTo(int day, int minuteOfDay) {
        FakeTimeService_SetDay(day);
        FakeTimeService_SetMinute(minuteOfDay);
    }
    void checkLightState(int id, int level) {
    	if (id == LIGHT_ID_UNKNOWN) {
	        LONGS_EQUAL(id, LightControllerSpy_GetLastId());
	        LONGS_EQUAL(level, LightControllerSpy_GetLastState());
    	} else {
	        LONGS_EQUAL(level, LightControllerSpy_GetLightState(id));
    	}
    }
};

TEST(LightScheduler, NoChangeToLightsDuringInitialization)
{
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}


TEST(LightScheduler, NoScheduleNothingHappens)
{
    setTimeTo(MONDAY, 100);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}
TEST(LightScheduler, ScheduleOnEverydayNotTimeYet)
{
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
    setTimeTo(MONDAY, 100);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleOnEverydayItsTime)
{
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
    setTimeTo(MONDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, ScheduleOffEverydayItsTime)
{
    LightScheduler_ScheduleTurnOff(3, EVERYDAY, 1200);
    setTimeTo(MONDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(3, LIGHT_OFF);
}

TEST(LightScheduler, scheduleTuestayButItsMonday)
{
    LightScheduler_ScheduleTurnOn(3, TUESDAY, 1200);
    setTimeTo(MONDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, scheduleTuestayAndItsTuesday)
{
    LightScheduler_ScheduleTurnOn(4, TUESDAY, 1200);
    setTimeTo(TUESDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(4, LIGHT_ON);
}

TEST(LightScheduler, scheduleWeekdayAndItsTuesday)
{
    LightScheduler_ScheduleTurnOn(4, WEEKDAY, 1200);
    setTimeTo(TUESDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(4, LIGHT_ON);
}
TEST(LightScheduler, scheduleWeekdayAndItsSaturday)
{
    LightScheduler_ScheduleTurnOn(4, WEEKDAY, 1200);
    setTimeTo(SATURDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, scheduleWeekendAndItsFriday)
{
    LightScheduler_ScheduleTurnOn(2, WEEKEND, 1200);
    setTimeTo(FRIDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);

}
TEST(LightScheduler, scheduleWeekendAndItsSaturday)
{
    LightScheduler_ScheduleTurnOn(2, WEEKEND, 1200);
    setTimeTo(SATURDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(2, LIGHT_ON);
}


TEST(LightScheduler, ScheduleTwoEventAtTheSameTime)
{
    LightScheduler_ScheduleTurnOn(3, SUNDAY, 1200);
    LightScheduler_ScheduleTurnOn(12, SUNDAY, 1200);
    setTimeTo(SUNDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(3, LIGHT_ON);
    checkLightState(12, LIGHT_ON);
}
TEST(LightScheduler, RejectsTooManyEvents)
{
	for(int i = 0; i < 128; i++) {
		LONGS_EQUAL(LS_OK, LightScheduler_ScheduleTurnOn(6, MONDAY, 600+i));
	}
	LONGS_EQUAL(LS_TOO_MANY_EVENTS, LightScheduler_ScheduleTurnOn(6, MONDAY, 600+129));
}

/***************************************************/
TEST_GROUP(LightSchedulerInitAndCleanup)
{
};

TEST(LightSchedulerInitAndCleanup, CreateStartsOneMinuteAlarm)
{
    LightScheduler_Create();
    POINTERS_EQUAL((void*)LightScheduler_Wakeup, (void*)FakeTimeService_GetAlarmCallback());
    LONGS_EQUAL(60, FakeTimeService_GetAlarmPeriod());
    LightScheduler_Destroy();
}


TEST(LightSchedulerInitAndCleanup, DestroyCancelsOneMinuteAlarm)
{
    LightScheduler_Create();
    LightScheduler_Destroy();
    POINTERS_EQUAL(NULL, (void*)FakeTimeService_GetAlarmCallback());
}
