#include "manager.h"

void sort_by_name_asc(CheckInRecord *headall)
{
    EmpDayCount *head = count_emp_days(headall);

    if (head == NULL || head->next == NULL)
        return;

    int flag = 0;
    EmpDayCount *p;

    // 冒泡排序
    do
    {
        flag = 0;
        p = head->next;

        while (p->next != NULL)
        {
            if (strcmp(p->emp_name, p->next->emp_name) > 0)
            {
                EmpDayCount *prev = head;
                while (prev->next != p)
                    prev = prev->next;
                EmpDayCount *node1 = p;
                EmpDayCount *node2 = p->next;

                node1->next = node2->next;
                node2->next = node1;
                prev->next = node2;

                flag = 1;
                p = node2;
            }

            p = p->next;
        }
    } while (flag);

    clear_screen();
    printf("========================================================\n");
    printf("当前位置：查询部门信息->查询部门打卡情况->按姓名升序\n");
    printf("========================================================\n");
    printf("员工ID      姓名      打卡天数\n");
    printf("========================================================\n");

    if (head->next == NULL)
    {
        printf("            暂无本部门打卡记录！\n");
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

    EmpDayCount *cur = head;
    EmpDayCount *temp;
    while (cur != NULL)
    {
        temp = cur->next;
        free(cur);
        cur = temp;
    }
}