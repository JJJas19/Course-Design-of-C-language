#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "common.h"
#include "employee.h"

void EmployLogic(Employee* employee) {
	printf("职员姓名: %s\n", employee->employeeName);
	printf("职员ID:%d\n", employee->employeeID);
	while (true) {
		printf("请选择要执行的操作:\n");
		int operation;
		scanf("%d", &operation);
		printf("0.退出\n");
		printf("1.打卡\n");
		printf("2.打卡记录查询\n");
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
	Employee* employeeA=(Employee*)malloc(sizeof(Employee));
	printf("请输入员工的名字:\n");
	scanf("%s", employeeA->employeeName);
	printf("请输入员工的ID:\n");
	scanf("%d", &employeeA->employeeID);
	EmployLogic(employeeA);
	return 0;
}