#include "../head/administrator.h"

void queryLeaveHistorybyID() {
    char employeeID[20];
    printf("请输入员工ID: ");
    scanf("%s", employeeID);

    LeaveApplication *current = leave_head->next;
    while (current != NULL) {
        if (strcmp(current->emp_id, employeeID) == 0) {
            printf("员工ID: %s\n", current->emp_id);
            printf("员工姓名: %s\n", current->emp_name);
            printf("所属部门: %s\n", current->department);
            printf("请假天数: %d\n", current->leave_days);
            printf("请假类型: %d\n", current->leave_type);
            printf("申请时间: %s\n", current->apply_time);
            printf("审批状态: %d\n", current->status);
            printf("-----------------------------------\n");
            return;
        }
        current = current->next;
    }
    printf("未找到员工ID为%s的员工。\n", employeeID);
}

void queryLeaveHistorybystatus() {
    int status;
    printf("请输入审批状态 (0:待审批, 1:已批准, 2:已拒绝): ");
    scanf("%d", &status);

    LeaveApplication *current = leave_head->next;
    int found = 0;
    while (current != NULL) {
        if (current->status == status) {
            printf("员工ID: %s\n", current->emp_id);
            printf("员工姓名: %s\n", current->emp_name);
            printf("所属部门: %s\n", current->department);
            printf("请假天数: %d\n", current->leave_days);
            printf("请假类型: %d\n", current->leave_type);
            printf("申请时间: %s\n", current->apply_time);
            printf("审批状态: %d\n", current->status);
            printf("-----------------------------------\n");
            found = 1;
        }
        current = current->next;
    }
    if (!found) {
        printf("未找到审批状态为%d的请假申请。\n", status);
    }
}

void queryLeaveHistorybyleaveType() {
    int leaveType;
    printf("请输入请假类型 (0:年假, 1:病假, 2:事假): ");
    scanf("%d", &leaveType);

    LeaveApplication *current = leave_head->next;
    int found = 0;
    while (current != NULL) {
        if (current->leave_type == leaveType) {
            printf("员工ID: %s\n", current->emp_id);
            printf("员工姓名: %s\n", current->emp_name);
            printf("所属部门: %s\n", current->department);
            printf("请假天数: %d\n", current->leave_days);
            printf("请假类型: %d\n", current->leave_type);
            printf("申请时间: %s\n", current->apply_time);
            printf("审批状态: %d\n", current->status);
            printf("-----------------------------------\n");
            found = 1;
        }
        current = current->next;
    }
    if (!found) {
        printf("未找到请假类型为%d的请假申请。\n", leaveType);
    }
}

void queryLeaveHistoryByTime()
{
    char startTime[20], endTime[20];
    printf("请输入查询的开始时间 (格式: YYYY-MM-DD): ");
    scanf("%s", startTime);
    printf("请输入查询的结束时间 (格式: YYYY-MM-DD): ");
    scanf("%s", endTime);

    LeaveApplication *current = leave_head->next;
    int found = 0;
    while (current != NULL) {
        if (strcmp(current->apply_time, startTime) >= 0 && strcmp(current->apply_time, endTime) <= 0) {
            printf("员工ID: %s\n", current->emp_id);
            printf("员工姓名: %s\n", current->emp_name);
            printf("所属部门: %s\n", current->department);
            printf("请假天数: %d\n", current->leave_days);
            printf("请假类型: %d\n", current->leave_type);
            printf("申请时间: %s\n", current->apply_time);
            printf("审批状态: %d\n", current->status);
            printf("-----------------------------------\n");
            found = 1;
        }
        current = current->next;
    }
    if (!found) {
        printf("未找到在%s到%s之间的请假申请。\n", startTime, endTime);
    }
}

void displayLeaveHistory() {
    LeaveApplication *current = leave_head->next;
    if (current == NULL) {
        printf("没有请假申请记录。\n");
        return;
    }
    while (current != NULL) {
        printf("员工ID: %s\n", current->emp_id);
        printf("员工姓名: %s\n", current->emp_name);
        printf("所属部门: %s\n", current->department);
        printf("请假天数: %d\n", current->leave_days);
        printf("请假类型: %d\n", current->leave_type);
        printf("申请时间: %s\n", current->apply_time);
        printf("审批状态: %d\n", current->status);
        printf("-----------------------------------\n");
        current = current->next;
    }
}

void queryLeaveHistoryByTimeAndID()
{
    char employeeID[20];
    char startTime[20], endTime[20];
    printf("请输入员工ID: ");
    scanf("%s", employeeID);
    printf("请输入查询的开始时间 (格式: YYYY-MM-DD): ");
    scanf("%s", startTime);
    printf("请输入查询的结束时间 (格式: YYYY-MM-DD): ");
    scanf("%s", endTime);

    LeaveApplication *current = leave_head->next;
    int found = 0;
    while (current != NULL) {
        if (strcmp(current->emp_id, employeeID) == 0 && strcmp(current->apply_time, startTime) >= 0 && strcmp(current->apply_time, endTime) <= 0) {
            printf("员工ID: %s\n", current->emp_id);
            printf("员工姓名: %s\n", current->emp_name);
            printf("所属部门: %s\n", current->department);
            printf("请假天数: %d\n", current->leave_days);
            printf("请假类型: %d\n", current->leave_type);
            printf("申请时间: %s\n", current->apply_time);
            printf("审批状态: %d\n", current->status);
            printf("-----------------------------------\n");
            found = 1;
        }
        current = current->next;
    }
    if (!found) {
        printf("未找到在%s到%s之间的请假申请。\n", startTime, endTime);
    }
}


void query_leave_history() {
    int choice;
    do {
        system("cls");
        printf("请选择查询方式:\n");
        printf("1. 按员工ID查询\n");
        printf("2. 按审批状态查询\n");
        printf("3. 按请假类型查询\n");
        printf("4. 按申请时间查询\n");
        printf("5. 显示所有请假记录\n");
        printf("6. 查询某员工某天是否请假\n");
        printf("0. 返回上级菜单\n");
        printf("请输入选择: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                queryLeaveHistorybyID();
                system("pause");
                break;
            case 2:
                queryLeaveHistorybystatus();
                system("pause");
                break;
            case 3:
                queryLeaveHistorybyleaveType();
                system("pause");
                break;
            case 4:
                queryLeaveHistoryByTime();
                system("pause");
                break;
            case 5:
                displayLeaveHistory();
                system("pause");
                break;
            case 6:
                queryLeaveHistoryByTimeAndID();
                system("pause");
                break;
            case 0:
                printf("返回上级菜单。\n");
                break;
            default:
                printf("无效选择，请重新输入。\n");
        }
    } while (choice != 0);
}