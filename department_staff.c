#include "manager.h"
void department_staff()
{
    FILE *fp = fopen("all_staff.csv", "r");
    if (fp == NULL)
    {
        printf("打开文件失败!无法查询员工信息!\n");
        Sleep(1000);
        return;
    }

    Staff *head = (Staff *)malloc(sizeof(Staff));
    if (head == NULL)
    {
        printf("内存分配失败！\n");
        Sleep(1000);
        fclose(fp);
        return;
    }
    memset(head, 0, sizeof(*head));
    head->next = NULL;

    char buffer[1024];
    // 跳过表头
    fgets(buffer, sizeof(buffer), fp);
    clear_screen();
    printf("%s:\n", DEPARTMENT);
    printf("========================================================\n");

    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        Staff *staff = malloc(sizeof(*staff));
        if (staff == NULL)
            break;
        memset(staff, 0, sizeof(*staff));

        int ret = sscanf(buffer, "%[^,],%[^,],%[^,],%[^,]",
                         staff->staffID,
                         staff->staffName,
                         staff->staffDepartment,
                         staff->staffPosition);

        if (ret != 4)
        {
            free(staff);
            continue;
        }

        // 只保留本部门
        if (strcmp(staff->staffDepartment, DEPARTMENT) == 0)
        {
            if (strcmp(staff->staffPosition, "经理") == 0)
            {
                printf("%s,%s,%s,%s\n",
                       staff->staffID,
                       staff->staffName,
                       staff->staffDepartment,
                       staff->staffPosition);
                free(staff);
            }
            else
            {
                staff->next = head->next;
                head->next = staff;
            }
        }
        else
        {
            free(staff);
        }
    }

    Staff *cur = head->next;
    while (cur != NULL)
    {
        printf("%s,%s,%s,%s",
               cur->staffID,
               cur->staffName,
               cur->staffDepartment,
               cur->staffPosition);
        cur = cur->next;
    }

    printf("========================================================\n");
    printf("输入任意字符返回...\n");

    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
    getchar();

    cur = head;
    while (cur != NULL)
    {
        Staff *temp = cur->next;
        free(cur);
        cur = temp;
    }

    fclose(fp);
}