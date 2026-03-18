#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "administrator.h"

Department *departmentHead = NULL;
void initDepartmentList()
{
    departmentHead = (Department*)malloc(sizeof(Department));
    departmentHead->next = NULL;
}

int addDepartmentNode(int departmentID, const char* departmentName)
{
    if (departmentHead == NULL) {
        initDepartmentList();
    }
    Department *newNode = (Department*)malloc(sizeof(Department));
    if (newNode == NULL) {
        printf("创建节点失败\n");
        return 0;
    }
    newNode->departmentID = departmentID;
    int size = strlen(departmentName);
    if (size > MAX_NAME_LENGTH) {
        printf("部门名称过长，请重新创建\n");
        free(newNode);
        return 0;
    }
    strcpy(newNode->name, departmentName);

    Department *point = departmentHead;
    while (point->next != NULL) {
        point = point->next;
    }
    point->next = newNode;

    printf("插入部门成功");
    return 1;
}

int removeDepartmentNode(int index) // 要删除第几个节点
{
    if (index == 0)
    {
        printf("输入编号非法\n");
        return 0;
    }
    int number = 0;
    Department *point = departmentHead;
    Department *preNode = point;
    while (point->next != NULL && number != index) {
        preNode = point;
        point = point->next;
        number ++;
    }
    if (number == index)
    {
        preNode->next = point->next;
        free(point);
        printf("删除成功\n");
        return 1;
    }
    else
    {
        printf("输入编号非法\n");
        return 0;
    }
}

int modifyDepartmentNode(int index)
{
    int number = 0;
    Department *point = departmentHead;
    while (point->next != NULL && number != index) {
        point = point->next;
        number ++;
    }
    if (number == index)
    {
        char name[MAX_NAME_LENGTH];
        printf("请输入部门名称: ");
        scanf("%s", name);
        while (strlen(name) > MAX_NAME_LENGTH) {
            printf("部门昵称过长，请重新输入: ");
            scanf("%s", name);
        }
        
        strcpy(point->name, name);
        return 1;
    }
    else
    {
        printf("输入编号非法\n");
        return 0;
    }
}

void freeDepartmentNode()
{
    Department *point = departmentHead;
    Department *preNode = point;
    while (point->next != NULL) {
        preNode = point;
        point = point->next;
        free(preNode);
    }
    free(point);
}

Employee *employeeHead = NULL;
void initEmployeeList()
{
    employeeHead = (Employee*)malloc(sizeof(Employee));
    employeeHead->next = NULL;
}

int addEmployeeNode(int employeeID, int departmentID, const char* employeeName)
{
    if (employeeHead == NULL) {
        initEmployeeList();
    }
    Employee *newNode = (Employee*)malloc(sizeof(Employee));
    if (newNode == NULL) {
        printf("创建节点失败\n");
        return 0;
    }
    newNode->departmentID = departmentID;
    newNode->employeeID = employeeID;
    int size = strlen(employeeName);
    if (size > MAX_NAME_LENGTH) {
        printf("部门名称过长，请重新创建\n");
        free(newNode);
        return 0;
    }
    strcpy(newNode->employeeName, employeeName);

    Employee *point = employeeHead;
    while (point->next != NULL) {
        point = point->next;
    }
    point->next = newNode;

    printf("插入部门成功");
    return 1;
}

int removeEmployeeNode(int index) // 要删除第几个节点
{
    if (index == 0)
    {
        printf("输入编号非法\n");
        return 0;
    }
    int number = 0;
    Employee *point = employeeHead;
    Employee *preNode = point;
    while (point->next != NULL && number != index) {
        preNode = point;
        point = point->next;
        number ++;
    }
    if (number == index)
    {
        preNode->next = point->next;
        free(point);
        printf("删除成功\n");
        return 1;
    }
    else
    {
        printf("输入编号非法\n");
        return 0;
    }
}

int modifyEmployeeNode(int index)
{
    int number = 0;
    Employee *point = employeeHead;
    while (point->next != NULL && number != index) {
        point = point->next;
        number ++;
    }
    if (number == index)
    {
        char name[MAX_NAME_LENGTH];
        printf("请输入员工名称: ");
        scanf("%s", name);
        while (strlen(name) > MAX_NAME_LENGTH) {
            printf("部门昵称过长，请重新输入: ");
            scanf("%s", name);
        }
        
        strcpy(point->employeeName, name);

        printf("请输入部门编号: ");
        int departmentID;
        scanf("%d", departmentID);
        point->departmentID = departmentID;

        return 1;
    }
    else
    {
        printf("输入编号非法\n");
        return 0;
    }
}

void freeEmployeeNode()
{
    Employee *point = employeeHead;
    Employee *preNode = point;
    while (point->next != NULL) {
        preNode = point;
        point = point->next;
        free(preNode);
    }
    free(point);
}

HolidayType *holidayHead = NULL;
void initHolidayList()
{
    holidayHead = (HolidayType*)malloc(sizeof(HolidayType));
    holidayHead->next = NULL;
}

int addHolidayNode(int holidayID, int maximumTime, int minimumTime, const char* name)
{
    if (holidayHead == NULL) {
        initHolidayList();
    }
    HolidayType *newNode = (HolidayType*)malloc(sizeof(HolidayType));
    if (newNode == NULL) {
        printf("创建节点失败\n");
        return 0;
    }
    newNode->holidayID = holidayID;
    newNode->maximumTime = maximumTime;
    newNode->minimumTime = minimumTime;
    int size = strlen(name);
    if (size > MAX_NAME_LENGTH) {
        printf("假期名称过长，请重新创建\n");
        free(newNode);
        return 0;
    }
    strcpy(newNode->name, name);

    HolidayType *point = holidayHead;
    while (point->next != NULL) {
        point = point->next;
    }
    point->next = newNode;

    printf("插入假期成功");
    return 1;
}

int removeHolidayNode(int index) // 要删除第几个节点
{
    if (index == 0)
    {
        printf("输入编号非法\n");
        return 0;
    }
    int number = 0;
    HolidayType *point = holidayHead;
    HolidayType *preNode = point;
    while (point->next != NULL && number != index) {
        preNode = point;
        point = point->next;
        number ++;
    }
    if (number == index)
    {
        preNode->next = point->next;
        free(point);
        printf("删除成功\n");
        return 1;
    }
    else
    {
        printf("输入编号非法\n");
        return 0;
    }
}

int modifyHolidayNode(int index)
{
    int number = 0;
    HolidayType *point = holidayHead;
    while (point->next != NULL && number != index) {
        point = point->next;
        number ++;
    }
    if (number == index)
    {
        char name[MAX_NAME_LENGTH];
        printf("请输入假期名称: ");
        scanf("%s", name);
        while (strlen(name) > MAX_NAME_LENGTH) {
            printf("假期昵称过长，请重新输入: ");
            scanf("%s", name);
        }
        
        strcpy(point->name, name);

        printf("请输入假期最短时间: ");
        int minimumTime;
        scanf("%d", &minimumTime);
        point->minimumTime = minimumTime;
        printf("请输入假期最长时间: ");
        int maximumTime;
        scanf("%d", &maximumTime);
        point->maximumTime = maximumTime;

        return 1;
    }
    else
    {
        printf("输入编号非法\n");
        return 0;
    }
}

void freeHolidayNode()
{
    HolidayType *point = holidayHead;
    HolidayType *preNode = point;
    while (point->next != NULL) {
        preNode = point;
        point = point->next;
        free(preNode);
    }
    free(point);
}

User *userHead = NULL;
void initUserList()
{
    userHead = (User*)malloc(sizeof(User));
    userHead->next = NULL;
}

int addUserNode(int id, const char* password, const char* name, RoleType roleType)
{
    if (userHead == NULL) {
        initUserList();
    }
    User *newNode = (User*)malloc(sizeof(User));
    if (newNode == NULL) {
        printf("创建节点失败\n");
        return 0;
    }
    newNode->id = id;
    strcpy(newNode->password, password);
    newNode->roleType = roleType;
    int size = strlen(name);
    if (size > MAX_NAME_LENGTH) {
        printf("用户名过长，请重新创建\n");
        free(newNode);
        return 0;
    }
    strcpy(newNode->name, name);

    User *point = userHead;
    while (point->next != NULL) {
        point = point->next;
    }
    point->next = newNode;

    printf("插入用户成功");
    return 1;
}

int removeUserNode(int index) // 要删除第几个节点
{
    if (index == 0)
    {
        printf("输入编号非法\n");
        return 0;
    }
    int number = 0;
    User *point = userHead;
    User *preNode = point;
    while (point->next != NULL && number != index) {
        preNode = point;
        point = point->next;
        number ++;
    }
    if (number == index)
    {
        preNode->next = point->next;
        free(point);
        printf("删除成功\n");
        return 1;
    }
    else
    {
        printf("输入编号非法\n");
        return 0;
    }
}

int modifyUserNode(int index)
{
    int number = 0;
    User *point = userHead;
    while (point->next != NULL && number != index) {
        point = point->next;
        number ++;
    }
    if (number == index)
    {
        char name[MAX_NAME_LENGTH];
        printf("请输入用户名: ");
        scanf("%s", name);
        while (strlen(name) > MAX_NAME_LENGTH) {
            printf("用户名过长，请重新输入: ");
            scanf("%s", name);
        }
        
        strcpy(point->name, name);

        char password[MAX_NAME_LENGTH];
        printf("请输入密码: ");
        scanf("%s", password);
        while (strlen(password) > MAX_NAME_LENGTH) {
            printf("密码过长，请重新输入: ");
            scanf("%s", password);
        }
        
        strcpy(point->password, password);

        printf("请输入角色编号(1-4): ");
        int roleType;
        scanf("%d", &roleType);
        if (roleType < 1 || roleType > 4) {
            printf("输入编号非法\n");
            return 0;
        }
        point->roleType = roleType;

        return 1;
    }
    else
    {
        printf("输入编号非法\n");
        return 0;
    }
}

void freeUserNode()
{
    User *point = userHead;
    User *preNode = point;
    while (point->next != NULL) {
        preNode = point;
        point = point->next;
        free(preNode);
    }
    free(point);
}

int setEmployeeDepartment(int employeeID, int departmentID)
{
    Employee *point = employeeHead;
    while (point != NULL) {
        if (point->employeeID == employeeID) {
            point->departmentID = departmentID;
            return 1;
        }
        point = point->next;
    }
    printf("未找到该员工\n");
    return 0;
}

int setHolidayTime(int holidayID, int minimumTime, int maximumTime)
{
    HolidayType *point = holidayHead;
    while (point != NULL) {
        if (point->holidayID == holidayID) {
            point->minimumTime = minimumTime;
            point->maximumTime = maximumTime;
            return 1;
        }
        point = point->next;
    }
    printf("未找到该假期\n");
    return 0;
}

void freeNode()
{
    freeDepartmentNode();
    freeEmployeeNode();
    freeHolidayNode();
    freeUserNode();
}

