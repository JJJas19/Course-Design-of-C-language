#ifndef COMMON_H
#define COMMON_H

#define MAX_DEPARTMENT_LENGTH 1000
#define MAX_NAME_LENGTH 1000
struct Staff
{
    char department[MAX_DEPARTMENT_LENGTH];
    char name[MAX_NAME_LENGTH];
    int holidayTime;
};

#endif 