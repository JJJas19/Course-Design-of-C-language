#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "common.h"

extern Department *departmentHead;
extern Employee *employeeHead;
extern HolidayType *holidayHead;
extern User *userHead;

void initDepartmentList();
int addDepartmentNode(int departmentID, const char* departmentName);
int removeDepartmentNode(int index);
int modifyDepartmentNode(int index);
void freeDepartmentNode();
void initEmployeeList();
int addEmployeeNode(int employeeID, const char* departmentName, const char* employeeName);
int addUserNode(int id, const char* password, const char* name, const char* account, RoleType roleType);
int addHolidayNode(int holidayID, int maximumTime, int minimumTime, const char* name);
int setEmployeeDepartment(int employeeID, int departmentID);
int setHolidayTime(int holidayID, int minimumTime, int maximumTime);
void freeNode();
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

void initlist();

void setpasswordMenu();
void setHolidayTimeMenu();
void setEmployeeDepartmentMenu();
void setEmployeeHolidayQuotaMenu();

void loadDepartmentData();
void loadEmployeeData();
void loadData();

void saveDepartmentData();
void saveEmployeeData();
void saveUserData();
void saveHolidayData();
void saveData();

void administrator_menu();

#endif 