#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <windows.h>
#include "clear_screen.h"

#define MAX_NAME_LENGTH 1000

// 员工信息
typedef struct 
{
    int department_id;
    char name[MAX_NAME_LENGTH];
    int holidayTime;
} Staff;

// 部门信息
typedef struct
{
    int department_id;
    char name[MAX_NAME_LENGTH];
} Department;

// 时间结构体
typedef struct 
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
} Time;

// 假期类型
typedef struct
{
    int holiday_id;
    char name[MAX_NAME_LENGTH]
} HolidayType;

// 假期状态
typedef enum
{
    pending = 1, // 待审批
    approved, // 通过
    rejected // 拒绝
} HolidayStatus;

// 角色类型
typedef enum
{
    administrator = 1,
    manager,
    staff,
    humanresource
} RoleType;



#endif