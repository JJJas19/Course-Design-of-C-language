#include "manager.h"
void show_all_check_in(CheckInRecord *head)
{
    printf("========================================================\n");
    printf("当前位置：查询部门信息->查询部门打卡情况->查看全部打卡信息\n");
    printf("========================================================\n");
    printf("员工ID,姓名,部门,打卡时间,打卡状态\n");
    printf("========================================================\n");

    CheckInRecord *cur = head->next;
    int has_data = 0;

    while (cur != NULL)
    {
        // 只显示当前经理部门的记录
        if (strcmp(cur->department, DEPARTMENT) == 0)
        {
            has_data = 1;
            printf("%s,%s,%s,%s,%s\n",
                   cur->emp_id,
                   cur->emp_name,
                   cur->department,
                   cur->check_time,
                   cur->check_status);
        }
        cur = cur->next;
    }

    if (!has_data)
    {
        printf("暂无本部门打卡记录！\n");
    }

    printf("========================================================\n");
    printf("输入任意字符返回...\n");
    fflush(stdin); // 清空缓冲区
    char ch;
    scanf("%c", &ch);
}