#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include "menu.h"
#include "common.h"
#include "administrator.h"

void hr_menu()
{
    int i = 1;
    while (i)
    {
        printf("**********欢迎使用HR人力资源管理系统**********\n");
        printf("********************************************\n");
        printf("**********1.考勤数据查询      ***************\n");
        printf("**********2.假期额度查询      ***************\n");
        printf("**********3.个人密码维护      ***************\n");
        printf("**********4.考勤对接薪酬      ***************\n");
        printf("**********5.薪酬发放系统      ***************\n");
        printf("**********6.退出             ***************\n");
        printf("********************************************\n");
        int choose;
        printf("请选择您要做的操作：\n");
        scanf("%d", &choose);
        switch (choose)
        {
        case 1:

            break;
        case 2:

            break;
        case 3:
            modify_password();
            break;
        case 4:

            break;
        case 5:

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
    printf("===== 考勤数据查询 =====\n");
    FILE *fp = fopen("Attendance_data.csv", "w");
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
            lastdate = clockValues->numberOfDays;
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

} // 考勤数据查询

void query_leave_quota(Employee *employeeHead)
{
    printf("===== 假期额度数据查询 =====\n");
    FILE *fp = fopen("Holiday_quota.csv", "w");
    if (fp == NULL)
    {
        perror("打开CSV文件失败");
        return;
    }
    fprintf(fp, "%s,%s,%s,%s,%s,%s\n", "员工ID", "员工姓名", "假期类型ID", "总共额度", "已使用额度", "剩余额度");
    printf("%s,%s,%s,%s,%s,%s\n", "员工ID", "假期类型ID", "总共额度", "已使用额度", "剩余额度");
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
} // 假期额度查询

void attendance_to_salary(Employee *employeeHead)
{
    printf("===== 工资数据查询 =====\n");
    printf("员工ID   员工姓名   员工工资");
    Employee *employeenode = employeeHead->next;
    FILE *fp = fopen("salary.csv", "w");
    if (fp == NULL)
    {
        perror("打开CSV文件失败");
        return;
    }
    fprintf(fp, "%10s %10s %10s", "员工ID", "员工姓名", "员工工资");
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
        for (int i = 0; i < 12; i++)
        {
            if (data[i] >= 27)
            {
                prize = 500;
            }
            else if (data[i] <= 20)
            {
                clockpunish += (data[i] - 20);
            }
        }
        employeenode->salary = 5000 + prize - 100 * holidaypunish - 100 * clockpunish;
        printf("%10d %10s %10d", employeenode->employeeID, employeenode->employeeName, employeenode->salary);
        // 将工资信息存入到表中
        fprintf(fp, "%10d %10s %10d", employeenode->employeeID, employeenode->employeeName, employeenode->salary);
    }
    fclose(fp);

} // 考勤对接薪酬

void salary_payment()
{
    
} // 薪酬发放系统
