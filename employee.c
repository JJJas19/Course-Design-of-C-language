#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "common.h"
#include "employee.h"



void EmployLogic(Employee* employee) {
	printf("职员姓名: %s\n", employee->employeeName);
	printf("职员ID:%d\n", employee->employeeID);
	Clock(employee);
}

int main() {
	Employee* employeeA=(Employee*)malloc(sizeof(Employee));
	printf("请输入员工的名字:\n");
	scanf("%s", employeeA->employeeName);
	printf("请输入员工的ID:\n");
	scanf("%d", &employeeA->employeeID);
	EmployLogic(employeeA);
	return 0;
}