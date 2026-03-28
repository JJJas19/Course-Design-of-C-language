#include "../head/manager.h"

CheckInRecord *filter_by_my_dept(CheckInRecord *head)
{
    CheckInRecord *result = (CheckInRecord *)malloc(sizeof(CheckInRecord));
    result->next = NULL;

    CheckInRecord *cur = head->next;
    while (cur != NULL)
    {
        if (strcmp(cur->department, DEPARTMENT) == 0)
        {
            CheckInRecord *node = (CheckInRecord *)malloc(sizeof(CheckInRecord));
            memcpy(node, cur, sizeof(CheckInRecord));
            node->next = result->next;
            result->next = node;
        }
        cur = cur->next;
    }
    return result;
}