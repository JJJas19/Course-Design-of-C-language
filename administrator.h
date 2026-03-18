#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "common.h"
void initDepartmentList();
int addDepartmentNode(int departmentID, const char* departmentName);
int removeDepartmentNode(int index);
int modifyDepartmentNode(int index);
void freeDepartmentNode();
#endif 