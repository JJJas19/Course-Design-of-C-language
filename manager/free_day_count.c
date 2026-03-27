#include "manager.h"
void free_day_count(EmpDayCount *head)
{
    EmpDayCount *cur = head;
    EmpDayCount *temp;
    while (cur != NULL)
    {
        temp = cur->next;
        free(cur);
        cur = temp;
    }
}