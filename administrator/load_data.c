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
    system("cls");
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
    system("cls");
    printf("员工数据加载成功！\n");
}

void loadUserData()
{
    FILE *file = fopen("../data/all_user.csv", "r");
    if (file == NULL) {
        printf("无法打开用户数据文件！\n");
        return;
    }

    int id;
    char password[MAX_NAME_LENGTH];
    char name[MAX_NAME_LENGTH];
    int roleType;

    char buffer[1024];
    fgets(buffer, sizeof(buffer), file);

    while (fgets(buffer, sizeof(buffer), file))
    {
        if (sscanf(buffer, "%d,%[^,\n],%[^,\n],%d",
            &id,
            name,
            password,
            &roleType) == 4)
        {
            addUserNode(id, password, name, (RoleType)roleType);
        }
    }

    fclose(file);
    system("cls");
    printf("用户数据加载成功！\n");
}

void loadData()
{
    initlist();
    loadDepartmentData();
    loadEmployeeData();
}