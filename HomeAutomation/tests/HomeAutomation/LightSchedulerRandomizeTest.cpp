#include "CppUTest/TestHarness.h"
extern "C" {
#include "RandomMinute.h"
#include "LightControllerSpy.h"
#include "LightScheduler.h"
#include "FakeRandomMinute.h"
#include "TimeService.h"
#include "FakeTimeService.h"
}

TEST_GROUP(LightSchedulerRandomize)
{
	int (*savedRandomMinute_Get)();
	void setup(){
		LightController_Create();
		LightScheduler_Create();
		savedRandomMinute_Get = RandomMinute_Get;
		RandomMinute_Get = FakeRandomMinute_Get;
	}
	void teardown() {
        LightController_Destroy();
        LightScheduler_Destroy();
		RandomMinute_Get = savedRandomMinute_Get;
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

TEST(LightSchedulerRandomize, TurnOnEarly)
{
	FakeRandomMinute_SetFirstAndIncrement(-10, 5);
	LightScheduler_ScheduleTurnOn(4, EVERYDAY, 600);
	LightScheduler_Randomize(4, EVERYDAY, 600);
	setTimeTo(MONDAY, 600 - 10);
	LightScheduler_Wakeup();
	checkLightState(4, LIGHT_ON);
}
