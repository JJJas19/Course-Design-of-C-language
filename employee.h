#ifndef EMPLOY_H
#define EMPLOY_H

typedef struct ClockNoting {
	int numberOfDays;
	char clockInTime[6];
	char clockOutTime[6];
	struct ClockNoting* next;
}ClockNoting;

#endif
