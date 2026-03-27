#include "manager.h"
// 统计本部门每个员工的打卡天数
EmpDayCount *count_emp_days(CheckInRecord *head)
{
    // 创建统计链表头节点
    EmpDayCount *count_head = (EmpDayCount *)malloc(sizeof(EmpDayCount));
    count_head->next = NULL;

    CheckInRecord *p = head->next;

    // 遍历所有打卡记录
    while (p != NULL)
    {
        // 只处理本部门
        if (strcmp(p->department, DEPARTMENT) != 0)
        {
            p = p->next;
            continue;
        }

        // 查找当前员工是否已经统计
        EmpDayCount *q = count_head->next;
        int found = 0;

        while (q != NULL)
        {
            // 找到,天数+1
            if (strcmp(q->emp_id, p->emp_id) == 0)
            {
                q->day_count++;
                found = 1;
                break;
            }
            q = q->next;
        }

        // 没找到,新建节点
        if (!found)
        {
            EmpDayCount *new_node = (EmpDayCount *)malloc(sizeof(EmpDayCount));
            strcpy(new_node->emp_id, p->emp_id);
            strcpy(new_node->emp_name, p->emp_name);
            new_node->day_count = 1;

            new_node->next = count_head->next;
            count_head->next = new_node;
        }

        p = p->next;
    }

    return count_head;
}