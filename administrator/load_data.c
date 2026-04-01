#include "../head/administrator.h"
#include <stdio.h>

void loadDepartmentData()
{
    FILE *file = fopen("../data/all_apartment.csv", "r");
    if (file == NULL) {
        printf("无法打开部门数据文件！\n");
        return;
    }

    int departmentID;
    char departmentName[MAX_NAME_LENGTH];

    char buffer[1024];
    fgets(buffer, sizeof(buffer), file); // 跳过表头

    while (fgets(buffer, sizeof(buffer), file))
    {
        if (sscanf(buffer, "%d,%[^,\n]",
            &departmentID,
             departmentName) == 2)
        {
            addDepartmentNode(departmentID, departmentName);
        }
    }

    fclose(file);
    //system("cls");
    printf("部门数据加载成功！\n");
}

void loadEmployeeData()
{
    FILE *file = fopen("../data/all_staff.csv", "r");
    if (file == NULL) {
        printf("无法打开员工数据文件！\n");
        return;
    }

    int employeeID;
    char departmentName[MAX_NAME_LENGTH];
    char employeeName[MAX_NAME_LENGTH];
    char rolename[MAX_NAME_LENGTH];

    char buffer[1024];
    fgets(buffer, sizeof(buffer), file);

    while (fgets(buffer, sizeof(buffer), file))
    {
        if (sscanf(buffer, "%d,%[^,\n],%[^,\n],%[^,\n]",
            &employeeID,
            employeeName,
            departmentName,
            rolename) == 4)
        {
            addEmployeeNode(employeeID, departmentName, employeeName);
        }
    }

    fclose(file);
    //system("cls");
    printf("员工数据加载成功！\n");
}

void loadAttendanceData() {
    FILE *file = fopen("../data/check_in_record.csv", "r");
    if (file == NULL) {
        printf("无法打开打卡记录！\n");
        return;
    }

    char buffer[1024];
    fgets(buffer, sizeof(buffer), file);  // 跳过表头

    int employeeID;
    char checkTime[50];   // 打卡时间字符串
    char status[20];      // 正常/迟到/早退/下班
    int year, month, day, hour, minute, second;
    while (fgets(buffer, sizeof(buffer), file))
    {
        // 读取：员工ID、打卡时间、打卡状态
        
        if (sscanf(buffer, "%d,%*[^,],%*[^,],%d-%d-%d %d:%d:%d,%[^\n]",
            &employeeID,
            &year, &month, &day, &hour, &minute, &second,
            status) == 7)
        {
            // ==============================================
            // 在这里你可以直接用这三个变量：
            // employeeID  员工ID
            // checkTime   打卡时间（如 2026-03-19 08:26:00）
            // status      状态（正常/迟到/早退/下班）
            // ==============================================

            printf("ID:%d  时间:%d-%d-%d %d:%d:%d  状态:%s\n", employeeID, year, month, day, hour, minute, second, status);
            Employee *point = employeeHead->next;
            while (point != NULL) {
                if (point->employeeID == employeeID) {
                    // addClockNotingNode(point, year, month, day, hour, minute, second, status);
                    break;
                }
                point = point->next;
            }
        }
    }

    fclose(file);
}

void loadUserData()
{
    FILE *file = fopen("../data/userdata.csv", "r");
    if (file == NULL) {
        printf("无法打开用户数据文件！\n");
        return;
    }

    int id;
    char password[MAX_NAME_LENGTH];
    char name[MAX_NAME_LENGTH];
    char role[MAX_NAME_LENGTH];
    char account[MAX_NAME_LENGTH];
    int roleType;

    char buffer[1024];
    fgets(buffer, sizeof(buffer), file);

    while (fgets(buffer, sizeof(buffer), file))
    {
        if (sscanf(buffer, "%[^,\n],%[^,\n],%[^,\n],%[^,\n],%d,%d",
            role,
            account,
            password,
            name,
            &id,
            &roleType) == 6)
        {
            addUserNode(id, password, name, account, (RoleType)roleType);
        }
    }

    fclose(file);
    //system("cls");
    printf("用户数据加载成功！\n");
}

void loadHolidayData()
{
    FILE *file = fopen("../data/holidaydata.csv", "r");
    if (file == NULL) {
        printf("无法打开假期数据文件！\n");
        return;
    }

    int holidayID;
    char holidayName[MAX_NAME_LENGTH];
    int minimumTime;
    int maximumTime;

    char buffer[1024];
    fgets(buffer, sizeof(buffer), file);

    while (fgets(buffer, sizeof(buffer), file))
    {
        if (sscanf(buffer, "%d,%[^,\n],%d,%d",
            &holidayID,
            holidayName,
            &minimumTime,
            &maximumTime) == 4)
        {
            addHolidayNode(holidayID, minimumTime, maximumTime, holidayName);
        }
    }

    fclose(file);
    //system("cls");
    printf("假期数据加载成功！\n");
}

void loadEmployeeInfo()
{
    Employee *point = employeeHead->next;
    while (point != NULL) {
        GetEmployeeInfo(point);
        point = point->next;
    }
}

void loadData()
{
    initlist();
    loadDepartmentData();
    loadEmployeeData();
    loadUserData();
    loadHolidayData();
    loadAttendanceData();
    loadVacationRecord();
    loadEmployeeInfo();
    // system("cls");
    printf("数据加载成功！\n");
}