#include "../head/manager.h"
// 按打卡天数 升序排序
void sort_by_day_asc(CheckInRecord *head)
{
    EmpDayCount *headcount = count_emp_days(head);
    if (headcount->next == NULL)
        return;

    int flag;       // 是否交换过
    EmpDayCount *p; // 遍历指针

    do
    {
        flag = 0; // 假设没交换
        p = headcount->next;

        // 冒泡
        while (p->next != NULL)
        {
            if (p->day_count > p->next->day_count)
            {
                EmpDayCount *prev = headcount;
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

    show(headcount);

    free_day_count(headcount);
}