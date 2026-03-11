#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <windows.h>
#include "clear_screen.h"

#define MAX_DEPARTMENT_LENGTH 1000
#define MAX_NAME_LENGTH 1000
struct Staff
{
    char department[MAX_DEPARTMENT_LENGTH];
    char name[MAX_NAME_LENGTH];
    int holidayTime;
};

#endif