#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../head/administrator.h"

Department *departmentHead = NULL;
void initDepartmentList()
{
    departmentHead = (Department*)malloc(sizeof(Department));
    if (departmentHead == NULL) {
        printf("部门链表初始化失败\n");
        exit(1);
    }
    memset(departmentHead, 0, sizeof(Department));
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
    memset(newNode, 0, sizeof(Department));
    newNode->next = NULL;

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

    printf("插入部门成功\n");
    return 1;
}

int removeDepartmentNode(int index) // 要删除第几个节点
{
    if (index == 0)
    {
        printf("输入序号非法\n");
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
        printf("输入序号非法\n");
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
        printf("输入序号非法\n");
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
    if (employeeHead == NULL) {
        printf("员工链表初始化失败\n");
        exit(1);
    }
    memset(employeeHead, 0, sizeof(Employee));
    employeeHead->next = NULL;
    employeeHead->holidayQuotaData = NULL;
    employeeHead->clockNotingData = NULL;
}

int addEmployeeNode(int employeeID, const char* departmentName, const char* employeeName, const char* role)
{
    if (employeeHead == NULL) {
        initEmployeeList();
    }
    Employee *newNode = (Employee*)malloc(sizeof(Employee));
    if (newNode == NULL) {
        printf("创建节点失败\n");
        return 0;
    }
    memset(newNode, 0, sizeof(Employee));
    newNode->next = NULL;

    newNode->employeeID = employeeID;
    int size = strlen(employeeName);
    if (size > MAX_NAME_LENGTH) {
        printf("员工名称过长，请重新创建\n");
        free(newNode);
        return 0;
    }
    size = strlen(departmentName);
    if (size > MAX_NAME_LENGTH) {
        printf("部门名称过长，请重新创建\n");
        free(newNode);
        return 0;
    }
    size = strlen(role);
    if (size > MAX_NAME_LENGTH) {
        printf("角色名称过长，请重新创建\n");
        free(newNode);
        return 0;
    }
    strcpy(newNode->employeeName, employeeName);
    strcpy(newNode->departmentName, departmentName);
    strcpy(newNode->roleName, role);
    Employee *point = employeeHead;
    while (point->next != NULL) {
        point = point->next;
    }
    point->next = newNode;

    printf("插入员工成功\n");
    return 1;
}

int removeEmployeeNode(int index) // 要删除第几个节点
{
    if (index == 0)
    {
        printf("输入序号非法\n");
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
        printf("输入序号非法\n");
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

        printf("请输入部门名称: ");
        char departmentName[MAX_NAME_LENGTH];
        scanf("%s", departmentName);
        while (strlen(departmentName) > MAX_NAME_LENGTH) {
            printf("部门名称过长，请重新输入: ");
            scanf("%s", departmentName);
        }
        strcpy(point->departmentName, departmentName);

        return 1;
    }
    else
    {
        printf("输入序号非法\n");
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
    if (holidayHead == NULL) {
        printf("假期链表初始化失败\n");
        exit(1);
    }
    memset(holidayHead, 0, sizeof(HolidayType));
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
    memset(newNode, 0, sizeof(HolidayType));
    newNode->next = NULL;

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

    printf("插入假期成功\n");
    return 1;
}

int removeHolidayNode(int index) // 要删除第几个节点
{
    if (index == 0)
    {
        printf("输入序号非法\n");
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
        printf("输入序号非法\n");
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
        printf("输入序号非法\n");
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
    if (userHead == NULL) {
        printf("用户链表初始化失败\n");
        exit(1);
    }
    memset(userHead, 0, sizeof(User));
    userHead->next = NULL;
}

int addUserNode(int id, const char* password, const char* name, const char* account, RoleType roleType, const char* department, const char* role)
{
    if (userHead == NULL) {
        initUserList();
    }
    User *newNode = (User*)malloc(sizeof(User));
    if (newNode == NULL) {
        printf("创建节点失败\n");
        return 0;
    }
    memset(newNode, 0, sizeof(User));
    newNode->next = NULL;

    int size = strlen(account);
    if (size > MAX_NAME_LENGTH) {
        printf("账号过长，请重新创建\n");
        free(newNode);
        return 0;
    }
    size = strlen(password);
    if (size > MAX_NAME_LENGTH) {
        printf("密码过长，请重新创建\n");
        free(newNode);
        return 0;
    }
    strcpy(newNode->name, name);
    strcpy(newNode->account, account);
    strcpy(newNode->password, password);
    strcpy(newNode->department, department);
    strcpy(newNode->role, role);
    newNode->id = id;
    newNode->roleType = roleType;

    User *point = userHead;
    while (point->next != NULL) {
        point = point->next;
    }
    point->next = newNode;

    printf("插入用户成功\n");
    return 1;
}

int removeUserNode(int index) // 要删除第几个节点
{
    if (index == 0)
    {
        printf("输入序号非法\n");
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
        printf("输入序号非法\n");
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
        printf("请输入用户身份: ");
        char role[MAX_NAME_LENGTH];
        scanf("%s", role);
        while (strlen(role) > MAX_NAME_LENGTH) {
            printf("用户身份过长，请重新输入: ");
            scanf("%s", role);
        }
        strcpy(point->role, role);

        printf("请输入用户ID: ");
        int id;
        scanf("%d", &id);
        point->id = id;

        char account[MAX_NAME_LENGTH];
        printf("请输入账号: ");
        scanf("%s", account);
        while (strlen(account) > MAX_NAME_LENGTH) {
            printf("账号过长，请重新输入: ");
            scanf("%s", account);
        }
        strcpy(point->account, account);

        char password[MAX_NAME_LENGTH];
        printf("请输入密码: ");
        scanf("%s", password);
        while (strlen(password) > MAX_NAME_LENGTH) {
            printf("密码过长，请重新输入: ");
            scanf("%s", password);
        }
        strcpy(point->password, password);       

        char name[MAX_NAME_LENGTH];
        printf("请输入姓名: ");
        scanf("%s", name);
        while (strlen(name) > MAX_NAME_LENGTH) {
            printf("姓名过长，请重新输入: ");
            scanf("%s", name);
        }
        strcpy(point->name, name);

        printf("请输入角色编号(1-4): ");
        int roleType;
        scanf("%d", &roleType);
        if (roleType < 1 || roleType > 4) {
            printf("输入编号非法\n");
            return 0;
        }

        printf("请输入部门名称: ");
        char department[MAX_NAME_LENGTH];
        scanf("%s", department);
        while (strlen(department) > MAX_NAME_LENGTH) {
            printf("部门名称过长，请重新输入: ");
            scanf("%s", department);
        }
        strcpy(point->department, department);

        point->roleType = (RoleType)roleType;

        return 1;
    }
    else
    {
        printf("输入序号非法\n");
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

void initHolidayQuota()
{
    Employee *employeepoint = employeeHead;
    while (employeepoint->next != NULL) {
        HolidayType *holidayPoint = holidayHead;
        employeepoint = employeepoint->next;
        employeepoint->holidayQuotaData = NULL;
        while (holidayPoint->next != NULL) {
            holidayPoint = holidayPoint->next;
            EmployeeHolidayQuota *newNode = (EmployeeHolidayQuota*)malloc(sizeof(EmployeeHolidayQuota));
            memset(newNode, 0, sizeof(EmployeeHolidayQuota));
            newNode->next = NULL;

            newNode->employeeID = employeepoint->employeeID;
            newNode->holidayTypeID = holidayPoint->holidayID;
            newNode->totalQuota = 0;
            newNode->usedQuota = 0;
            newNode->remainingQuota = 0;
            newNode->next = employeepoint->holidayQuotaData;
            employeepoint->holidayQuotaData = newNode;
        }
    }
}

int setEmployeeHolidayQuota(int employeeID, int holidayTypeID, int totalQuota)
{
    Employee *employeepoint = employeeHead;
    while (employeepoint->next != NULL) {
        employeepoint = employeepoint->next;
        if (employeepoint->employeeID == employeeID) {
            EmployeeHolidayQuota *holidayQuotaPoint = employeepoint->holidayQuotaData;
            while (holidayQuotaPoint != NULL) {
                if (holidayQuotaPoint->holidayTypeID == holidayTypeID) {
                    holidayQuotaPoint->totalQuota = totalQuota;
                    holidayQuotaPoint->remainingQuota = totalQuota - holidayQuotaPoint->usedQuota;
                    return 1;
                }
                holidayQuotaPoint = holidayQuotaPoint->next;
            }
        }
    }
    printf("未找到该员工或假期类型\n");
    return 0;
}

void freeHolidayQuota()
{
    Employee *employeepoint = employeeHead;
    while (employeepoint->next != NULL) {
        employeepoint = employeepoint->next;
        EmployeeHolidayQuota *holidayQuotaPoint = employeepoint->holidayQuotaData;
        EmployeeHolidayQuota *preNode = holidayQuotaPoint;
        while (holidayQuotaPoint != NULL) {
            preNode = holidayQuotaPoint;
            holidayQuotaPoint = holidayQuotaPoint->next;
            free(preNode);
        }
    }
}

int setEmployeeDepartment(int employeeID, int departmentID)
{
    Employee *point = employeeHead->next;
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
    freeHolidayQuota();
    
    freeDepartmentNode();
    freeEmployeeNode();
    freeHolidayNode();
    freeUserNode();
}

void initlist()
{
    initDepartmentList();
    initEmployeeList();
    initHolidayList();
    initUserList();
}

void displayDepartmentList()
{
    Department *point = departmentHead->next;
    printf("部门列表:\n");
    while (point != NULL) {
        printf("部门ID: %d, 部门名称: %s\n", point->departmentID, point->name);
        point = point->next;
    }
}

void addDepartment()
{
    int departmentID;
    char departmentName[MAX_NAME_LENGTH];
    printf("请输入部门ID: ");
    scanf("%d", &departmentID);
    printf("请输入部门名称: ");
    scanf("%s", departmentName);
    addDepartmentNode(departmentID, departmentName); 
}

void removeDepartment()
{
    int index;
    printf("请输入要删除的部门序号: ");
    scanf("%d", &index);
    removeDepartmentNode(index);
}

void modifyDepartment()
{
    int index;
    printf("请输入要修改的部门序号: ");
    scanf("%d", &index);
    modifyDepartmentNode(index);
}

void displayEmployeeList()
{
    Employee *point = employeeHead->next;
    printf("员工列表:\n");
    while (point != NULL) {
        printf("员工ID: %d, 员工姓名: %s, 部门名称: %s\n", point->employeeID, point->employeeName, point->departmentName);
        point = point->next;
    }
}

void addEmployee()
{
    int employeeID;
    char employeeName[MAX_NAME_LENGTH];
    char departmentName[MAX_NAME_LENGTH];
    char role[MAX_NAME_LENGTH];
    printf("请输入员工ID: ");
    scanf("%d", &employeeID);
    printf("请输入部门名称: ");
    scanf("%s", departmentName);
    printf("请输入员工姓名: ");
    scanf("%s", employeeName);
    printf("请输入员工职位名称: ");
    scanf("%s", role);
    addEmployeeNode(employeeID, departmentName, employeeName, role); 
}

void removeEmployee()
{
    int index;
    printf("请输入要删除的员工序号: ");
    scanf("%d", &index);
    removeEmployeeNode(index);
}

void modifyEmployee()
{
    int index;
    printf("请输入要修改的员工序号: ");
    scanf("%d", &index);
    modifyEmployeeNode(index);
}

void displayHolidayList()
{
    HolidayType *point = holidayHead->next;
    printf("假期列表:\n");
    while (point != NULL) {
        printf("假期ID: %d, 假期名称: %s, 最短时间: %d, 最长时间: %d\n", point->holidayID, point->name, point->minimumTime, point->maximumTime);
        point = point->next;
    }
}

void addHoliday()
{
    int holidayID;
    int minimumTime;
    int maximumTime;
    char name[MAX_NAME_LENGTH];
    printf("请输入假期ID: ");
    scanf("%d", &holidayID);
    printf("请输入假期名称: ");
    scanf("%s", name);
    printf("请输入假期最短时间: ");
    scanf("%d", &minimumTime);
    printf("请输入假期最长时间: ");
    scanf("%d", &maximumTime);
    addHolidayNode(holidayID, maximumTime, minimumTime, name); 
}

void removeHoliday()
{
    int index;
    printf("请输入要删除的假期序号: ");
    scanf("%d", &index);
    removeHolidayNode(index);
}

void modifyHoliday()
{
    int index;
    printf("请输入要修改的假期序号: ");
    scanf("%d", &index);
    modifyHolidayNode(index);
}

void displayUserList()
{
    User *point = userHead->next;
    printf("用户列表:\n");
    while (point != NULL) {
        printf("用户身份：%s, 用户账号：%s, 用户密码：%s, 用户ID: %d, 姓名: %s, 角色: %d, 所属部门: %s\n", point->role, point->account, point->password, point->id, point->name, point->roleType, point->department);
        point = point->next;
    }
}

void addUser()
{
    char role[MAX_NAME_LENGTH];
    int id;
    char password[MAX_NAME_LENGTH];
    char name[MAX_NAME_LENGTH];
    char account[MAX_NAME_LENGTH];
    char department[MAX_NAME_LENGTH];
    int roleType;

    printf("请输入用户身份: ");
    scanf("%s", role);
    printf("请输入账号: ");
    scanf("%s", account);
    printf("请输入密码: ");
    scanf("%s", password);
    printf("请输入姓名: ");
    scanf("%s", name);

    printf("请输入用户ID: ");
    scanf("%d", &id);

    printf("请输入角色编号(1-4): ");
    scanf("%d", &roleType);
    if (roleType < 1 || roleType > 4) {
        printf("输入编号非法\n");
        return;
    }
    printf("请输入用户所属部门名称: ");
    scanf("%s", department);

    addUserNode(id, password, name, account, (RoleType)roleType, department, role); 
}

void removeUser()
{
    int index;
    printf("请输入要删除的用户序号: ");
    scanf("%d", &index);
    removeUserNode(index);
}

void modifyUser()
{
    int index;
    printf("请输入要修改的用户序号: ");
    scanf("%d", &index);
    modifyUserNode(index);
}

int queryEmployeeClockNotingByID()
{
    int employeeID;
    printf("请输入员工ID: ");
    scanf("%d", &employeeID);

    Employee *point = employeeHead->next;
    while (point != NULL) {
        if (point->employeeID == employeeID) {
            printf("员工ID: %d, 员工姓名: %s, 部门ID: %d\n", point->employeeID, point->employeeName, point->departmentID);
            ClockNoting *clockNotingPoint = point->clockNotingData;
            printf("打卡记录:\n");
            while (clockNotingPoint != NULL) {
                printf("打卡日期: %d-%d-%d, 上班时间: %d:%d, 下班时间: %d:%d, 是否缺勤: %s\n",
                    clockNotingPoint->clockDate.year, clockNotingPoint->clockDate.month, clockNotingPoint->clockDate.day,
                    clockNotingPoint->clockInTime.hour, clockNotingPoint->clockInTime.minute,
                    clockNotingPoint->clockOutTime.hour, clockNotingPoint->clockOutTime.minute,
                    clockNotingPoint->isAbsent ? "是" : "否");
                clockNotingPoint = clockNotingPoint->next;
            }
            return 1;
        }
        point = point->next;
    }
    printf("未找到该员工\n");
    return 0;
}

int queryEmployeeClockNotingByNameandDate()
{
    char employeeName[MAX_NAME_LENGTH];
    Date clockDate;
    printf("请输入员工姓名: ");
    scanf("%s", employeeName);
    printf("请输入打卡日期 (年 月 日): ");
    scanf("%d %d %d", &clockDate.year, &clockDate.month, &clockDate.day);
    
    Employee *point = employeeHead->next;
    while (point != NULL) {
        if (strcmp(point->employeeName, employeeName) == 0) {
            ClockNoting *clockNotingPoint = point->clockNotingData;
            while (clockNotingPoint != NULL) {
                if (clockNotingPoint->clockDate.day == clockDate.day && clockNotingPoint->clockDate.month == clockDate.month && clockNotingPoint->clockDate.year == clockDate.year)
                {
                    printf("员工ID: %d, 员工姓名: %s, 部门ID: %d\n", point->employeeID, point->employeeName, point->departmentID);
                    printf("打卡日期: %d-%d-%d, 上班时间: %d:%d, 下班时间: %d:%d, 是否缺勤: %s\n",
                        clockNotingPoint->clockDate.year, clockNotingPoint->clockDate.month, clockNotingPoint->clockDate.day,
                        clockNotingPoint->clockInTime.hour, clockNotingPoint->clockInTime.minute,
                        clockNotingPoint->clockOutTime.hour, clockNotingPoint->clockOutTime.minute,
                        clockNotingPoint->isAbsent ? "是" : "否");
                    return 1;
                }
                clockNotingPoint = clockNotingPoint->next;
            }
            printf("未找到该员工在该日期的打卡记录\n");
            return 0;
        }
        point = point->next;
    }
    printf("未找到该员工\n");
    return 0;
}

void setpasswordMenu()
{
    int userID;
    char newPassword[MAX_NAME_LENGTH];
    printf("请输入用户ID: ");
    scanf("%d", &userID);
    printf("请输入新密码: ");
    scanf("%s", newPassword);
    while (strlen(newPassword) > MAX_NAME_LENGTH) {
        printf("密码过长，请重新输入: ");
        scanf("%s", newPassword);
    }
    
    User *point = userHead->next;
    while (point != NULL) {
        if (point->id == userID) {
            strcpy(point->password, newPassword);
            printf("密码修改成功\n");
            return;
        }
        point = point->next;
    }
    printf("未找到该用户\n");
}

void setHolidayTimeMenu()
{
    int holidayID;
    int minimumTime;
    int maximumTime;
    printf("请输入假期ID: ");
    scanf("%d", &holidayID);
    printf("请输入假期最短时间: ");
    scanf("%d", &minimumTime);
    printf("请输入假期最长时间: ");
    scanf("%d", &maximumTime);
    setHolidayTime(holidayID, minimumTime, maximumTime);
}

void setEmployeeHolidayQuotaMenu()
{
    int employeeID;
    int holidayTypeID;
    int totalQuota;
    printf("请输入员工ID: ");
    scanf("%d", &employeeID);
    printf("请输入假期类型ID: ");
    scanf("%d", &holidayTypeID);
    printf("请输入假期总额度: ");
    scanf("%d", &totalQuota);
    setEmployeeHolidayQuota(employeeID, holidayTypeID, totalQuota);
}

void setEmployeeDepartmentMenu()
{
    int employeeID;
    int departmentID;
    printf("请输入员工ID: ");
    scanf("%d", &employeeID);
    printf("请输入部门ID: ");
    scanf("%d", &departmentID);
    setEmployeeDepartment(employeeID, departmentID);
}

void displayHolidayQuotaList()
{
    Employee *point = employeeHead->next;
    while (point != NULL) {
        printf("员工ID: %d, 员工姓名: %s\n", point->employeeID, point->employeeName);
        if (point->holidayQuotaData == NULL) {
            printf("该员工无假期配额数据\n");
            point = point->next;
            continue;
        }
        EmployeeHolidayQuota *holidayQuotaPoint = point->holidayQuotaData->next;
        while (holidayQuotaPoint != NULL) {
            printf("假期类型ID: %d, 总配额: %d, 已用配额: %d, 剩余配额: %d\n",
                holidayQuotaPoint->holidayTypeID,
                holidayQuotaPoint->totalQuota,
                holidayQuotaPoint->usedQuota,
                holidayQuotaPoint->remainingQuota);
            holidayQuotaPoint = holidayQuotaPoint->next;
        }
        point = point->next;
    }
}

void displayHolidayQuota(Employee *employee)
{
    printf("员工ID: %d, 员工姓名: %s\n", employee->employeeID, employee->employeeName);
    if (employee->holidayQuotaData == NULL) {
        printf("该员工无假期配额数据\n");
        return;
    }
    EmployeeHolidayQuota *holidayQuotaPoint = employee->holidayQuotaData->next;
    while (holidayQuotaPoint != NULL) {
        printf("假期类型ID: %d, 总配额: %d, 已用配额: %d, 剩余配额: %d\n",
            holidayQuotaPoint->holidayTypeID,
            holidayQuotaPoint->totalQuota,
            holidayQuotaPoint->usedQuota,
            holidayQuotaPoint->remainingQuota);
        holidayQuotaPoint = holidayQuotaPoint->next;
    }
}

void setHolidayQuotaMenu()
{
    int employeeID;
    int holidayTypeID;
    int totalQuota;
    displayEmployeeList();
    printf("请输入员工ID: ");
    scanf("%d", &employeeID);
    Employee *point = employeeHead;
    int found = 0;
    while (point->next != NULL) {
        point = point->next;
        if (point->employeeID == employeeID) {
            found = 1;
            system("cls");
            displayHolidayQuota(point);
            printf("请输入假期类型ID: ");
            scanf("%d", &holidayTypeID);
            printf("请输入假期总额度: ");
            scanf("%d", &totalQuota);
            EmployeeHolidayQuota *holidayQuotaPoint = point->holidayQuotaData->next;
            while (holidayQuotaPoint != NULL) {
                if (holidayQuotaPoint->holidayTypeID == holidayTypeID) {
                    holidayQuotaPoint->totalQuota = totalQuota;
                    holidayQuotaPoint->remainingQuota = max(totalQuota - holidayQuotaPoint->usedQuota, 0);
                    printf("假期额度设置成功\n");
                    return;
                }
                holidayQuotaPoint = holidayQuotaPoint->next;
            }
        }
    }
    if (!found) printf("未找到该员工\n");
}