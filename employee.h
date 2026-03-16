#ifndef EMPLOY_H
#define EMPLOY_H


bool Clock(Employee* employee) {
	while (true) {
		printf("要进行打卡吗？(请输入数字)\n");
		printf("1.是\t2.否\n");
		int clocking;
		scanf("%d", &clocking);
		int c;
		while ((c = getchar()) != '\n' && c != EOF);

		while (clocking != 1 && clocking != 2) {
			printf("输入错误，请重新输入!\n");
			printf("要进行打卡吗？(请输入数字)\n");
			printf("1.是\t2.否\n");
			scanf("%d", &clocking);
			while ((c = getchar()) != '\n' && c != EOF);
		}

		while (clocking == 1) {
			printf("请输入打卡时间:(输入0返回)\n");
			char input[1000];
			fgets(input, sizeof(input), stdin);
			int len = strlen(input);
			if (len == 2 && input[0] == '0') {
				clocking = 0;
				break;
			}
			else if (len == 6 && input[2] == ':') {
				int hour=(input[0]-'0')*10+(input[1]-'0');
				if (hour == 24) {
					hour -= 24;
				}
				else if (hour > 24) {
					printf("输入错误，请重新输入!\n");
					continue;
				}
				int minute=(input[3]-'0')*10+(input[4]-'0');
				if (minute >= 60) {
					printf("输入错误，请重新输入!\n");
					continue;
				}
				employee->clockNotingData = (ClockNoting*)malloc(sizeof(ClockNoting));
				employee->clockNotingData->clockInTime.hour = hour;
				employee->clockNotingData->clockInTime.minute = minute;
				printf("打卡成功！\n");
				printf("打卡时间为:");
				if (hour < 10) {
					printf("0%d:",hour);
				}
				else {
					printf("%d:",hour);
				}
				if (minute < 10) {
					printf("0%d\n", minute);;
				}
				else {
					printf("%d\n", minute);
				}
				return true;
			}
			else {
				printf("输入错误，请重新输入!\n");
				continue;
			}
		}

		if (clocking == 2) {
			printf("取消打卡。\n");
			return false;
		}

		if (clocking == 0) {
			printf("返回到上一个界面。\n");
			continue;
		}

		return false;
	}
	return false;
}


#endif
