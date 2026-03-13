#ifndef EMPLOY_H
#define EMPLOY_H
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

		if (clocking == 1) {

		}
		else if (clocking == 2) {
			return false;
		}

		return false;
	}
}

#endif
