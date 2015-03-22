#include "LightControllerSpy.h"

static int lastId;
static int lastStatus;
static int light_State[LIGHTCONTROLLER_MAX_ID] ;
void LightController_Create(void)
{
    lastId = LIGHT_ID_UNKNOWN;
    lastStatus = LIGHT_STATE_UNKNOWN;
    for(unsigned int i = 0; i < LIGHTCONTROLLER_MAX_ID; i++) {
    	light_State[i] = LIGHT_ID_UNKNOWN;
    }
}

void LightController_Destroy(void)
{
}

void LightController_On(int id) {
    lastId = id;
    lastStatus = LIGHT_ON;
    light_State[id] = LIGHT_ON;
}

void LightController_Off(int id) {
    lastId = id;
    lastStatus = LIGHT_OFF;
    light_State[id] = LIGHT_OFF;
}

int LightControllerSpy_GetLastId(void) {
    return lastId;
}

int LightControllerSpy_GetLastState(void) {
    return lastStatus;
}

int LightControllerSpy_GetLightState(int id) {
	return light_State[id];
}

