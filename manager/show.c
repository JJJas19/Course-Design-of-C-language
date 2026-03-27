#include "manager.h"
void show(EmpDayCount *head)
{
    clear_screen();
    printf("========================================================\n");
    printf("当前位置：查询部门信息->查询部门打卡情况->按天数升序\n");
    printf("========================================================\n");
    printf("员工ID      姓名      打卡天数\n");
    printf("========================================================\n");

    if (head->next == NULL)
    {
        printf("暂无本部门打卡记录！\n");
    }
    else
    {
        EmpDayCount *p = head->next;
        while (p != NULL)
        {
            printf("%-8s %-8s %d\n",
                   p->emp_id,
                   p->emp_name,
                   p->day_count);
            p = p->next;
        }
    }

    printf("========================================================\n");
    printf("输入任意字符返回...");
    while (getchar() != '\n')
        ;
    getchar();
}