#include "manager.h"
LeaveApplication *load_vacation_record()
{
    FILE *fp = fopen("leave_applications.csv", "r");
    if (fp == NULL)
    {
        printf("打开打卡记录文件失败！\n");
        Sleep(1000);
        return NULL;
    }

    LeaveApplication *head = (LeaveApplication *)malloc(sizeof(LeaveApplication));
    if (head == NULL)
    {
        fclose(fp);
        return NULL;
    }
    head->next = NULL;

    char buffer[1024];
    // 跳过表头
    fgets(buffer, sizeof(buffer), fp);

    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        LeaveApplication *new_node = (LeaveApplication *)malloc(sizeof(LeaveApplication));
        if (new_node == NULL)
            break;

        int parse_result = sscanf(buffer, "%19[^,],%9[^,],%9[^,],%d,%d,%19[^,],%d",
                                  new_node->emp_id,
                                  new_node->emp_name,
                                  new_node->department,
                                  &(new_node->leave_type),
                                  &(new_node->leave_days),
                                  new_node->apply_time,
                                  &(new_node->status));

        if (parse_result != 7)
        {
            continue;
        }

        if (strcmp(new_node->department, DEPARTMENT) == 0 && new_node->status == 2)
        {
            new_node->next = head->next;
            head->next = new_node;
        }
        else
        {
            free(new_node);
        }
    }

    fclose(fp);
    return head;
}

void vacation_by_emp_id(LeaveApplication *head)
{
    printf("========================================================\n");
    printf("当前位置：查询部门信息->查询部门请假情况->按员工ID查询\n");
    printf("========================================================\n");
    char emp_id[20];
    printf("请输入要查询的员工ID:");
    scanf("%s", emp_id);
    printf("\n查询结果:\n");
    printf("========================================================\n");
    printf("员工ID      姓名      请假类型    请假天数    申请时间\n");
    printf("========================================================\n");

    LeaveApplication *cur = head->next;
    int has_data = 0;
    while (cur != NULL)
    {
        if (strcmp(cur->emp_id, emp_id) == 0 && strcmp(cur->department, DEPARTMENT) == 0)
        {
            has_data = 1;
            char type[10];
            if (cur->leave_type == 1)
            {
                strcpy(type, "事假");
            }
            else if (cur->leave_type == 2)
            {
                strcpy(type, "病假");
            }
            else if (cur->leave_type == 3)
            {
                strcpy(type, "年假");
            }

            printf("%-10s %-13s %-13s %-8d %-10s\n",
                   cur->emp_id, cur->emp_name, type,
                   cur->leave_days, cur->apply_time);
        }

        cur = cur->next;
    }

    if (!has_data)
    {
        printf("该员工暂无审批通过的请假记录！\n");
    }

    printf("========================================================\n");
    printf("输入任意字符返回...\n");
    while (getchar() != '\n')
        ;
    getchar();
}

void vacation_by_emp_name(LeaveApplication *head)
{
    printf("========================================================\n");
    printf("当前位置：查询部门信息->查询部门请假情况->按员工姓名查询\n");
    printf("========================================================\n");
    char emp_name[10];
    printf("请输入要查询的员工姓名：");
    scanf("%s", emp_name);
    fflush(stdin);

    printf("\n查询结果:\n");
    printf("========================================================\n");
    printf("员工ID      姓名      请假类型    请假天数    申请时间\n");
    printf("========================================================\n");

    LeaveApplication *cur = head->next;
    int has_data = 0;

    while (cur != NULL)
    {
        // 匹配姓名 + 本部门
        if (strstr(cur->emp_name, emp_name) != NULL && strcmp(cur->department, DEPARTMENT) == 0)
        {
            has_data = 1;
            char type[10];
            if (cur->leave_type == 1)
            {
                strcpy(type, "事假");
            }
            else if (cur->leave_type == 2)
            {
                strcpy(type, "病假");
            }
            else if (cur->leave_type == 3)
            {
                strcpy(type, "年假");
            }

            printf("%-10s %-13s %-13s %-8d %-10s\n",
                   cur->emp_id, cur->emp_name, type,
                   cur->leave_days, cur->apply_time);
        }
        cur = cur->next;
    }

    if (!has_data)
    {
        printf("未查询到姓名包含【%s】的请假记录!\n", emp_name);
    }

    printf("========================================================\n");
    printf("输入任意字符返回...\n");
    while (getchar() != '\n')
        ;
    getchar();
}

void free_vacation(LeaveApplication *head)
{
    if (head == NULL)
        return;
    LeaveApplication *cur = head;
    LeaveApplication *temp;
    while (cur != NULL)
    {
        temp = cur->next;
        free(cur);
        cur = temp;
    }
}

EmpDayCount *count_vacation_days(LeaveApplication *head)
{
    // 创建统计链表头节点
    EmpDayCount *count_head = (EmpDayCount *)malloc(sizeof(EmpDayCount));
    count_head->next = NULL;

    LeaveApplication *p = head->next;

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
                q->day_count += p->leave_days;
                q->time_count++;
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

void vacation_by_day_asc(LeaveApplication *head)
{
    EmpDayCount *headcount = count_vacation_days(head);
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

    clear_screen();
    printf("========================================================\n");
    printf("当前位置：查询部门信息->查询部门请假情况->按总天数升序\n");
    printf("========================================================\n");
    printf("员工ID      姓名      总请假天数\n");
    printf("========================================================\n");

    if (headcount->next == NULL)
    {
        printf("暂无本部门打卡记录！\n");
    }
    else
    {
        p = headcount->next;
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

    free_day_count(headcount);
}

void vacation_by_time_asc(LeaveApplication *headall)
{
    EmpDayCount *head = count_vacation_days(headall);

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
            if (p->time_count > p->next->time_count)
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
    printf("当前位置：查询部门信息->查询部门请假情况->按次数升序\n");
    printf("========================================================\n");
    printf("员工ID      姓名      请假次数\n");
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
                   p->time_count);
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

void query_vacation()
{
    LeaveApplication *head = load_vacation_record();
    if (head == NULL)
    {
        return;
    }

    while (1)
    {
        clear_screen();
        printf("========================================================\n");
        printf("当前位置：查询部门信息->查询部门请假情况\n");
        printf("========================================================\n");
        printf("请选择操作：\n");
        printf("1)查看全部请假信息\n");
        printf("2)按员工ID查询请假信息\n");
        printf("3)按员工姓名查询请假信息\n");
        printf("4)按请假次数升序查询\n");
        printf("5)按请假天数升序查询\n");
        printf("6)返回上一步\n");
        printf("========================================================\n");
        int operation;
        if (scanf("%d", &operation) != 1)
        {
            fflush(stdin);
            printf("\n输入不合法,请重新输入\n");
            Sleep(1000);
            continue;
        }

        switch (operation)
        {
        case 1:
            clear_screen();
            department_vacation(head); // 查看全部打卡信息
            break;
        case 2:
            clear_screen();
            vacation_by_emp_id(head); // 按ID查询
            break;
        case 3:
            clear_screen();
            vacation_by_emp_name(head); // 按姓名查询
            break;
        case 4:
            clear_screen();
            vacation_by_time_asc(head); //  天数升序
            break;
        case 5:
            clear_screen();
            vacation_by_day_asc(head); //  次数升序
            break;
        case 6:
            clear_screen();
            free_vacation(head);
            return;
            break;
        default:
            printf("\n输入不合法,请重新输入\n");
            Sleep(1000);
            clear_screen();
        }
    }

    free_vacation(head);
}