#include <stdio.h>
#include <stdlib.h>
#include "common.h"

void DateChange(Date* date) {
	date->day=date->day+1;
	if (date->day > 30) {
		date->month=date->month+1;
		date->day = 1;
		if (date->month > 12) {
			date->year=date->year+1;
			date->month = 1;
		}
	}
}

void TimeManage(Date* date) {
	while (true) {
		printf("今天是%d年%d月%d日\n",date->year,date->month,date->day);
		printf("要进入下一天吗?\n");
		printf("0.返回\t1.是\n");
		int operation;
		scanf("%d", &operation);
		if (operation == 1) {
			DateChange(date);
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