
#include "CppUTest/TestHarness.h"
#include <string.h>
extern "C" {
#include "RandomMinute.h"
}
enum {BOUND = 30};
TEST_GROUP(RandomMinute)
{
	int minute;
	void setup()
	{
		RandomMinute_Create(BOUND);
		srand(1);
	}
	void AssertMinuteIsInRange()
	{
		if(minute < -BOUND ||  minute > BOUND) {
			printf("bad minute value: %d¥n", minute);
			FAIL("Minute out of range");
		}
	}
};

TEST(RandomMinute, GetIsInRange)
{
	for (int i = 0; i < 100; i++) {
		minute = RandomMinute_Get();
		AssertMinuteIsInRange();
	}
}

TEST(RandomMinute, AllVluesPossible)
{
	int hit[2 * BOUND + 1];
	memset(hit, 0, sizeof(hit));
	int i;
	for (i = 0; i < 300; i++){
		minute = RandomMinute_Get();
		AssertMinuteIsInRange();
		hit[minute + BOUND]++;
	}

	for(i = 0; i < 2 * BOUND; i++){
		CHECK(hit[i] > 0);
	}
}



