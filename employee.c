#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "common.h"
#include "employee.h"
#include "timemanage.h"

void EmployLogic(Employee* employee) {
	printf("职员姓名: %s\n", employee->employeeName);
	printf("职员ID:%d\n", employee->employeeID);
	while (true) {
		printf("请选择要执行的操作:\n");
		printf("0.退出\n");
		printf("1.打卡\n");
		printf("2.打卡记录查询\n");
		printf("3.时间总控\n");
		int operation;
		int c;
		char input[20];
		if (fgets(input, sizeof(input), stdin) == NULL) {
			printf("输入有误!请重新输入!\n");
			continue;
		}
		while ((c = getchar()) != EOF && c != '\n');
		int res = sscanf(input, "%d", &operation);
		if (res != 1) {
			printf("读取失败!请重新尝试!\n");
			continue;
		}
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
	Date date;
	FILE* fp;
	fp = fopen("timedata.bin", "rb");
	if (fp == NULL) {
		printf("首次运行，未找到历史文件，初始化默认时间：2026.01.01");
		date = (Date){ 2026,1,1 };
	}
	else {
		size_t read_num = fread(&date, sizeof(Date), 1, fp);
		if (read_num != 1) {
			printf("读取历史文件失败，初始化默认时间：2026.01.01\n");
			date = (Date){ 2026,1,1 };
		}
		else {
			printf("读取历史文件成功!\n");
		}
		fclose(fp);
	}
	while (true) {
		printf("当前时间是%d年%d月%d日\n", date.year, date.month, date.day);
		printf("要进行时间管理吗?\n");
		printf("0.否\t1.是\n");
		int operation;
		scanf("%d", &operation);
		if (operation == 1) {
			TimeManage(&date);
		}
		else {
			break;
		}
	}
	fp = fopen("timedata.bin", "wb");
	if (fp == NULL) {
		printf("保存时间失败！\n");
		return 1;
	}
	fwrite(&date, sizeof(Date), 1, fp);
	return 0;
}