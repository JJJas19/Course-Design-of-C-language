#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "common.h"
#include "employee.h"


void EmployLogic(Employee* employee) {
	printf("职员姓名: %s\n", employee->employeeName);
	printf("职员ID:%d\n", employee->employeeID);
	Clock(employee);
}

int main() {
	Employee* employeeA;
	employeeA = (Employee*)malloc(sizeof(Employee));
	employeeA->clockNotingData=(ClockNoting*)malloc(sizeof(ClockNoting));
	employeeA->clockNotingData->numberOfDays = 0;
	printf("正在运行\n");
	scanf("%s", employeeA->employeeName);
	scanf("%d", &employeeA->employeeID);
	EmployLogic(employeeA);
	return 0;
}