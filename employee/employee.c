#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "../head/common.h"
#include "../head/employee.h"

//定义ControlEmployee函数，用于实现员工总控
void ControlEmployee(Employee* employee) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
	printf("职员姓名: %s\n", employee->employeeName);
	printf("职员ID:%d\n", employee->employeeID);
	while (true) {
        printf("========================================\n");
		printf("请选择要执行的操作:\n");
		printf("0.退出\n");
		printf("1.打卡\n");
		printf("2.打卡记录查询\n");
        printf("3.信息统计\n");
        printf("4.请假\n");
		int operation;
		char input[20];
		if (fgets(input, sizeof(input), stdin) == NULL) {
			printf("输入有误!请重新输入!\n");
			continue;
		}
        if (strchr(input, '\n') == NULL) {
            while ((c = getchar()) != EOF && c != '\n');
        }
		int res = sscanf(input, "%d", &operation);
		if (res != 1) {
			printf("读取失败!请重新尝试!\n");
			continue;
		}
		if (operation == 0) {
            printf("正在退出...\n");
            return;
		}
		else if (operation == 1) {
			Clock(employee);
		}
		else if (operation == 2) {
			GetClockNoting(employee);
		}
        else if (operation == 3) {
            SortInformation(employee);
        }
        else if (operation == 4) {
            ApplyForVacation(employee);
        }
		else {
			printf("输入错误，请重新输入！\n");
			continue;
		}
	}

}

//定义FindDay函数，用于查找某日的打卡记录，参数为指向ClockNoting结构体的指针、指向Vacation结构体的指针、年、月、日
ClockNoting* FindDay(ClockNoting** origDate, Vacation* vacationList, int year, int month, int day) {
    //如果头节点为空，则创建一个头节点
    if ((*origDate) == NULL) {
        (*origDate) = (ClockNoting*)malloc(sizeof(ClockNoting));
        (*origDate)->clockDate.year = 0;
        (*origDate)->clockDate.month = 0;
        (*origDate)->clockDate.day = 0;
        (*origDate)->clockDate.dateID = 0;
        (*origDate)->clockInTime.isClocking = 0;
        (*origDate)->clockInTime.minute = 0;
        (*origDate)->clockOutTime.isClocking = 0;
        (*origDate)->clockOutTime.hour = 0;
        (*origDate)->clockOutTime.minute = 0;
        (*origDate)->next = NULL;
    }

    ClockNoting* q = (*origDate);
    while (q != NULL) {
        if (q->clockDate.dateID==year*10000+month*100+day) {
            return q;
        }
        q = q->next;
    }
    ClockNoting* newDate = (ClockNoting*)malloc(sizeof(ClockNoting));
    newDate->clockDate.year = year;
    newDate->clockDate.month = month;
    newDate->clockDate.day = day;
    newDate->clockDate.dateID = year * 10000 + month * 100 + day;
    newDate->clockInTime.isClocking = 0;
    newDate->clockOutTime.isClocking = 0;
    newDate->isAbsent = 0;
    newDate->next = NULL;
    while (vacationList != NULL) {
        if (vacationList->start.dateID <= newDate->clockDate.dateID && vacationList->end.dateID >= newDate->clockDate.dateID) {
            newDate->isAbsent = 1;
            break;
        }
        vacationList=vacationList->next;
    }
    q = (*origDate);
    if (q->next==NULL) {
        q->next=newDate;
        return newDate;
    }
    else {
        while (q != NULL && q->next != NULL) {
            if (q->clockDate.dateID<newDate->clockDate.dateID && q->next->clockDate.dateID>newDate->clockDate.dateID) {
                newDate->next = q->next;
                q->next = newDate;
                break;
            }
            q = q->next;
            if (q->next == NULL) {
                q->next = newDate;
                break;
            }
        }
    }
    return newDate;
}

// 定义Clock函数，用于处理员工打卡操作，参数为指向Employee结构体的指针
bool Clock(Employee* employee) {
    while (true) {
        printf("========================================\n");
        printf("请选择打卡类型:\n");
        printf("0.返回\t1.上班\t2.下班\n");
        int clockingType;
        char input[20];
        int c;
        if ((fgets(input, sizeof(input), stdin)) == NULL) {
            printf("输入有误!请重新输入!\n");
            continue;
        }
        while (strchr(input, '\n') == NULL) {
            while ((c = getchar()) != EOF && c != '\n');
        }
        int res = sscanf(input, "%d", &clockingType);
        if (res != 1) {
            printf("数据解析失败，请重新输入!\n");
            continue;
        }
        if (clockingType == 0) {
            return false;
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
            if (fgets(input, sizeof(input), stdin) == NULL) {
                printf("输入错误，请重新输入!\n");
                continue;
            }
            if (strchr(input, '\n') == NULL) {
                while ((c = getchar()) != EOF && c != '\n');
            }
            res = sscanf(input, "%d", &clocking);
            if (res != 1) {
                printf("输入错误，请重新输入!\n");
                continue;
            }

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
                time_t now = time(NULL);
                struct tm* localTime = localtime(&now);
                char time_str[64];
                strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localTime);
                printf("当前时间为: %s\n", time_str);
                int year, month, day, hour, minute, second;
                sscanf(time_str, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
                ClockNoting* clockNotingData = FindDay(&(employee->clockNotingData), employee->vacation, year, month, day);
                int isClock = 0;
                if (clockingType == 1) {
                    if (clockNotingData->clockInTime.isClocking == 1) {
                        printf("您今天上班已经打过卡了，请不要重复打卡!\n");
                        break;
                    }
                    clockNotingData->clockInTime.hour = hour;
                    clockNotingData->clockInTime.minute = minute;
                    clockNotingData->clockInTime.second = second;
                    clockNotingData->clockInTime.isClocking = 1;
                    clockNotingData->isAbsent = 0;
                    employee->numberOfDays++;
                    isClock = 1;
                }
                else if (clockingType == 2) {
                    if (clockNotingData->clockInTime.isClocking == 0) {
                        printf("请先进行上班打卡!\n");
                        break;
                    }
                    if (clockNotingData->clockOutTime.isClocking == 1) {
                        printf("您今天下班已经打过卡了，请不要重复打卡!\n");
                        break;
                    }
                    clockNotingData->clockOutTime.hour = hour;
                    clockNotingData->clockOutTime.minute = minute;
                    clockNotingData->clockOutTime.second = second;
                    clockNotingData->clockOutTime.isClocking = 1;
                    isClock = 1;
                }
                if (isClock == 1) {
                    FILE* fp = fopen("../data/check_in_record.csv", "a");
                    if (fp == NULL) {
                        printf("无法打开文件！保存打卡记录失败！\n");
                    }
                    fprintf(fp, "%03d,%s,%s,%d-%d-%d %d:%d:%d,%s\n",
                        employee->employeeID, employee->employeeName,
                        employee->departmentName,
                        year, month, day, hour, minute, second,
                        JudgeClockingState(clockNotingData, clockingType));
                    fclose(fp);
                }
                printf("打卡成功!\n");
                return true;
            }

            // 如果用户选择取消打卡（输入2）
            if (clocking == 2) {
                printf("取消打卡\n"); // 打印取消打卡提示
                return false; // 返回false，表示未打卡
            }

            // 如果用户选择返回（输入0）
            if (clocking == 0) {
                printf("返回到上一个界面\n"); // 打印返回提示
                continue; // 继续下一次循环
            }

            return false; // 这里实际上是多余的，因为在clocking == 1和2时已经返回
        }
        return false; // 这里也是多余的，因为在while(true)循环中不会执行到这里
    }
}

//某日的打卡情况
void ClockNotingByDate(ClockNoting* clockNotingData) {
    printf("%d年%d月%d日打卡情况:\n", clockNotingData->clockDate.year, clockNotingData->clockDate.month, clockNotingData->clockDate.day);
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
            printf("%02d:%02d\n", clockNotingData->clockInTime.hour, clockNotingData->clockInTime.minute);
        }
        else {
            printf("状态未知!\n");
            //实际上是多余的，因为isClocking只能取0、1两种值
        }
        //对下班的打卡时间查询
        printf("下班:");
        if (clockNotingData->clockOutTime.isClocking == 0) {
            printf("未打卡!\n");
        }
        else if (clockNotingData->clockOutTime.isClocking == 1) {
            printf("%02d:%02d\n", clockNotingData->clockOutTime.hour, clockNotingData->clockOutTime.minute);
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

//查询打卡记录的函数
void FindClockNoting(Employee* employee) {
    ClockNoting* q = employee->clockNotingData->next;
    printf("您已积累打卡%d天\n", employee->numberOfDays);
    while (q != NULL) {
        ClockNotingByDate(q);
        q = q->next;
    }
}

//查询请假日期
void FindAbsenceByDate(Vacation* vacationList) {
    printf("请假的日期为:\n");
    if (vacationList == NULL) {
        printf("暂无请假记录!\n");
    }
    Vacation* q = vacationList->next;
    while (q!= NULL) {
        printf("%d.%d.%d", q->start.year, q->start.month, q->start.day);
        printf("-");
        printf("%d.%d.%d", q->end.year, q->end.month, q->end.day);
        printf(":请假%d天\n", q->length);
        q = q->next;
    }
}

//查询某日打卡记录的函数
void FindClockNotingByDate(Employee* employee) {
    if (employee->clockNotingData == NULL) {
        printf("您还没有打卡记录!\n");
        return;
    }
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
        while (strchr(input, '\n') == NULL) {
            while ((c = getchar()) != EOF && c != '\n');
        }
        scanCount = sscanf(input, "%d.%d.%d", &year, &month, &day);
        if (scanCount == 1 && year == 0) {
            printf("返回到上一界面\n");
            break;
        }
        else if (scanCount == 3) {
            if (!JudgeDate(year, month, day)) {
                printf("请重新输入!\n");
                continue;
            }
            printf("您选择的日期为%d年%d月%d日\n", year, month, day);
            //查询该日期的打卡记录
            ClockNoting* temp = employee->clockNotingData;
            int isFound = 0; //是否找到该日期的打卡记录
            while (temp != NULL) {
                if (temp->clockDate.dateID == year * 10000 + month * 100 + day) {
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
                            printf("%02d:%02d\n", temp->clockInTime.hour, temp->clockInTime.minute);
                        }
                        printf("下班记录:");
                        if (temp->clockOutTime.isClocking == 0) {
                            printf("未打卡!\n");
                        }
                        else if (temp->clockOutTime.isClocking == 1) {
                            printf("%02d:%02d\n", temp->clockOutTime.hour, temp->clockOutTime.minute);
                        }
                    }
                    break;
                }
                else {
                    temp = temp->next;
                }
            }
            if (isFound == 0) {
                printf("未查询到该日期!\n");
                continue;
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
    while (true) {
        int year;
        int month;
        int c;
        printf("请输入要查询的年份和月份，格式为yyyy.mm,(输入0返回):");
        char input[20];
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("数据解析失败,请重新输入!\n");
            continue;
        }
        while (strchr(input, '\n') == NULL) {
            while ((c = getchar()) != EOF || c != '\n');
        }
        int res = sscanf(input, "%d.%d", &year, &month);
        if (res == 1 && year == 0) {
            break;
        }
        else if (res == 2) {
            if (!JudgeDate(year, month, 1)) {
                printf("请重新输入\n");
                continue;
            }
            int isFound = 0;
            ClockNoting* q = employee->clockNotingData;
            while (q != NULL) {
                if (q->clockDate.dateID/100==year*100+month) {
                    ClockNotingByDate(q);
                    isFound = 1;
                }
                q = q->next;
            }
            if (isFound == 0) {
                printf("未找到当月打卡记录!\n");
            }
        }
        else {
            printf("输入有误，请重新输入!\n");
            continue;
        }
    }
}

//定义GetClockNoting函数，用于查询员工的打卡信息,参数为指向Employee结构体的指针
void GetClockNoting(Employee* employee) {
    while (true) {
        printf("========================================\n");
        printf("请选择您要查询的记录:\n");
        printf("0.退出\n");
        printf("1.打卡记录;\n");
        printf("2.请假记录;\n");
        printf("3.查询某日打卡记录;\n");
        printf("4.查询某月打卡记录;\n");
        //定义opertation变量，用于存储用户的输入
        char input[20];
        int operation;
        int c;
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("数据解析失败，请重新输入!\n");
            continue;
        }
        if (strchr(input, '\n') == NULL) {
            while ((c = getchar()) != EOF && c != '\n');
        }
        int res = sscanf(input, "%d", &operation);
        if (res != 1) {
            printf("输入错误，请重新输入!\n");
            continue;
        }
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
            FindAbsenceByDate(employee->vacation);
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

//定义Pop函数，用来为某种信息进行降序排序
//按请假时长
void PopDownByLength(Vacation** messeges, int length) {
    int i, j;
    for (i = 0; i < length; i++) {
        int max = i;
        for (j = i; j < length; j++) {
            if (messeges[j]->length > messeges[max]->length) {
                max = j;
            }
        }
        Vacation* temp = messeges[i];
        messeges[i] = messeges[max];
        messeges[max] = temp;
    }
}
//按请假日期
void PopDownByDate(Vacation** messeges, int length) {
    int i, j;
    for (i = 0; i < length; i++) {
        int max = i;
        for (j = i; j < length; j++) {
            if (messeges[j]->start.dateID > messeges[max]->start.dateID) {
                max = j;
            }
        }
        Vacation* temp = messeges[i];
        messeges[i] = messeges[max];
        messeges[max] = temp;
    }
}

//统计请假信息
void SortAbsenceMessege(Vacation* vacation) {
    if (vacation==NULL || vacation->next==NULL) {
        printf("还没有请假记录!\n");
        return;
    }
    Vacation* q = vacation->next;
    int absenceCount = 0;
    while (q != NULL) {
        absenceCount++;
        q = q->next;
    }
    Vacation** absenceMessege = (Vacation**)malloc(absenceCount * sizeof(Vacation*) * absenceCount);
    int i;
    q=vacation->next;
    for (i = 0; i < absenceCount; i++) {
        absenceMessege[i] = q;
        q = q->next;
    }
    printf("您的请假信息如下:\n");
    printf("您的请假次数为:%d\n", absenceCount);
    for (i = 0; i < absenceCount; i++) {
        printf("%d年%d月%d日", absenceMessege[i]->start.year, absenceMessege[i]->start.month, absenceMessege[i]->start.day);
        printf("-");
        printf("%d年%d月%d日", absenceMessege[i]->end.year, absenceMessege[i]->end.month, absenceMessege[i]->end.day);
        printf(":请假%d天\n", absenceMessege[i]->length);
    }
    while (true) {
        printf("请选择要执行的操作:\n");
        printf("0.返回\n");
        printf("1.按请假天数降序排序\n");
        printf("2.按请假日期降序排序\n");
        int operation;
        int c;
        char input[20];
        if ((fgets(input, sizeof(input), stdin) == NULL)) {
            printf("数据解析失败，请重试!\n");
            continue;
        }
        while (strchr(input, '\n') == NULL) {
            while ((c = getchar()) != EOF && c != '\n');
        }
        int res = sscanf(input, "%d", &operation);
        if (res != 1) {
            printf("输入错误，请重新输入!\n");
            continue;
        }
        else {
            if (operation == 0) {
                return;
            }
            else if (operation == 1) {
                PopDownByLength(absenceMessege, absenceCount);
                for (i = 0; i < absenceCount; i++) {
                    printf("%d年%d月%d日", absenceMessege[i]->start.year, absenceMessege[i]->start.month, absenceMessege[i]->start.day);
                    printf("-");
                    printf("%d年%d月%d日", absenceMessege[i]->end.year, absenceMessege[i]->end.month, absenceMessege[i]->end.day);
                    printf(":请假%d天\n", absenceMessege[i]->length);
                }
            }
            else if (operation == 2) {
                PopDownByDate(absenceMessege, absenceCount);
                for (i = 0; i < absenceCount; i++) {
                    printf("%d年%d月%d日", absenceMessege[i]->start.year, absenceMessege[i]->start.month, absenceMessege[i]->start.day);
                    printf("-");
                    printf("%d年%d月%d日", absenceMessege[i]->end.year, absenceMessege[i]->end.month, absenceMessege[i]->end.day);
                    printf(":请假%d天\n", absenceMessege[i]->length);
                }
            }
        }
    }
}

//统计请假天数
void SortAbsenceDays(Vacation* vacation) {
    int sumOfDays = 0;
    while (vacation != NULL) {
        sumOfDays += vacation->length;
        vacation = vacation->next;
    }
    printf("您请假的总天数为%d天\n", sumOfDays);
}

//统计迟到、早退天数
void UnpunctuatedDays(ClockNoting* clockNoting) {
    if (clockNoting == NULL || clockNoting->next == NULL) {
        printf("还没有打卡信息!\n");
        return;
    }
    int lateCount = 0;
    int earlyCount = 0;
    ClockNoting* p = clockNoting->next;
    while (p!= NULL) {
        if (p->clockInTime.isClocking == 1) {
            if ((p->clockInTime.hour == 8 && p->clockInTime.minute>30) || p->clockInTime.hour>8) {
                lateCount++;
            }
        }
        if (p->clockOutTime.isClocking == 1) {
            if (p->clockOutTime.hour < 18) {
                earlyCount++;
            }
        }
        p = p->next;
    }
    printf("您共计迟到%d次\n", lateCount);
    printf("您共计早退%d次\n", earlyCount);
}

//定义InformationIntegrety函数，用于统计员工的打卡信息
void SortInformation(Employee* employee) {
    while (true) {
        printf("========================================\n");
        printf("请输入您要执行的操作:\n");
        printf("0.退出\n");
        printf("1.请假记录统计\n");
        printf("2.请假时长统计\n");
        printf("3.迟到、早退天数统计\n");
        int operation;
        int c;
        char input[20];
        if ((fgets(input, sizeof(input), stdin) == NULL)) {
            printf("数据解析失败,请重新输入!\n");
            continue;
        }
        while (strchr(input, '\n') == NULL) {
            while ((c = getchar()) != EOF && c != '\n');
        }
        int res = sscanf(input, "%d", &operation);
        if (res != 1) {
            printf("输入错误，请重新输入!\n");
            continue;
        }
        if (operation == 0) {
            return;
        }
        else if (operation == 1) {
            SortAbsenceMessege(employee->vacation);
        }
        else if (operation == 2) {
            SortAbsenceDays(employee->vacation);
        }
        else if (operation == 3) {
            UnpunctuatedDays(employee->clockNotingData);
        }
        else {
            printf("输入错误，请重新输入!\n");
            continue;
        }
    }
}

//定义CalculateDate,用来计算日期
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

//定义AddVacation函数，用来为员工添加请假信息
void AddVacation(Employee* employee, int type, int year,int month,int day, int length, int state) {
    if (employee->vacation == NULL) {
        employee->vacation = (Vacation*)malloc(sizeof(Vacation));
        employee->vacation->start.year = 0;
        employee->vacation->start.month = 0;
        employee->vacation->start.day = 0;
        employee->vacation->start.dateID = 0;
        employee->vacation->end.year = 0;
        employee->vacation->end.month = 0;
        employee->vacation->end.day = 0;
        employee->vacation->end.dateID = 0;
        employee->vacation->length = 0;
        employee->vacation->holidayType = 0;
        employee->vacation->holidyStatus = 0;
        employee->vacation->next = NULL;
    }
    Vacation* p = employee->vacation;
    while (p->next != NULL) {
        p = p->next;
    }
    Date date;
    date.year = year;
    date.month = month;
    date.day = day;

    Vacation* vacation = (Vacation*)malloc(sizeof(Vacation));
    vacation->start = date;
    vacation->start.dateID = vacation->start.year * 10000 + vacation->start.month * 100 + vacation->start.day;
    vacation->length = length;
    vacation->end = CalculateDate(date, length);
    vacation->end.dateID = vacation->end.year * 10000 + vacation->end.month * 100 + vacation->end.day;
    vacation->holidayType = type;
    vacation->holidyStatus = state;
    vacation->next = NULL;
    p->next = vacation;
}

//定义JudgeDate函数，用来判断日期是否合法
bool JudgeDate(int year, int month, int day) {
    if (month > 12 || month < 1) {
        printf("日期不合法！\n");
        return false;
    }
    int standeredYear[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
        standeredYear[2] = 29;
    }
    else {
        standeredYear[2] = 28;
    }
    if (day > standeredYear[month] || day < 1) {
        printf("日期不合法!\n");
        return false;
    }
    return true;
}

//定义ApplyForVacation函数，用来为员工请假
void ApplyForVacation(Employee* employee)
{
    while (true) {
        printf("========================================");
        printf("要进行请假吗?\n");
        printf("1.是\t2.否\n");
        int c;
        char input[20];
        int operation;
        if ((fgets(input, sizeof(input), stdin)) == NULL) {
            printf("数据解析失败，请重试!\n");
            continue;
        }
        while (strchr(input, '\n') == NULL) {
            while ((c = getchar()) != EOF && c != '\n');
        }
        int res = sscanf(input, "%d", &operation);
        if (res != 1) {
            printf("输入有误，请重新输入!\n");
        }
        else {
            if (operation == 2) {
                return;
            }
            else if (operation == 1) {
                FILE* fp = fopen("../data/leave_applications.csv", "a");
                if (fp == NULL)
                {
                    printf("打开文件失败！无法进行申请!\n");
                    return;
                }
                int year = 0, month = 0, day = 0;
                int length;
                while (true)
                {
                    printf("请输入假期类型：\n");
                    printf("0.返回\n");
                    printf("1.事假\n");
                    printf("2.病假\n");
                    printf("3.年假\n");
                    if ((fgets(input, sizeof(input), stdin)) == NULL) {
                        printf("数据解析失败，请重试!\n");
                        continue;
                    }
                    while (strchr(input, '\n') == NULL) {
                        while ((c = getchar()) != EOF && c != '\n');
                    }
                    int res=sscanf(input, "%d", &operation);
                    if (operation == 0)
                    {
                        printf("返回上一界面...\n");
                        break;
                    }
                    else if (operation != 1 && operation != 2 && operation != 3) {
                        printf("您的输入有误，请重新输入!\n");
                        continue;
                    }
                    break;
                }
                if (operation == 0) {
                    continue;
                }
                else {
                    while (true)
                    {
                        printf("请输入请假开始时间yyyy.mm.dd:\n");
                        if ((fgets(input, sizeof(input), stdin)) == NULL) {
                            printf("数据解析失败，请重新输入!\n");
                            continue;
                        }
                        while (strchr(input, '\n') == NULL) {
                            while ((c = getchar()) != EOF && c != '\n');
                        }
                        int res = sscanf(input, "%d.%d.%d", &year, &month, &day);
                        if (res != 3) {
                            printf("输入有误,请重新输入!\n");
                        }
                        else {
                            if (!JudgeDate(year, month, day)) {
                                printf("请重新输入!\n");
                                continue;
                            }
                            break;
                        }
                    }
                    while (true)
                    {
                        printf("请输入请假长度(天):\n");
                        if ((fgets(input, sizeof(input), stdin)) == NULL) {
                            printf("数据解析失败，请重试!\n");
                            continue;
                        }
                        while (strchr(input, '\n') == NULL) {
                            while ((c = getchar()) != EOF && c != '\n');
                        }
                        int res = sscanf(input, "%d", &length);
                        if (res != 1) {
                            printf("输入有误，请重新输入!\n");
                            continue;
                        }
                        break;
                    }
                    fprintf(fp, "%d,%s,%d,%d,%d,%d-%d-%d,1\n", employee->employeeID,employee->employeeName ,employee->departmentID, operation, length, year, month, day);
                    AddVacation(employee, operation, year, month, day, length, 1);
                    printf("申请成功！请等待审批！\n");
                    Sleep(1000);
                    fclose(fp);
                    continue;
                }
            }
            else {
                printf("输入有误，请重新输入!\n");
                continue;
            }
        }
    }
}

//用来保存员工信息
void SaveEmployee(Employee* employee) {
    ClockNoting* q = employee->clockNotingData;
    if (q == NULL || q->next == NULL) {
        printf("打卡信息不存在!\n");
        return;
    }
    q = q->next;
    FILE* fp = fopen("../data/check_in_record.csv", "a");
    if (fp == NULL) {
        printf("文件打开失败!保存失败!\n");
        return;
    }
    while (q != NULL) {
        fprintf(fp, "%03d,%s,%s,%d-%d-%d %02d:%02d:%02d,%s\n",
            employee->employeeID,
            employee->employeeName,
            employee->departmentName,
            q->clockDate.year,
            q->clockDate.month,
            q->clockDate.day,
            q->clockInTime.hour,
            q->clockInTime.minute,
            q->clockInTime.second,
            JudgeClockingState(q, 1)
        );
        fprintf(fp, "%03d,%s,%s,%d-%d-%d %02d:%02d:%02d,%s\n",
            employee->employeeID,
            employee->employeeName,
            employee->departmentName,
            q->clockDate.year,
            q->clockDate.month,
            q->clockDate.day,
            q->clockOutTime.hour,
            q->clockOutTime.minute,
            q->clockOutTime.second,
            JudgeClockingState(q, 2)
        );
        q = q->next;
    }
    printf("信息保存成功!\n");
    fclose(fp);
}

//用来判断打卡状态
const char* JudgeClockingState(ClockNoting* clockNoting,int kind) {
    if (kind == 1) {
        if (clockNoting->clockInTime.isClocking == 1) {
            if (clockNoting->clockInTime.hour >= 8) {
                return "迟到";
            }
            else {
                return "下班";
            }
        }
        else {
            return "未打卡";
        }
    }
    else if (kind == 2) {
        if (clockNoting->clockOutTime.isClocking == 1) {
            if (clockNoting->clockOutTime.hour < 18) {
                return "早退";
            }
            else {
                return "正常";
            }
        }
        else {
            return "未打卡";
        }
    }
    else {
        return "未知";
    }
}

//用来读取员工打卡信息
void GetClockInfo(Employee* employee) {
    employee->clockNotingData = (ClockNoting*)malloc(sizeof(ClockNoting));
    employee->clockNotingData->next = NULL;
    employee->clockNotingData->isAbsent = 0;
    employee->clockNotingData->clockDate.year = 0;
    employee->clockNotingData->clockDate.month = 0;
    employee->clockNotingData->clockDate.day = 0;
    employee->clockNotingData->clockInTime.hour = 0;
    employee->clockNotingData->clockInTime.minute = 0;
    employee->clockNotingData->clockInTime.second = 0;
    employee->clockNotingData->clockInTime.isClocking = 0;
    employee->clockNotingData->clockOutTime.hour = 0;
    employee->clockNotingData->clockOutTime.minute = 0;
    employee->clockNotingData->clockOutTime.second = 0;
    employee->clockNotingData->clockOutTime.isClocking = 0;
    employee->numberOfDays = 0;
    FILE* fp = fopen("../data/check_in_record.csv", "r");
    if (fp == NULL) {
        printf("打卡信息不存在!\n");
        return;
    }
    char line[256];
    fgets(line, sizeof(line), fp);
    while (fgets(line, sizeof(line), fp) != NULL) {
        line[strcspn(line, "\n")] = 0;
        int ID;
        char name[20];
        char departmentName[20];
        int year;
        int month;
        int day;
        int hour;
        int minute;
        int second;
        char state[20];
        int res = sscanf(line, "%d,%[^,],%[^,],%d-%d-%d %d:%d:%d,%[^\n]", &ID, name, departmentName, &year, &month, &day, &hour, &minute, &second, state);
        if (res != 10) {
            printf("文件损坏!\n");
            continue;
        }
        if (ID == employee->employeeID) {
            printf("%s\n", line);
            int kind=JudgeClockingKind(state);
            if (kind == 0) {
                printf("未知打卡信息!\n");
                continue;
            }
            ClockNoting* q = employee->clockNotingData;
            int dateID = year * 10000 + month * 100 + day;
            int find = 0;
            while (q != NULL) {
                if (q->clockDate.dateID == dateID) {
                    find = 1;
                    break;
                }
                q = q->next;
            }
            if (find == 0) {
                employee->numberOfDays++;
            }
            if (q == NULL) {
                q = (ClockNoting*)malloc(sizeof(ClockNoting));
                q->clockDate.year = year;
                q->clockDate.month = month;
                q->clockDate.day = day;
                q->clockDate.dateID = dateID;
                q->isAbsent = 0;
                q->clockInTime.isClocking = 0;
                q->clockOutTime.isClocking = 0;
                if (kind == 1) {
                    q->clockInTime.hour = hour;
                    q->clockInTime.minute = minute;
                    q->clockInTime.second = second;
                    q->clockInTime.isClocking = 1;
                }
                else {
                    q->clockOutTime.hour= hour;
                    q->clockOutTime.minute = minute;
                    q->clockOutTime.second = second;
                    q->clockOutTime.isClocking = 1;
                }
                q->next = NULL;
                ClockNoting* p = employee->clockNotingData;
                while (p->next != NULL) {
                    p = p->next;
                }
                p->next = q;
            }
            else {
                if (kind == 1) {
                    q->clockInTime.hour = hour;
                    q->clockInTime.minute = minute;
                    q->clockInTime.second = second;
                    q->clockInTime.isClocking = 1;
                }
                else {
                    q->clockOutTime.hour = hour;
                    q->clockOutTime.minute = minute;
                    q->clockOutTime.second = second;
                    q->clockOutTime.isClocking = 1;
                }
            }
        }
    }
    printf("打卡信息加载结束\n");
    fclose(fp);
}

//用来读取员工假期信息
void GetVacationInfo(Employee* employee) {
    employee->vacation = (Vacation*)malloc(sizeof(Vacation));
    employee->vacation->next = NULL;
    employee->vacation->start.year = 0;
    employee->vacation->start.month = 0;
    employee->vacation->start.day = 0;
    employee->vacation->start.dateID = 0;
    employee->vacation->length = 0;
    employee->vacation->end.year = 0;
    employee->vacation->end.month = 0;
    employee->vacation->end.day = 0;
    employee->vacation->end.dateID = 0;
    FILE* fp = fopen("../data/leave_applications.csv", "r");
    if (fp == NULL) {
        printf("假期信息不存在!\n");
        return;
    }
    char line[256];
    fgets(line, sizeof(line), fp);
    while (fgets(line, sizeof(line), fp) != NULL) {
        line[strcspn(line, "\n")] = 0;
        int ID;
        char name[20];
        char departmentName[20];
        int type;
        int length;
        int year;
        int month;
        int day;
        int state;
        int res = sscanf(line, "%d,%[^,],%[^,],%d,%d,%d-%d-%d,%d", &ID, name, departmentName, &type, &length, &year, &month, &day, &state);
        if (res != 9) {
            printf("文件损坏!请检查文件是否完整!\n");
            continue;
        }
        if (employee->employeeID == ID) {
            AddVacation(employee, type, year, month, day, length, state);
        }
    }
    printf("假期信息加载结束\n");
    fclose(fp);
}

//用来判断打卡的类型
int JudgeClockingKind(char* state) {
    if (strcmp(state, "迟到") == 0 || strcmp(state,"正常")==0) {
        return 1;
    }
    else if (strcmp(state, "早退") == 0 || strcmp(state, "下班") == 0) {
        return 2;
    }
    else {
        return 0;
    }
}

//用来读取员工信息
void GetEmployeeInfo(Employee* employee) {
    GetClockInfo(employee);
    GetVacationInfo(employee);
}