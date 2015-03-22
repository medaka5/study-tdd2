
enum {
	MAX_EVENT=128,
};
enum {
	LS_OK = 0,
	LS_TOO_MANY_EVENTS,
	LS_OUT_OF_BOUNDS
};
extern void LightScheduler_Wakeup(void);
extern void LightScheduler_Create(void);
extern void LightScheduler_Destroy(void);
extern int LightScheduler_ScheduleTurnOn(int id, int day, int minuteOfDay);
extern int LightScheduler_ScheduleTurnOff(int id, int day, int minuteOfDay);
extern void LightScheduler_ScheduleRemove(int id, int day, int minuteOfDay);

