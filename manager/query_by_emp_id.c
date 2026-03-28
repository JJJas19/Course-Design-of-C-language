#include "../head/manager.h"
void query_by_emp_id(CheckInRecord *head)
{
    printf("========================================================\n");
    printf("当前位置：查询部门信息->查询部门打卡情况->按员工ID查询\n");
    printf("========================================================\n");
    char emp_id[20];
    printf("请输入要查询的员工ID：");
    scanf("%s", emp_id);
    fflush(stdin); // 清空缓冲区

    printf("\n查询结果：\n");
    printf("员工ID,姓名,部门,打卡时间,打卡状态\n");
    printf("========================================================\n");

    CheckInRecord *cur = head->next;
    int has_data = 0;

    while (cur != NULL)
    {
        // 匹配ID + 本部门
        if (strcmp(cur->emp_id, emp_id) == 0 && strcmp(cur->department, DEPARTMENT) == 0)
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
        printf("未查询到【%s】的打卡记录！\n", emp_id);
    }

    printf("========================================================\n");
    printf("输入任意字符返回...\n");
    char ch;
    scanf("%c", &ch);
}