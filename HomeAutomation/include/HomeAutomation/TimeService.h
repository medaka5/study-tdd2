
#ifndef TIME_SERVICE_H
#define TIME_SERVICE_H
enum {
    TIME_UNKNOWN = -1,
};
enum {
    NONE = -1,
    MONDAY = 1,
    TUESDAY = 2,
    WEDNESDAY = 3,
    THURSDAY = 4,
    FRIDAY = 5,
    SATURDAY = 6,
    SUNDAY = 7,
    EVERYDAY = 10,
    WEEKDAY ,
    WEEKEND
};
struct Time_t {
    int minuteOfDay;
    int dayOfWeek;
};
typedef struct Time_t Time;

extern void TimeService_GetTime(Time *time);

#endif // TIME_SERVICE_H
