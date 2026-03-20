#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "common.h"
#include "employee.h"
#include "administrator.c"

Employee* CreateEmployee() {
	Employee* employee = (Employee*)malloc(sizeof(Employee));
	printf("请输入职员姓名:");
	char name[MAX_NAME_LENGTH];
	fgets(name, sizeof(name), stdin);
	strcpy(employee->employeeName, name);
	printf("请输入员工ID：");
	scanf("%d", &employee->employeeID);
	return employee;
}

void EmployeeLogic(Employee* employee) {
	printf("职员姓名: %s\n", employee->employeeName);
	printf("职员ID:%d\n", employee->employeeID);
	while (true) {
		printf("请选择要执行的操作:\n");
		int operation;
		printf("0.退出\n");
		printf("1.打卡\n");
		printf("2.打卡记录查询\n");
		scanf("%d", &operation);
		
		if (operation == 0) {
			return;
		}
		else if (operation == 1) {
			Clock(employee);
		}
		else if (operation == 2) {
			GetClockNoting(employee);
		}
		else if (operation == 3) {

		}
		else {
			printf("输入错误，请重新输入！\n");
			continue;
		}
	}
}

int main() {
	Employee* employee;
	while (true) {
		printf("请输入要执行的操作:\n");
		printf("0.退出\n");
		printf("1.添加员工\n");
		printf("2.管理某员工\n");
		int operation;
		scanf("%d", &operation);
		int c;
		while ((c = getchar()) != EOF && c != '\n');
		if (operation == 0) {
			break;
		}
		else if (operation == 1) {
			employee = CreateEmployee();
		}
		else if (operation == 2) {
			EmployeeLogic(employee);
		}
	}
	return 0;
}