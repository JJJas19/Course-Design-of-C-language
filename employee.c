#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include "common.h"

bool Clock(Employee* employee) {
	while (true) {
		printf("要进行打卡吗？(请输入数字)\n");
		printf("1.是\t2.否");
		int clocking;
		scanf("%d", &clocking);

		while (clocking != 1 && clocking != 2) {
			printf("输入错误，请重新输入!/n");
			printf("要进行打卡吗？(请输入数字)\n");
			printf("1.是\t2.否");
			scanf("%d", &clocking);
		}

		

		return false;
	}
}

void EmployLogic(Employee* employee) {
	printf("职员姓名: %s\n", employee->employeeName);
	printf("职员ID:%d\n", employee->employeeID);
	Clock(employee);
}