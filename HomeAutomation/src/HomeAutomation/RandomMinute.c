#include "RandomMinute.h"

static int bound = 0;
void RandomMinute_Create(int _bound) {
	bound = _bound;

}
static int RandomMinute_GetImpl(void) {
	return bound  - rand() % (bound * 2 + 1);
}
int (*RandomMinute_Get)(void) = RandomMinute_GetImpl;



