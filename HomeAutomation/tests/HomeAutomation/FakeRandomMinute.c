#include "FakeRandomMinute.h"

static int sFirst;
static int sIncrement;
static int sNext;

void FakeRandomMinute_SetFirstAndIncrement(int first, int increment) {
	sFirst = first;
	sIncrement = increment;
	sNext = first;
}


int FakeRandomMinute_Get(void) {
	int ret = sNext;
	sNext += sIncrement;
	return ret;
}
