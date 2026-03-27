#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "../common.h"
#include "employee.h"

//定义ControlEmployee函数，用于实现员工总控
void ControlEmployee(Employee* employee) {
	printf("职员姓名: %s\n", employee->employeeName);
	printf("职员ID:%d\n", employee->employeeID);
	while (true) {
		printf("请选择要执行的操作:\n");
		printf("0.退出\n");
		printf("1.打卡\n");
		printf("2.打卡记录查询\n");
        printf("3.信息统计\n");
		int operation;
		int c;
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
                if (clockingType == 1) {
                    if (clockNotingData->clockInTime.isClocking == 1) {
                        printf("您今天上班已经打过卡了，请不要重复打卡!\n");
                        break;
                    }
                    clockNotingData->clockInTime.hour = hour;
                    clockNotingData->clockInTime.minute = minute;
                    clockNotingData->clockInTime.second = second;
                    clockNotingData->clockInTime.isClocking = 1;
                    printf("打卡状态为%d\n", clockNotingData->clockInTime.isClocking);
                    clockNotingData->isAbsent = 0;
                    employee->numberOfDays++;
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
            printf("%d:%d\n", clockNotingData->clockInTime.hour, clockNotingData->clockInTime.minute);
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
            printf("%d:%d\n", clockNotingData->clockInTime.hour, clockNotingData->clockInTime.minute);
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
    while (vacationList!= NULL) {
        printf("%d.%d.%d", vacationList->start.year, vacationList->start.month, vacationList->start.day);
        printf("-");
        printf("%d.%d.%d", vacationList->end.year, vacationList->end.month, vacationList->end.day);
        printf("\t请假%d天\n", vacationList->length);
        vacationList = vacationList->next;
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
                            printf("%d:%d\n", temp->clockInTime.hour, temp->clockInTime.minute);
                        }
                        printf("下班记录:");
                        if (temp->clockOutTime.isClocking == 0) {
                            printf("未打卡!\n");
                        }
                        else if (temp->clockOutTime.isClocking == 1) {
                            printf("%d:%d\n", temp->clockOutTime.hour, temp->clockOutTime.minute);
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
            while (employee->clockNotingData != NULL) {
                if (employee->clockNotingData->clockDate.dateID/100==year*100+month) {
                    ClockNotingByDate(employee->clockNotingData);
                }
                employee->clockNotingData = employee->clockNotingData->next;
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
    if (vacation == NULL) {
        printf("还没有请假记录!\n");
        return;
    }
    int absenceCount = 0;
    Vacation* q = vacation;
    while (q != NULL) {
        absenceCount++;
        q = q->next;
    }
    Vacation** absenceMessege = (Vacation**)malloc(absenceCount * sizeof(Vacation*) * absenceCount);
    q = vacation;
    int i;
    for (i = 0; i < absenceCount; i++) {
        absenceMessege[i] = q;
        q = q->next;
    }
    printf("您的请假信息如下:\n");
    printf("您的请假次数为:%d\n", absenceCount);
    for (i = 0; i < absenceCount; i++) {
        printf("%d年%d月%d日\n", absenceMessege[i]->start.year, absenceMessege[i]->start.month, absenceMessege[i]->start.day);
        printf("-");
        printf("%d年%d月%d日\n", absenceMessege[i]->end.year, absenceMessege[i]->end.month, absenceMessege[i]->end.day);
        printf("\t请假%d天\n", absenceMessege[i]->length);
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
        while ((c = getchar()) != EOF && c != '\n');
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
                    printf("%d年%d月%d日\n", absenceMessege[i]->start.year, absenceMessege[i]->start.month, absenceMessege[i]->start.day);
                    printf("-");
                    printf("%d年%d月%d日\n", absenceMessege[i]->end.year, absenceMessege[i]->end.month, absenceMessege[i]->end.day);
                    printf("\t请假%d天\n", absenceMessege[i]->length);
                }
            }
            else if (operation == 2) {
                PopDownByDate(absenceMessege, absenceCount);
                for (i = 0; i < absenceCount; i++) {
                    printf("%d年%d月%d日\n", absenceMessege[i]->start.year, absenceMessege[i]->start.month, absenceMessege[i]->start.day);
                    printf("-");
                    printf("%d年%d月%d日\n", absenceMessege[i]->end.year, absenceMessege[i]->end.month, absenceMessege[i]->end.day);
                    printf("\t请假%d天\n", absenceMessege[i]->length);
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
    int lateCount = 0;
    int earlyCount = 0;
    while (clockNoting != NULL) {
        if (clockNoting->clockInTime.isClocking == 1) {
            if (clockNoting->clockInTime.hour < 8) {
                lateCount++;
            }
        }
        if (clockNoting->clockOutTime.isClocking == 1) {
            if (clockNoting->clockOutTime.hour > 18) {
                earlyCount++;
            }
        }
    }
    printf("您共计迟到%d次\n", lateCount);
    printf("您共计早退%d次\n", earlyCount);
}

//定义InformationIntegrety函数，用于统计员工的打卡信息
void SortInformation(Employee* employee) {
    while (true) {
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
void AddVacation(Employee* employee, Date date, int length) {
    while (employee->vacation != NULL) {
        employee->vacation = employee->vacation->next;
    }
    Vacation* vacation = (Vacation*)malloc(sizeof(Vacation));
    vacation->start = date;
    vacation->start.dateID = vacation->start.year * 10000 + vacation->start.month * 100 + vacation->start.day;
    vacation->length = length;
    vacation->end = CalculateDate(date, length);
    vacation->end.dateID = vacation->end.year * 10000 + vacation->end.month * 100 + vacation->end.day;
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