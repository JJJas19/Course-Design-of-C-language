#include "../head/administrator.h"
#include <stdio.h>
#include <string.h>

void saveDepartmentData()
{
    FILE *file = fopen("../data/all_apartment.csv", "w");
    if (file == NULL) {
        printf("无法打开部门数据文件！\n");
        return;
    }

    fprintf(file, "departmentID,departmentName\n");

    Department *p = departmentHead;
    while (p != NULL) {
        fprintf(file, "%d,%s\n", p->departmentID, p->name);
        p = p->next;
    }

    fclose(file);
    printf("部门数据保存成功！\n");
}

void saveEmployeeData()
{
    FILE *file = fopen("../data/all_staff.csv", "w");
    if (file == NULL) {
        printf("无法打开员工数据文件！\n");
        return;
    }

    fprintf(file, "employeeID,employeeName,departmentName,rolename\n");

    Employee *p = employeeHead;
    char rolename[MAX_NAME_LENGTH];
    strcpy(rolename, "员工");
    while (p != NULL) {
        fprintf(file, "%d,%s,%s,%s\n",
                p->employeeID,
                p->employeeName,
                p->departmentName,
                rolename);
        p = p->next;
    }

    fclose(file);
    printf("员工数据保存成功！\n");
}

void saveUserData()
{
    FILE *file = fopen("../data/userdata.csv", "w");
    if (file == NULL) {
        printf("无法打开用户数据文件！\n");
        return;
    }

    fprintf(file, "role,account,password,name,id,roleType\n");

    User *p = userHead;
    while (p != NULL) {
        char role[MAX_NAME_LENGTH];
        if (p->roleType == 1) {
            strcpy(role, "管理员");
        } else if (p->roleType == 2) {
            strcpy(role, "部门经理");
        } else if (p->roleType == 3) {
            strcpy(role, "人事专员");
        } else if (p->roleType == 4) {
            strcpy(role, "员工");
        }
        fprintf(file, "%s,%s,%s,%s,%d,%d\n",
                role,
                p->account,
                p->password,
                p->name,
                p->id,
                p->roleType);
        p = p->next;
    }

    fclose(file);
    printf("用户数据保存成功！\n");
}

void saveHolidayData()
{
    FILE *file = fopen("../data/holidaydata.csv", "w");
    if (file == NULL) {
        printf("无法打开假期数据文件！\n");
        return;
    }

    fprintf(file, "holidayID,holidayName,minimumTime,maximumTime\n");

    HolidayType *p = holidayHead;
    while (p != NULL) {
        fprintf(file, "%d,%s,%d,%d\n",
                p->holidayID,
                p->name,
                p->minimumTime,
                p->maximumTime);
        p = p->next;
    }

    fclose(file);
    printf("假期数据保存成功！\n");
}

void saveData()
{
    saveDepartmentData();
    saveEmployeeData();
    saveUserData();
    saveHolidayData();
    system("cls");
    printf("所有数据保存成功！\n");
}