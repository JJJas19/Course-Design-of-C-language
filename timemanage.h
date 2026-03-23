#include <stdio.h>
#include <stdlib.h>
#include "common.h"


void ChangeDate(Date* date,int length) {
	int year[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	if (date->year % 4 == 0 && (date->year % 100 != 0 || date->year % 400 == 0)) {
		year[2] = 29;
	}
	else {
		year[2] = 28;
	}
	date->day += length;
	while (date->day > year[date->month]) {
		date->day -= year[date->month];
		date->month++;
		if (date->month > 12) {
			date->month -= 12;
			date->year++;
			if (date->year % 4 == 0 && (date->year % 100 != 0 || date->year % 400 == 0)) {
				year[2] = 29;
			}
			else {
				year[2] = 28;
			}
		}
	}
}

Date CalculateDate(Date date, int length) {
	int year[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	if (date.year % 4 == 0 && (date.year % 100 != 0 || date.year % 400 == 0)) {
		year[2] = 29;
	}
	else {
		year[2] = 28;
	}
	date.day += length;
	while (date.day > year[date.month]) {
		date.day -= year[date.month];
		date.month++;
		if (date.month > 12) {
			date.month -= 12;
			date.year++;
			if (date.year % 4 == 0 && (date.year % 100 != 0 || date.year % 400 == 0)) {
				year[2] = 29;
			}
			else {
				year[2] = 28;
			}
		}
	}
	return date;
}

void TimeManage(Date* date) {
	while (true) {
		printf("今天是%d年%d月%d日\n",date->year,date->month,date->day);
		printf("要进入下一天吗?\n");
		printf("0.返回\t1.是\n");
		int operation;
		char input[20];
		if (fgets(input, 20, stdin) == NULL) {
			printf("输入错误，请重新输入\n");
			continue;
		}
		while ((c = getchar()) != EOF && c != '\n');
		int res = sscanf(input, "%d", &operation);
		if (res != 0) {
			printf("读取失败!请重新输入!\n");
			continue;
		}
		if (operation == 1) {
			ChangeDate(date,1);
			printf("已进入下一天!\n");
		}
		else if (operation == 0) {
			return;
		}
		else {
			printf("输入错误，请重新输入\n");
			continue;
		}
	}
}