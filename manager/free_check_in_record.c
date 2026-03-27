#include "manager.h"
void free_check_in_record(CheckInRecord *head)
{
    CheckInRecord *cur = head;
    CheckInRecord *temp;
    while (cur != NULL)
    {
        temp = cur->next;
        free(cur);
        cur = temp;
    }
}