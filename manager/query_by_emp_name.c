#include "manager.h"

void query_by_emp_name(CheckInRecord *head)
{
    printf("========================================================\n");
    printf("当前位置：查询部门信息->查询部门打卡情况->按员工姓名查询\n");
    printf("========================================================\n");
    char emp_name[10];
    printf("请输入要查询的员工姓名：");
    scanf("%s", emp_name);
    fflush(stdin);

    printf("\n查询结果:\n");
    printf("员工ID,姓名,部门,打卡时间,打卡状态\n");
    printf("========================================================\n");

    CheckInRecord *cur = head->next;
    int has_data = 0;

    while (cur != NULL)
    {
        // 匹配姓名 + 本部门
        if (strstr(cur->emp_name, emp_name) != NULL && strcmp(cur->department, DEPARTMENT) == 0)
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
        printf("未查询到姓名包含【%s】的打卡记录!\n", emp_name);
    }

    printf("========================================================\n");
    printf("输入任意字符返回...\n");
    char ch;
    scanf("%c", &ch);
}