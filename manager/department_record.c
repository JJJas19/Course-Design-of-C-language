#include "../head/manager.h"

// 统计部门打卡情况：正常/迟到/早退
void count_department_checkin(CheckInRecord *head)
{
    int normal = 0, late = 0, early = 0;
    CheckInRecord *cur = head->next;

    // 遍历打卡链表，筛选本部门并统计状态
    while (cur != NULL)
    {
        if (strcmp(cur->department, DEPARTMENT) == 0)
        {
            if (strcmp(cur->check_status, "正常") == 0 || strcmp(cur->check_status, "下班") == 0)
                normal++;
            else if (strcmp(cur->check_status, "迟到") == 0)
                late++;
            else if (strcmp(cur->check_status, "早退") == 0)
                early++;
        }
        cur = cur->next;
    }

    // 输出统计结果
    printf("========================================================\n");
    printf("              【%s】打卡情况统计\n", DEPARTMENT);
    printf("========================================================\n");
    printf("  正常打卡：%d 次\n", normal);
    printf("  迟到打卡：%d 次\n", late);
    printf("  早退打卡：%d 次\n", early);
    printf("--------------------------------------------------------\n");
    printf("  总计打卡：%d 次\n", normal + late + early);
    printf("========================================================\n");
    printf("输入任意字符返回...");
    fflush(stdin);
    getchar();
}

void department_record()
{
    CheckInRecord *head = load_check_in_record();
    if (head == NULL)
    {
        return;
    }

    while (1)
    {
        clear_screen();
        printf("========================================================\n");
        printf("当前位置：查询部门信息->查询部门打卡情况\n");
        printf("========================================================\n");
        printf("请选择操作：\n");
        printf("1)查看全部打卡信息\n");
        printf("2)按员工ID查询打卡信息\n");
        printf("3)按员工姓名查询打卡信息\n");
        printf("4)按天数升序查询\n");
        printf("5)按姓名升序查询\n");
        printf("6)统计部门打卡情况\n");
        printf("7)返回上一步\n");
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
            show_all_check_in(head); // 查看全部打卡信息
            break;
        case 2:
            clear_screen();
            query_by_emp_id(head); // 按ID查询
            break;
        case 3:
            clear_screen();
            query_by_emp_name(head); // 按姓名查询
            break;
        case 4:
            clear_screen();
            sort_by_day_asc(head); //  天数升序
            break;
        case 5:
            clear_screen();
            sort_by_name_asc(head); //  姓名升序
            break;
        case 6:
            clear_screen();
            count_department_checkin(head); // 全部统计
            break;
        case 7:
            clear_screen();
            free_check_in_record(head); // 释放链表
            return;
            break;
        default:
            fflush(stdin);
            printf("\n输入不合法,请重新输入\n");
            Sleep(1000);
            clear_screen();
        }
    }
}