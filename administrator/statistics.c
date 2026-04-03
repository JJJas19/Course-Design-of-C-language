#include "../head/administrator.h"


void calculateAverageAnnualLeaveDaysInApartment()
{
    displayDepartmentList();
    char departmentName[MAX_NAME_LENGTH];
    printf("请输入部门名称: ");
    scanf("%s", departmentName);
    LeaveApplication *current = leave_head->next;
    int totalLeaveDays = 0;
    int employeeCount = 0;
    while (current != NULL) {
        if (strcmp(current->department, departmentName) == 0) {
            totalLeaveDays += current->leave_days;
            employeeCount++;
        }
        current = current->next;
    }
    if (employeeCount > 0) {
        double average = (double)totalLeaveDays / employeeCount;
        printf("部门 %s 的平均年假天数为: %.2f 天\n", departmentName, average);
    } else {
        printf("未找到该部门的员工记录\n");
    }
}

int countAfterTime(int year, int month, int day, int hour, int minute)
{
    int count = 0;
    Employee *emp = employeeHead->next;

    while (emp != NULL)
    {
        if (emp->clockNotingData == NULL) {
            emp = emp->next;
            continue;
        }

        ClockNoting *record = emp->clockNotingData;

        while (record != NULL)
        {
            if (record->clockDate.year == year &&
                record->clockDate.month == month &&
                record->clockDate.day == day)
            {
                // 跳过缺勤
                if (record->isAbsent == 1) {
                    break;
                }
                // 判断是否在指定时间之后
                if (record->clockInTime.hour > hour ||
                   (record->clockInTime.hour == hour && record->clockInTime.minute > minute))
                {
                    count++;
                }
                break;
            }
            record = record->next;
        }
        emp = emp->next;
    }
    return count;
}

int countByDepartmentAndTimeRange(char *department, 
                                  int year, int month, int day,
                                  int startHour, int startMin,
                                  int endHour, int endMin)
{
    int count = 0;
    Employee *emp = employeeHead->next;

    while (emp != NULL)
    {
        if (strcmp(emp->departmentName, department) != 0) {
            emp = emp->next;
            continue;
        }

        if (emp->clockNotingData == NULL) {
            emp = emp->next;
            continue;
        }

        ClockNoting *record = emp->clockNotingData;

        while (record != NULL)
        {
            if (record->clockDate.year == year &&
                record->clockDate.month == month &&
                record->clockDate.day == day)
            {
                if (record->isAbsent == 1) {
                    break;
                }

                int h = record->clockInTime.hour;
                int m = record->clockInTime.minute;

                int afterStart = (h > startHour) || (h == startHour && m >= startMin);
                int beforeEnd  = (h < endHour)   || (h == endHour && m <= endMin);

                if (afterStart && beforeEnd) {
                    count++;
                }

                break; // 每人一天只算一次
            }
            record = record->next;
        }
        emp = emp->next;
    }

    return count;
}

void statisticsMenu()
{
    while (1)
    {
        int choice;
        printf("进入统计分析菜单...\n");
        printf("请选择操作：\n");
        printf("0. 返回上一级菜单\n");
        printf("1. 计算部门平均年假天数\n");
        printf("2. 统计某时间之后打卡的员工数量\n");
        printf("3. 统计部门在某时间范围内某部门打卡的员工数量\n");
        scanf("%d", &choice);
        system("cls"); // 清屏
        int year, month, day, hour, minute;
        switch (choice) {
            case 0:
                return;
            case 1:
                calculateAverageAnnualLeaveDaysInApartment();
                system("pause");
                system("cls");
                break;
            case 2:
                printf("请输入时间 (年 月 日 时 分): ");
                scanf("%d %d %d %d %d", &year, &month, &day, &hour, &minute);
                int count = countAfterTime(year, month, day, hour, minute);
                printf("在 %d-%02d-%02d %02d:%02d 之后打卡的员工数量为: %d\n", year, month, day, hour, minute, count);
                system("pause");
                system("cls");
                break;
            case 3:
                displayDepartmentList();
                char department[100];
                int startHour, startMin, endHour, endMin;
                printf("请输入部门名称: ");
                scanf("%s", department);
                printf("请输入日期 (年 月 日): ");
                scanf("%d %d %d", &year, &month, &day);
                printf("请输入时间范围 (开始时 分 结束时 分): ");
                scanf("%d %d %d %d", &startHour, &startMin, &endHour, &endMin);
                count = countByDepartmentAndTimeRange(department, year, month, day, startHour, startMin, endHour, endMin);
                printf("在 %d-%02d-%02d %02d:%02d 到 %02d:%02d 之间，%s 部门打卡的员工数量为: %d\n", year, month, day, startHour, startMin, endHour, endMin, department, count);
                system("pause");
                system("cls");
                break;

            default:    
                printf("无效的操作编号，请重新选择。\n");
                system("pause");
                system("cls");
                break;

        }
    }
}