#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "common.h"
void initDepartmentList();
int addDepartmentNode(int departmentID, const char* departmentName);
int removeDepartmentNode(int index);
int modifyDepartmentNode(int index);
void freeDepartmentNode();
void initEmployeeList();
int addEmployeeNode(int employeeID, int departmentID, const char* employeeName);
int setEmployeeDepartment(int employeeID, int departmentID);
int setHolidayTime(int holidayID, int minimumTime, int maximumTime);
void freeNode();

#endif 