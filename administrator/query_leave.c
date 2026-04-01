#include "../head/administrator.h"

LeaveApplication *queryResult = NULL;

void initQueryResult() {
    queryResult = (LeaveApplication*)malloc(sizeof(LeaveApplication));
    queryResult->next = NULL;
}

void freeQueryResult() {
    LeaveApplication *current = queryResult;
    while (current != NULL) {
        LeaveApplication *temp = current;
        current = current->next;
        free(temp);
    }
    queryResult = NULL;
}

void printQueryResult() {
    LeaveApplication *point = queryResult->next;
    if (point == NULL) {
        printf("没有符合条件的请假记录。\n");
        return;
    }
    while (point != NULL)
    {
        printf("员工ID: %s\n", point->emp_id);
        printf("员工姓名: %s\n", point->emp_name);
        printf("所属部门: %s\n", point->department);
        printf("请假天数: %d\n", point->leave_days);
        printf("请假类型: %d\n", point->leave_type);
        printf("申请时间: %s\n", point->apply_time);
        printf("审批状态: %d\n", point->status);
        printf("-----------------------------------\n");
        point = point->next;
    }
}

void addqueryResultNode(LeaveApplication *application) {
    LeaveApplication *newNode = (LeaveApplication*)malloc(sizeof(LeaveApplication));
    strcpy(newNode->emp_id, application->emp_id);
    strcpy(newNode->emp_name, application->emp_name);
    strcpy(newNode->department, application->department);
    newNode->leave_type = application->leave_type;
    newNode->leave_days = application->leave_days;
    strcpy(newNode->apply_time, application->apply_time);
    newNode->status = application->status;
    newNode->next = queryResult->next;
    queryResult->next = newNode;
}

void queryLeaveHistorybyID() {
    initQueryResult();
    char employeeID[20];
    printf("请输入员工ID: ");
    scanf("%s", employeeID);

    LeaveApplication *current = leave_head->next;
    while (current != NULL) {
        if (strcmp(current->emp_id, employeeID) == 0) {
            addqueryResultNode(current);
        }
        current = current->next;
    }
    printQueryResult();
}

void queryLeaveHistorybystatus() {
    int status;
    printf("请输入审批状态 (0:待审批, 1:已批准, 2:已拒绝): ");
    scanf("%d", &status);

    LeaveApplication *current = leave_head->next;
    while (current != NULL) {
        if (current->status == status) {
            addqueryResultNode(current);
        }
        current = current->next;
    }
    printQueryResult();
}

void queryLeaveHistorybyleaveType() {
    int leaveType;
    printf("请输入请假类型 (0:年假, 1:病假, 2:事假): ");
    scanf("%d", &leaveType);

    LeaveApplication *current = leave_head->next;
    while (current != NULL) {
        if (current->leave_type == leaveType) {
            addqueryResultNode(current);
        }
        current = current->next;
    }
    printQueryResult();
}

void queryLeaveHistoryByTime()
{
    char startTime[20], endTime[20];
    printf("请输入查询的开始时间 (格式: YYYY-MM-DD): ");
    scanf("%s", startTime);
    printf("请输入查询的结束时间 (格式: YYYY-MM-DD): ");
    scanf("%s", endTime);

    LeaveApplication *current = leave_head->next;
    while (current != NULL) {
        if (strcmp(current->apply_time, startTime) >= 0 && strcmp(current->apply_time, endTime) <= 0) {
            addqueryResultNode(current);
        }
        current = current->next;
    }
    printQueryResult();
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
            addqueryResultNode(current);
        }
        current = current->next;
    }
    printQueryResult();
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