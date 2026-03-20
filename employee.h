#ifndef EMPLOY_H
#define EMPLOY_H

// 定义Clock函数，用于处理员工打卡操作，参数为指向Employee结构体的指针
bool Clock(Employee* employee) {
    while (true) {
        printf("请选择打卡类型:\n");
        printf("0.返回\t1.上班\t2.下班\n");
        int clockingType;
        scanf("%d", &clockingType);
        if (clockingType == 0) {
            return;
        }
        if (clockingType != 1 && clockingType != 2) {
            printf("输入错误，请重新输入!\n");
            continue;
        }
        while (true) {
            // 提示用户是否要进行打卡
            printf("要进行打卡吗？(请输入数字)\n");
            printf("1.是\t2.否\n");
            int clocking; // 声明一个整数变量clocking用于存储用户的输入
            scanf("%d", &clocking); // 读取用户输入的数字
            int c;
            // 清空输入缓冲区，直到遇到换行符或文件结束符
            while ((c = getchar()) != '\n' && c != EOF);

            // 如果用户输入的数字不是1或2，则提示输入错误，并要求重新输入
            while (clocking != 1 && clocking != 2) {
                printf("输入错误，请重新输入!\n");
                printf("要进行打卡吗？(请输入数字)\n");
                printf("1.是\t2.否\n");
                scanf("%d", &clocking);
                while ((c = getchar()) != '\n' && c != EOF);
            }

            // 如果用户选择进行打卡（输入1）
            while (clocking == 1) {
                // 提示用户输入打卡时间，并告知输入0可以返回上一级菜单
                printf("请输入打卡时间:(输入0返回)\n");
                char input[1000]; // 声明一个字符数组input用于存储用户输入的时间字符串
                fgets(input, sizeof(input), stdin); // 读取用户输入的时间字符串
                int len = strlen(input); // 获取输入字符串的长度
                // 如果用户输入的是"0"（仅包含一个字符'0'和换行符'\n'），则将clocking设置为0并退出循环
                if (len == 2 && input[0] == '0') {
                    clocking = 0;
                    break;
                }
                // 如果用户输入的是格式为"HH:MM"的时间字符串
                else if (len == 6 && input[2] == ':') {
                    // 将小时和分钟从字符串中解析为整数
                    int hour = (input[0] - '0') * 10 + (input[1] - '0');
                    if (hour == 24) {
                        hour -= 24; // 如果小时为24，则将其调整为0，表示午夜
                    }
                    else if (hour > 24) {
                        printf("输入错误，请重新输入!\n"); // 如果小时大于24，则提示输入错误，并要求重新输入
                        continue;
                    }
                    int minute = (input[3] - '0') * 10 + (input[4] - '0'); // 计算分钟
                    if (minute >= 60) {
                        printf("输入错误，请重新输入!\n"); // 如果分钟大于等于60，则提示输入错误，并要求重新输入
                        continue;
                    }
                    // 为clockNotingData分配内存空间
                    employee->clockNotingData = (ClockNoting*)malloc(sizeof(ClockNoting));
                    // 设置打卡时间
                    if (clockingType == 1) {
                        if (employee->clockNotingData->clockInTime.isClocking == 1) {
                            printf("请不要重复打卡!\n");
                            continue;
                        }
                        employee->clockNotingData->clockInTime.isClocking = 1;
                        employee->clockNotingData->clockInTime.hour = hour;
                        employee->clockNotingData->clockInTime.minute = minute;
                    }
                    else if (clockingType == 2) {
                        if (employee->clockNotingData->clockOutTime.isClocking == 1) {
                            printf("请不要重复打卡!\n");
                            continue;
                        }
                        employee->clockNotingData->clockOutTime.isClocking = 1;
                        employee->clockNotingData->clockOutTime.hour = hour;
                        employee->clockNotingData->clockOutTime.minute = minute;
                    }
                    printf("打卡成功！\n"); // 打印打卡成功提示
                    printf("打卡时间为:"); // 打印打卡时间
                    // 根据小时和分钟的值，格式化输出时间，确保小时和分钟都是两位数
                    if (hour < 10) {
                        printf("0%d:", hour);
                    }
                    else {
                        printf("%d:", hour);
                    }
                    if (minute < 10) {
                        printf("0%d\n", minute);
                    }
                    else {
                        printf("%d\n", minute);
                    }
                    return true; // 打卡成功，返回true
                }
                else {
                    printf("输入错误，请重新输入!\n"); // 如果输入格式不正确，则提示输入错误，并要求重新输入
                    continue;
                }
            }

            // 如果用户选择取消打卡（输入2）
            if (clocking == 2) {
                printf("取消打卡。\n"); // 打印取消打卡提示
                return false; // 返回false，表示未打卡
            }

            // 如果用户选择返回（输入0）
            if (clocking == 0) {
                printf("返回到上一个界面。\n"); // 打印返回提示
                continue; // 继续下一次循环
            }

            return false; // 这里实际上是多余的，因为在clocking == 1和2时已经返回
        }
        return false; // 这里也是多余的，因为在while(true)循环中不会执行到这里
    }
}

//某日的打卡情况
void ClockNotingByDate(ClockNoting* clockNotingData) {
    printf("%d年%d月%d日打卡情况:", clockNotingData->clockDate.year, clockNotingData->clockDate.month, clockNotingData->clockDate.day);
    if (clockNotingData->isAbsent == 1) {
        printf("请假\n");
    }
    else if (clockNotingData->isAbsent == 0) {
        printf("上班:");
        if (clockNotingData->clockInTime.isClocking == 0) {
            printf("未打卡!\n");
        }
        else if (clockNotingData->clockInTime.isClocking == 1) {
            printf("%d:%d", clockNotingData->clockInTime.hour, clockNotingData->clockInTime.minute);
        }
        else {
            printf("状态未知!\n");
            //实际上是多余的，因为isClocking只能取0、1两种值
        }
        if (clockNotingData->isAbsent == 1) {
            printf("请假\n");
        }
        else if (clockNotingData->isAbsent == 0) {
            //对上班的打卡时间查询
            printf("上班:");
            if (clockNotingData->clockInTime.isClocking == 0) {
                printf("未打卡!\n");
            }
            else if (clockNotingData->clockInTime.isClocking == 1) {
                printf("%d:%d", clockNotingData->clockInTime.hour, clockNotingData->clockInTime.minute);
            }
            else {
                printf("状态未知!\n");
                //实际上是多余的，因为isClocking只能取0、1两种值
            }
            //对下班的打卡时间查询
            printf("下班:");
            if (clockNotingData->clockInTime.isClocking == 0) {
                printf("未打卡!\n");
            }
            else if (clockNotingData->clockInTime.isClocking == 1) {
                printf("%d:%d", clockNotingData->clockInTime.hour, clockNotingData->clockInTime.minute);
            }
            else {
                printf("状态未知!\n");
                //实际上是多余的，因为isClocking只能取0、1两种值
            }
        }
        else {
            printf("未知状态！\n");
            //实际上是多余的，因为isAbsent只能取0、1两种值
        }
    }
}

//查询打卡记录的函数
void FindClockNoting(Employee* employee) {
    printf("您已积累打卡%d天", employee->clockNotingData->numberOfDays);
    while (employee->clockNotingData != NULL) {
        ClockNotingByDate(employee->clockNotingData);
        employee->clockNotingData=employee->clockNotingData->next;
    }
}

//查询请假日期
void FindAbsenceByDate(Employee* employee) {
    printf("请假的日期为:\n");
    while (employee->clockNotingData != NULL) {
        if (employee->clockNotingData->isAbsent == 1) {
            printf("%d年%d月%d日\n", employee->clockNotingData->clockDate.year, employee->clockNotingData->clockDate.month, employee->clockNotingData->clockDate.day);
        }
        employee->clockNotingData= employee->clockNotingData->next;
    }
}

//查询某日打卡记录的函数
void FindClockNotingByDate(Employee* employee) {
    while (true) {
        printf("请输入具体日期,格式为yyyy.mm.dd,(输入0返回):");
        char input[20];
        int year, month, day;
        int scanCount;
        int c;
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("数据解析失败，请重试!\n");
            continue;
        }
        while ((c = getchar()) != EOF && c != '\n');
        scanCount = sscanf(input, "%d.%d.%d", &year, &month, &day);
        if (scanCount == 1 && year == 0) {
            printf("返回到上一界面\n");
            break;
        }
        else if (scanCount == 3) {
            printf("您选择的日期为%d年%d月%d日\n", year, month, day);
            //查询该日期的打卡记录
            ClockNoting* temp = employee->clockNotingData;
            int isFound = 0; //是否找到该日期的打卡记录
            while (temp != NULL) {
                if (temp->clockDate.year == year && temp->clockDate.month == month && temp->clockDate.day == day) {
                    isFound = 1;
                    printf("为您查询到的打卡记录:\n");
                    //是否请假
                    if (temp->isAbsent == 1) {
                        printf("请假\n");
                    }
                    //若未请假，则查询上下班的打卡记录
                    else {
                        printf("上班记录:");
                        if (temp->clockInTime.isClocking == 0) {
                            printf("未打卡!\n");
                        }
                        else if (temp->clockInTime.isClocking == 1) {
                            printf("%d:%d", temp->clockInTime.hour, temp->clockInTime.minute);
                        }
                        printf("下班记录:");
                        if (temp->clockOutTime.isClocking == 0) {
                            printf("未打卡!\n");
                        }
                        else if (temp->clockOutTime.isClocking == 1) {
                            printf("%d:%d", temp->clockOutTime.hour, temp->clockOutTime.minute);
                        }
                    }
                }
                else {
                    temp = temp->next;
                }
            }
            if (isFound == 0) {
                printf("未查询到该日期!\n");
            }
        }
        else {
            printf("输入有误，请重新输入!\n");
            continue;
        }
    }
}

//查询某月打卡情况
void FindClockNotingByMonth(Employee* employee) {
    printf("请输入年份:");
    int year;
    printf("请输入月份");
    int month;
    while (employee->clockNotingData != NULL) {
        
        if (employee->clockNotingData->clockDate.year == year && employee->clockNotingData->clockDate.month == month) {
            ClockNotingByDate(employee->clockNotingData);
        }
        employee->clockNotingData= employee->clockNotingData->next;
    }
}

//定义GetClockNoting函数，用于查询员工的打卡信息,参数为指向Employee结构体的指针
void GetClockNoting(Employee* employee) {
    while (true) {
        printf("请选择您要查询的记录:\n");
        printf("0.退出\n");
        printf("1.打卡记录;\n");
        printf("2.请假记录;\n");
        printf("3.查询某日打卡记录;\n");
        printf("4.查询某月打卡记录;\n");
        //定义opertation变量，用于存储用户的输入
        int operation;
        int c;
        if (scanf("%d", &operation) != 1) {
            printf("输入有误，请重新输入!\n");
            while ((c = getchar()) != EOF && c != '\n') {
                continue;
            }
        };
        //输入0，则退出循环
        if (operation == 0) {
            return;
        }
        //输入1，则查询打卡记录
        else if (operation == 1) {
            FindClockNoting(employee);
        }
        //输入2，则查询请假记录
        else if (operation == 2) {
            FindAbsenceByDate(employee);
        }
        //输入3，查询某日打卡记录
        else if (operation == 3) {
            FindClockNotingByDate(employee);
        }
        //输入4，查询某月打卡记录
        else if (operation == 4) {
            FindClockNotingByMonth(employee);
        }
        //若未正确输入，则提示输入错误
        else {
            printf("输入有误，请重新输入!\n");
            continue;
        }
    }
}

//统计请假信息
void SortAbsenceMessege(ClockNoting* clockNoting) {
    int absenceCount = 0;
    while (clockNoting != NULL) {
        if (clockNoting->isAbsent == 1) {
            absenceCount++;
        }
        clockNoting = clockNoting->next;
    }
}

//定义InformationIntegrety函数，用于统计员工的打卡信息
void InformationSort(Employee* employee) {
    while (true) {
        printf("请输入您要执行的操作:\n");
        printf("0.退出\n");
        printf("1.请假记录统计\n");
        int operation;
        scanf("%d", &operation);
        if (operation == 0) {
            return;
        }
        else if (operation == 1) {
            SortAbsenceMessege(employee->clockNotingData);
        }
    }
}

#endif