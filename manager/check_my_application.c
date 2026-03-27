#include "manager.h"
void check_my_application()
{
    FILE *fp = fopen("./data/leave_applications.csv", "r");
    if (fp == NULL)
    {
        printf("打开文件失败！无法查询！\n");
        Sleep(1000);
        return;
    }

    LeaveApplication *head = malloc(sizeof(*head));
    if (head == NULL)
    {
        printf("内存分配失败！\n");
        Sleep(1000);
        fclose(fp);
        return;
    }
    memset(head, 0, sizeof(*head));
    head->next = NULL;

    char buffer[1024];
    // 跳过表头
    fgets(buffer, sizeof(buffer), fp);

    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        LeaveApplication *app = malloc(sizeof(*app));
        if (app == NULL)
            break;
        memset(app, 0, sizeof(*app));

        int ret = sscanf(buffer, "%[^,],%[^,],%[^,],%d,%d,%[^,],%d",
                         app->emp_id,
                         app->emp_name,
                         app->department,
                         &app->leave_type,
                         &app->leave_days,
                         app->apply_time,
                         &app->status);

        if (ret != 7)
        {
            free(app);
            continue;
        }

        // 只保留本人
        if (strcmp(app->emp_id, ID) == 0 || strcmp(app->emp_name, Name) == 0)
        {
            app->next = head->next;
            head->next = app;
        }
        else
        {
            free(app);
        }
    }

    clear_screen();
    printf("========================================================\n");
    printf("当前位置：请假申请->查看假期申请状态\n");
    printf("========================================================\n");
    printf("员工ID,姓名,部门,请假类型,请假天数,申请时间,审批状态\n");

    LeaveApplication *cur = head->next;
    while (cur != NULL)
    {
        char type[10] = {0};
        if (cur->leave_type == 1)
            strcpy(type, "事假");
        else if (cur->leave_type == 2)
            strcpy(type, "病假");
        else if (cur->leave_type == 3)
            strcpy(type, "年假");
        else
            strcpy(type, "未知");

        char app_status[10] = {0};
        if (cur->status == 1)
            strcpy(app_status, "待审批");
        else if (cur->status == 2)
            strcpy(app_status, "已通过");
        else if (cur->status == 3)
            strcpy(app_status, "被驳回");
        else
            strcpy(app_status, "异常");

        printf("%s,%s,%s,%s,%d,%s,%s\n",
               cur->emp_id, cur->emp_name, cur->department,
               type, cur->leave_days, cur->apply_time, app_status);
        cur = cur->next;
    }

    printf("========================================================\n");
    printf("输入任意字符返回...\n");

    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
    getchar();

    cur = head;
    while (cur != NULL)
    {
        LeaveApplication *temp = cur->next;
        free(cur);
        cur = temp;
    }

    fclose(fp);
}