#include "../head/manager.h"

LeaveApplication *load_leave_records()
{
    FILE *fp = fopen("../data/leave_applications.csv", "r");
    if (fp == NULL)
    {
        printf("打开请假文件失败！\n");
        Sleep(1000);
        return NULL;
    }

    LeaveApplication *head = (LeaveApplication *)malloc(sizeof(LeaveApplication));
    if (head == NULL)
    {
        fclose(fp);
        return NULL;
    }
    head->next = NULL;

    char buffer[1024];
    fgets(buffer, sizeof(buffer), fp);

    fclose(fp);
    return head;
}

void department_vacation(LeaveApplication *head)
{
    if (head == NULL)
        return;

    clear_screen();
    printf("========================================================\n");
    printf("当前位置：查询部门信息->查询部门请假情况（审批通过）\n");
    printf("========================================================\n");
    printf("员工ID      姓名      请假类型    请假天数    申请时间\n");
    printf("========================================================\n");

    LeaveApplication *cur = head->next;
    int has_data = 0;
    while (cur != NULL)
    {
        has_data = 1;
        char type[10];
        if (cur->leave_type == 1)
        {
            strcpy(type, "事假");
        }
        else if (cur->leave_type == 2)
        {
            strcpy(type, "病假");
        }
        else if (cur->leave_type == 3)
        {
            strcpy(type, "年假");
        }

        printf("%-10s %-13s %-13s %-8d %-10s\n",
               cur->emp_id, cur->emp_name, type,
               cur->leave_days, cur->apply_time);
        cur = cur->next;
    }

    if (!has_data)
    {
        printf("本部门暂无审批通过的请假记录！\n");
    }

    printf("========================================================\n");
    printf("输入任意字符返回...");
    while (getchar() != '\n')
        ;
    getchar();
}