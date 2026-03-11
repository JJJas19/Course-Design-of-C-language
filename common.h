#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <windows.h>

#define MAX_DEPARTMENT_LENGTH 1000
struct Staff
{
    char department[MAX_DEPARTMENT_LENGTH];
    int holidayTime;
};

#endif