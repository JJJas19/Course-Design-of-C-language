#include "../head/administrator.h"
#include <stdio.h>
#include <string.h>

void saveDepartmentData()
{
    FILE *file = fopen("../data/all_apartment.csv", "w");
    if (file == NULL) {
        printf("无法写入部门数据文件！\n");
        return;
    }

    fprintf(file, "部门ID,部门名称\n");

    Department *point = departmentHead->next;
    while (point != NULL)
    {
        fprintf(file, "%d,%s\n",
            point->departmentID,
            point->name);
        point = point->next;
    }

    fclose(file);
}

void saveEmployeeData()
{
    FILE *file = fopen("../data/all_staff.csv", "w");
    if (file == NULL) {
        printf("无法写入员工数据文件！\n");
        return;
    }

    fprintf(file, "人员ID,人员姓名,所属部门,职位\n");

    Employee *point = employeeHead->next;
    while (point != NULL)
    {
        fprintf(file, "%d,%s,%s,%s\n",
            point->employeeID,
            point->employeeName,
            point->departmentName,
            point->roleName);
        point = point->next;
    }

    fclose(file);
}

void saveUserData()
{
    FILE *file = fopen("../data/userdata.csv", "w");
    if (file == NULL) {
        printf("无法写入用户数据文件！\n");
        return;
    }

    fprintf(file, "身份,账号,密码,姓名,ID,角色类型,部门\n");

    User *point = userHead->next;
    while (point != NULL)
    {
        fprintf(file, "%s,%s,%s,%s,%d,%d,%s\n",
            point->role,
            point->account,
            point->password,
            point->name,
            point->id,
            point->roleType,
            point->department);
        point = point->next;
    }

    fclose(file);
}

void saveHolidayData()
{
    FILE *file = fopen("../data/holidaydata.csv", "w");
    if (file == NULL) {
        printf("无法写入假期数据文件！\n");
        return;
    }

    fprintf(file, "holidayID,holidayName,minTime,maxTime\n");

    HolidayType *point = holidayHead->next;
    while (point != NULL)
    {
        fprintf(file, "%d,%s,%d,%d\n",
            point->holidayID,
            point->name,
            point->minimumTime,
            point->maximumTime);
        point = point->next;
    }

    fclose(file);
}

void saveHolidayQuota()
{
    FILE *file = fopen("../data/holidayquotadata.csv", "w");
    if (file == NULL) {
        printf("无法写入假期配额文件！\n");
        return;
    }

    fprintf(file, "员工ID,员工姓名,假期类型ID,总共额度,已使用额度,剩余额度\n");

    Employee *emp = employeeHead->next;
    while (emp != NULL)
    {
        if (emp->holidayQuotaData == NULL) {
            emp = emp->next;
            continue;
        }
        EmployeeHolidayQuota *quota = emp->holidayQuotaData->next;

        while (quota != NULL)
        {
            fprintf(file, "%d,%s,%d,%d,%d,%d\n",
                quota->employeeID,
                emp->employeeName,
                quota->holidayTypeID,
                quota->totalQuota,
                quota->usedQuota,
                quota->remainingQuota);

            quota = quota->next;
        }

        emp = emp->next;
    }

    fclose(file);
}

void saveData() {
    printf("1: 开始保存用户数据\n");
    saveUserData();

    printf("2: 开始保存部门数据\n");
    saveDepartmentData();

    printf("3: 开始保存员工数据\n");
    saveEmployeeData();

    printf("4: 开始保存假期数据\n");
    saveHolidayData();

    printf("5: 开始保存额度数据\n");
    saveHolidayQuota();

    printf("saveData 完成\n");
}