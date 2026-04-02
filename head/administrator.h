#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "common.h"
#include "manager.h"
#include "employee.h"

extern Department *departmentHead;
extern Employee *employeeHead;
extern HolidayType *holidayHead;
extern User *userHead;

// 链表操作
void initlist();
void freeNode();

void initDepartmentList();
int addDepartmentNode(int departmentID, const char* departmentName);
int removeDepartmentNode(int index);
int modifyDepartmentNode(int index);

int addEmployeeNode(int employeeID, const char* departmentName, const char* employeeName, const char* role);
int removeEmployeeNode(int index);
int modifyEmployeeNode(int index);

int addUserNode(int id, const char* password, const char* name, const char* account, RoleType roleType, const char* department, const char* role);
int removeUserNode(int index);
int modifyUserNode(int index);

int addHolidayNode(int holidayID, int maximumTime, int minimumTime, const char* name);
int removeHolidayNode(int index);
int modifyHolidayNode(int index);

int setEmployeeDepartment(int employeeID, int departmentID);
int setHolidayTime(int holidayID, int minimumTime, int maximumTime);

void displayDepartmentList();
void addDepartment();
void removeDepartment();
void modifyDepartment();

void displayEmployeeList();
void addEmployee();
void removeEmployee();
void modifyEmployee();

void addHoliday();
void removeHoliday();
void modifyHoliday();
void displayHolidayList();

void addUser();
void removeUser();
void modifyUser();
void displayUserList();

// 菜单
void setpasswordMenu();
void setHolidayTimeMenu();
void setEmployeeDepartmentMenu();
void setEmployeeHolidayQuotaMenu();
void administrator_menu();
void setHolidayQuotaMenu();

// 数据加载与保存
void loadDepartmentData();
void loadEmployeeData();
void loadData();

void saveDepartmentData();
void saveEmployeeData();
void saveUserData();
void saveHolidayData();
void saveData();

// 数据备份与恢复
void backupData();
void restoreData();

// 请假信息查询
void displayLeaveHistory();
void query_leave_history();

// 假期配额
void displayHolidayQuotaList();
void displayHolidayQuota(Employee *employee);

// 信息统计
void statisticsMenu();

#endif 