#include "../head/administrator.h"


void calculateAverageAnnualLeaveDaysInApartment()
{
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

void statisticsMenu()
{
    while (1)
    {
        int choice;
        printf("进入统计分析菜单...\n");
        printf("请选择操作：\n");
        printf("0. 返回上一级菜单\n");
        printf("1. 计算部门平均年假天数\n");
        scanf("%d", &choice);
        system("cls"); // 清屏
        switch (choice) {
            case 0:
                return;
            case 1:
                calculateAverageAnnualLeaveDaysInApartment();
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