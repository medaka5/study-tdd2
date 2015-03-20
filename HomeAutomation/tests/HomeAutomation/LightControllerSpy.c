#include "LightControllerSpy.h"

static int lastId;
static int lastStatus;
void LightController_Create(void)
{
    lastId = LIGHT_ID_UNKNOWN;
    lastStatus = LIGHT_STATE_UNKNOWN;
}

void LightController_Destroy(void)
{
}

void LightController_On(int id) {
    lastId = id;
    lastStatus = LIGHT_ON;
}

void LightController_Off(int id) {
    lastId = id;
    lastStatus = LIGHT_OFF;
}

int LightControllerSpy_GetLastId(void) {
    return lastId;
}

int LightControllerSpy_GetLastState(void) {
    return lastStatus;
}

