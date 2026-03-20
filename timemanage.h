#include <stdio.h>
#include <stdlib.h>
#include "common.h"

void DateChange(Date* date) {
	date->day++;
	if (day > 30) {
		date->month++;
		date->day = 1;
		if (month > 12) {
			date->year++;
			date->month = 1;
		}
	}
}

void TimeManage(Date* date) {
	while (true) {
		printf("今天是%d年%d月%d日\n");
		printf("要进入下一天吗?\n");
		printf("0.返回\t1.是\n");
		int operation;
		scanf("%d", &operation);
		if (operation == 1) {
			DateChange(date);
			printf("已进入下一天");
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