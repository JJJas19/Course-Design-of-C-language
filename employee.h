#ifndef EMPLOY_H
#define EMPLOY_H
#include <string.h>
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

		while (clocking == 1) {
			printf("请输入打卡时间,输入0返回\n");
			char input[1000];
			if (fgets(input, sizeof(input), stdin) == NULL) {
				printf("输入有误，请重新输入!\n");
				continue;
			}
			int len;
			len = strlen(input);
			if (len == 3 && input[0] == '0' && input[1] == '\n' && input[2] == '0')
			{
				clocking = 0;
				break;
			}
			else if (len == 7 && input[2] == ':') {
				int hour, minute;
				hour=(input[0]-'0')*10+(input[1]-'0');
				if (hour > 24) {
					printf("输入有误，请重新输入!\n");
					continue;
				}
				else if (hour == 24) {
					hour -= 24;
				}
				minute=(input[3]-'0')*10+(input[4]-'0');
				if (minute > 59) {
					printf("输入有误，请重新输入!\n");
					continue;
				}
				printf("打卡成功！\n");
				return true;
			}
			else {
				printf("输入有误，请重新输入！\n");
				continue;
			}
		}
		if (clocking == 2) {
			return false;
		}

		if (clocking == 0) {
			continue;
		}

		return false;
	}
}

#endif
