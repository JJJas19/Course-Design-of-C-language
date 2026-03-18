#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <windows.h>

#define MAX_NAME_LENGTH 1000

// 时间结构体
typedef struct
{
    int hour;
    int minute;
} Time;

// 日期结构体
typedef struct 
{
    int year;
    int month;
    int day;
} Date;

// 打卡类型
typedef struct ClockNoting
{
    int numberOfDays;
    Date clockDate;
    Time clockInTime;
    Time clockOutTime;
    struct ClockNoting *next;
} ClockNoting;

// 假期配额类型
typedef struct EmployeeHolidayQuota
{
    int employeeID;
    int holidayTypeID;
    int totalQuota;
    int usedQuota;
    int remainingQuota;
    struct EmployeeHolidayQuota *next;
} EmployeeHolidayQuota;

// 角色类型
typedef enum
{
    administrator = 0,
    manager,
    staff,
    humanresource
} RoleType;

// 用户类型
typedef struct
{
    int id;
    char password[MAX_NAME_LENGTH];
    char name[MAX_NAME_LENGTH];
    RoleType roleType;
    User *next;
} User;

// 员工类型
typedef struct
{
    char employeeName[MAX_NAME_LENGTH];
    int employeeID;
    int departmentID;
    Employee *next;
    ClockNoting* clockNotingData;
    EmployeeHolidayQuota* holidayQuotaData;
} Employee;

// 部门信息
typedef struct
{
    int departmentID;
    char name[MAX_NAME_LENGTH];
    Department *next;
} Department;

// 假期类型
typedef struct
{
    int holidayID;
    char name[MAX_NAME_LENGTH];
    int minimumTime;
    int maximumTime;
    HolidayType *next;
} HolidayType;

// 假期状态
typedef enum
{
    pending = 1, // 待审批
    approved,    // 通过
    rejected     // 驳回
} HolidayStatus;

#endif