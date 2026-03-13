#ifndef EMPLOY_H
#define EMPLOY_H


bool Clock(Employee* employee) {
	while (true) {
		printf("要进行打卡吗？(请输入数字)\n");
		printf("1.是\t2.否\n");
		int clocking;
		scanf("%d", &clocking);

		while (clocking != 1 && clocking != 2) {
			printf("输入错误，请重新输入!\n");
			printf("要进行打卡吗？(请输入数字)\n");
			printf("1.是\t2.否\n");
			scanf("%d", &clocking);
		}

		while (clocking == 1) {
			printf("请输入打卡时间:(输入0返回)\n");
			char input[1000];
			fgets(input, sizeof(input), stdin);
			int len = strlen(input);
			if (len == 3 && input[0] == '0') {
				clocking = 0;
				break;
			}
			else if (len == 7 && input[2] == ':') {
				printf("打卡成功！\n");
				return true;
			}
			else {
				printf("输入错误，请重新输入!\n");
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
	return false;
}


#endif
