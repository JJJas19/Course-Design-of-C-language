#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include "../head/menu.h"
#include "../head/common.h"
#include "../head/hr_specialist.h"

void hr_menu(Employee* employeeHead)
{
    int i = 1;
    while (i)
    {
        printf("**********欢迎使用HR人力资源管理系统**********\n");
        printf("********************************************\n");
        printf("**********1.考勤数据打印      ***************\n");
        printf("**********2.假期额度打印      ***************\n");
        printf("**********3.个人密码维护      ***************\n");
        printf("**********4.员工薪酬打印      ***************\n");
        printf("**********5.考勤数据查询      ***************\n");
        printf("**********6.假期额度查询      ***************\n");
        printf("**********7.员工薪酬查询      ***************\n");
        printf("**********8.退出             ***************\n");
        printf("********************************************\n");
        int choose;
        printf("请选择您要做的操作：\n");
        scanf("%d", &choose);
        switch (choose)
        {
        case 1:
            query_attendance(employeeHead);
            break;
        case 2:
            query_leave_quota(employeeHead);
            break;
        case 3:
            modify_password();
            break;
        case 4:
            attendance_to_salary(employeeHead);
            break;
        case 5:
            search_attendance(employeeHead);
            break;
        case 6:
            query_leave_quota_search(employeeHead);
            break;
        case 7:
            query_salary(employeeHead);
            break;
        default:
            printf("退出成功");
            i = 0;
            break;
        }
    }
}
void query_attendance(Employee *employeeHead)
{
    printf("===== 考勤数据打印 =====\n");
    FILE *fp = fopen("../data/Attendance_data.csv", "w");
    if (fp == NULL)
    {
        perror("打开CSV文件失败");
        return;
    }
    fprintf(fp, "%s,%s,%s,%s,%s\n", "员工ID", "员工姓名", "打卡总日期", "员工早上未打卡日期", "员工下午未打卡日期");
    printf("%s,%s,%s,%s,%s\n", "员工ID", "员工姓名", "打卡总日期", "员工早上未打卡日期", "员工下午未打卡日期");
    Employee *point = employeeHead->next;
    while (point != NULL)
    {
        int lastdate;
        ClockNoting *clockValues = point->clockNotingData;
        char morningAbsentDates[1000] = "";
        char afternoonAbsentDates[1000] = "";
        char totalDate[1000] = "";
        while (clockValues != NULL)
        {
            sprintf(totalDate, "%d-%02d-%02d",
                    clockValues->clockDate.year,
                    clockValues->clockDate.month,
                    clockValues->clockDate.day);
            if ((clockValues->isAbsent == 0) && (clockValues->clockInTime.isClocking == 0))
            {
                if (strlen(morningAbsentDates) > 0)
                {
                    strcat(morningAbsentDates, ";");
                }
                strcat(morningAbsentDates, totalDate);
            }
            if (clockValues->isAbsent == 0 && clockValues->clockOutTime.isClocking == 0)
            {
                if (strlen(afternoonAbsentDates) > 0)
                {
                    strcat(afternoonAbsentDates, ";");
                }
                strcat(afternoonAbsentDates, totalDate);
            }
            lastdate = point->numberOfDays;
            clockValues = clockValues->next;
        }
        const char *morningStr = strlen(morningAbsentDates) == 0 ? "无" : morningAbsentDates;
        const char *afternoonStr = strlen(afternoonAbsentDates) == 0 ? "无" : afternoonAbsentDates;

        fprintf(fp, "%d,%s,%d,%s,%s\n", point->employeeID, point->employeeName, lastdate, morningStr, afternoonStr);
        printf("%-8d\t%-10s\t%-10d\t%-20s\t%-20s\n", point->employeeID, point->employeeName, lastdate, morningStr, afternoonStr);
        point = point->next;
    }
    fclose(fp);
    printf("\n考勤数据已导出到 Attendance_data.csv\n");

} // 考勤数据打印，打印在Attendance_data.csv

void query_leave_quota(Employee *employeeHead)
{
    printf("===== 假期额度数据打印 =====\n");
    FILE *fp = fopen("../data/Holiday_quota.csv", "w");
    if (fp == NULL)
    {
        perror("打开CSV文件失败");
        return;
    }
    fprintf(fp, "%s,%s,%s,%s,%s,%s\n", "员工ID", "员工姓名", "假期类型ID", "总共额度", "已使用额度", "剩余额度");
    printf("%s,%s,%s,%s,%s,%s\n", "员工ID", "员工姓名","假期类型ID", "总共额度", "已使用额度", "剩余额度");
    Employee *point = employeeHead->next;
    while (point != NULL)
    {
        EmployeeHolidayQuota *HolidayQuota = point->holidayQuotaData;
        while (HolidayQuota != NULL)
        {
            fprintf(fp, "%d,%s,%d,%d,%d,%d\n", HolidayQuota->employeeID, point->employeeName, HolidayQuota->holidayTypeID, HolidayQuota->totalQuota, HolidayQuota->usedQuota, HolidayQuota->remainingQuota);
            printf("%d,%s,%d,%d,%d,%d\n", HolidayQuota->employeeID, point->employeeName, HolidayQuota->holidayTypeID, HolidayQuota->totalQuota, HolidayQuota->usedQuota, HolidayQuota->remainingQuota);
            HolidayQuota = HolidayQuota->next;
        }
        point = point->next;
    }
    fclose(fp);
    printf("\n假期额度数据已导出到 Holiday_quota.csv\n");
} // 假期额度打印，打印在Holiday_quota.csv中

void attendance_to_salary(Employee *employeeHead)
{
    printf("===== 工资数据打印 =====\n");
    printf("员工ID   员工姓名   员工工资\n");
    Employee *employeenode = employeeHead->next;
    FILE *fp = fopen("../data/salary.csv", "w");
    if (fp == NULL)
    {
        perror("打开CSV文件失败");
        return;
    }
    fprintf(fp, "%s %s %s\n", "员工ID", "员工姓名", "员工工资");
    while (employeenode != NULL)
    {
        int data[13] = {0};
        int holidaypunish = 0;
        int clockpunish = 0;
        int prize = 0;
        EmployeeHolidayQuota *holidayquotanode = employeenode->holidayQuotaData;
        ClockNoting *clocknode = employeenode->clockNotingData;
        while (holidayquotanode != NULL)
        {
            if (holidayquotanode->usedQuota > holidayquotanode->totalQuota)
            {
                holidaypunish += (holidayquotanode->usedQuota - holidayquotanode->totalQuota);
            }
            holidayquotanode = holidayquotanode->next;
        }
        while (clocknode != NULL)
        {
            int i = clocknode->clockDate.month;
            if (clocknode->clockInTime.isClocking == 1 && clocknode->clockOutTime.isClocking == 1)
            {
                data[i]++;
            }
            clocknode = clocknode->next;
        }
        for (int i = 1; i < 13; i++)
        {
            if (data[i] >= 27)
            {
                prize = 500;
            }
            else if (data[i] <= 20)
            {
                clockpunish += (20 - data[i]);
            }
        }
        employeenode->salary = 5000 + prize - 100 * holidaypunish - 100 * clockpunish;
        printf("%10d %10s %10d\n", employeenode->employeeID, employeenode->employeeName, employeenode->salary);
        // 将工资信息存入到表中
        fprintf(fp, "%d %s %d\n", employeenode->employeeID, employeenode->employeeName, employeenode->salary);
        employeenode = employeenode->next;
    }
    fclose(fp);
    printf("\n薪酬数据已导出到 salary.csv\n");

} // 考勤对接薪酬，打印在salary.csv中

// 考勤数据查询 - 支持按员工ID 或 员工姓名查询
void search_attendance(Employee *employeeHead)
{
    int choice;
    printf("===== 考勤数据查询 =====\n");
    printf("1. 按员工ID查询\n");
    printf("2. 按员工姓名查询\n");
    printf("请选择查询方式：");
    scanf("%d", &choice);
    getchar(); // 吸收回车，避免读取姓名出错

    Employee *point = employeeHead->next;
    int found = 0; // 标记是否找到员工

    if (choice == 1)
    {
        int searchID;
        printf("请输入要查询的员工ID：");
        scanf("%d", &searchID);

        // 按ID遍历查找
        while (point != NULL)
        {
            if (point->employeeID == searchID)
            {
                found = 1;
                break;
            }
            point = point->next;
        }
    }
    else if (choice == 2)
    {
        char searchName[50];
        printf("请输入要查询的员工姓名：");
        scanf("%s", searchName);
        //按姓名遍历查找
        while (point != NULL)
        {
            if (strcmp(point->employeeName, searchName) == 0)
            {
                found = 1;
                break;
            }
            point = point->next;
        }
    }
    else
    {
        printf("输入错误！\n");
        return;
    }
    if (!found)
    {
        printf("未查询到该员工信息！\n");
        return;
    }
    printf("\n===== 【%s - ID:%d】考勤汇总信息 =====\n", point->employeeName, point->employeeID);
    printf("%-8s\t%-10s\t%-10s\t%-20s\t%-20s\n",
           "员工ID", "员工姓名", "总天数", "早上未打卡", "下午未打卡");

    ClockNoting *clockValues = point->clockNotingData;
    char morningAbsentDates[1000] = "";
    char afternoonAbsentDates[1000] = "";
    char totalDate[50] = "";
    int lastdate = 0;

    // 遍历考勤记录，统计未打卡日期
    while (clockValues != NULL)
    {
        sprintf(totalDate, "%d-%02d-%02d",
                clockValues->clockDate.year,
                clockValues->clockDate.month,
                clockValues->clockDate.day);
        // 早上未打卡
        if (clockValues->isAbsent == 0 && clockValues->clockInTime.isClocking == 0)
        {
            if (strlen(morningAbsentDates) > 0)
                strcat(morningAbsentDates, ";");
            strcat(morningAbsentDates, totalDate);
        }
        // 下午未打卡
        if (clockValues->isAbsent == 0 && clockValues->clockOutTime.isClocking == 0)
        {
            if (strlen(afternoonAbsentDates) > 0)
                strcat(afternoonAbsentDates, ";");
            strcat(afternoonAbsentDates, totalDate);
        }

        lastdate = point->numberOfDays;
        clockValues = clockValues->next;
    }
    const char *morningStr = strlen(morningAbsentDates) == 0 ? "无" : morningAbsentDates;
    const char *afternoonStr = strlen(afternoonAbsentDates) == 0 ? "无" : afternoonAbsentDates;
    printf("%-8d\t%-10s\t%-10d\t%-20s\t%-20s\n",
           point->employeeID,
           point->employeeName,
           lastdate,
           morningStr,
           afternoonStr);
} // 考勤数据查询
void query_leave_quota_search(Employee *employeeHead)
{
    int choice;
    printf("===== 假期额度查询 =====\n");
    printf("1. 按员工ID查询\n");
    printf("2. 按员工姓名查询\n");
    printf("请选择查询方式：");
    scanf("%d", &choice);
    getchar();

    int searchID = 0;
    char searchName[50] = "";
    Employee *point = employeeHead->next;
    int found = 0;
    if (choice == 1)
    {
        printf("请输入要查询的员工ID：");
        scanf("%d", &searchID);
    }
    else if (choice == 2)
    {
        printf("请输入要查询的员工姓名：");
        scanf("%s", searchName);
    }
    else
    {
        printf("输入错误！\n");
        return;
    }
    while (point != NULL)
    {
        int match = 0;
        if (choice == 1 && point->employeeID == searchID)
            match = 1;
        if (choice == 2 && strcmp(point->employeeName, searchName) == 0)
            match = 1;

        if (match)
        {
            found = 1;
            printf("\n===== 员工【%s - ID:%d】假期额度 =====\n", point->employeeName, point->employeeID);
            printf("%-10s\t%-10s\t%-12s\t%-12s\t%-12s\n",
                   "假期类型ID", "总共额度", "已使用额度", "剩余额度", "员工姓名");
            EmployeeHolidayQuota *HolidayQuota = point->holidayQuotaData;
            while (HolidayQuota != NULL)
            {
                printf("%-10d\t%-12d\t%-12d\t%-12d\t%-10s\n",
                       HolidayQuota->holidayTypeID,
                       HolidayQuota->totalQuota,
                       HolidayQuota->usedQuota,
                       HolidayQuota->remainingQuota,
                       point->employeeName);
                HolidayQuota = HolidayQuota->next;
            }
            break;
        }
        point = point->next;
    }

    if (!found)
    {
        printf("未查询到该员工的假期额度信息！\n");
    }
} // 假期额度查询
void query_salary(Employee *employeeHead)
{
    printf("===== 薪资查询 =====\n");
    printf("1.按员工ID查询\n");
    printf("2.按员工姓名查询\n");
    printf("请选择需要查询的方式： ");
    int choose;
    scanf("%d", &choose);
    getchar();

    int search_id = 0;
    char search_name[50];
    Employee *employeenode = employeeHead->next;
    int found = 0;

    if (choose == 1)
    {
        printf("请输入要查询的员工id：\n");
        scanf("%d", &search_id);
    }
    else if (choose == 2)
    {
        printf("请输入要查询的员工姓名：\n");
        scanf("%s", search_name);
    }
    else
    {
        printf("输入错误！\n");
        return;
    }
    while (employeenode != NULL)
    {
        int match = 0;

        if (choose == 1 && employeenode->employeeID == search_id)
        {
            match = 1;
        }
        if (choose == 2 && strcmp(search_name, employeenode->employeeName) == 0)
        {
            match = 1;
        }

        if (match)
        {
            found = 1;
            break;
        }
        employeenode = employeenode->next;
    }
    if (found == 1)
    {
        printf("\n===== 员工【%s - ID:%d】薪资 =====\n", employeenode->employeeName, employeenode->employeeID);
        printf("%-10s\t%-10s\t%-10s\n", "员工ID", "员工姓名", "员工薪资");
        printf("%-10d\t%-10s\t%-10d\n", employeenode->employeeID, employeenode->employeeName, employeenode->salary);
    }
    else
    {
        printf("未查询到该员工的薪资信息！\n");
    }
}//薪资查询