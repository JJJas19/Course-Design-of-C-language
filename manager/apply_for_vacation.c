#include "../head/manager.h"

void apply_for_vacation()
{
    FILE *fp = fopen("../data/leave_applications.csv", "a");
    if (fp == NULL)
    {
        printf("打开文件失败！无法进行申请\n");
        return;
    }

    int type;
    int year = 0, month = 0, day = 0;
    int length;

    while (1)
    {
        clear_screen();
        printf("========================================================\n");
        printf("当前位置：请假申请->申请假期\n");
        printf("========================================================\n");
        printf("请输入假期类型：\n");
        printf("1)事假\n");
        printf("2)病假\n");
        printf("3)年假\n");
        printf("4)返回上一步\n");
        printf("========================================================\n");

        if (scanf("%d", &type) != 1)
        {
            // fflush(stdin);
            while (getchar() != '\n')
                ;
            printf("输入无效!请输入数字1-4:\n");
            Sleep(1000);
            continue;
        }

        if (type == 4)
        {
            fclose(fp);
            return;
        }
        else if (type >= 1 && type <= 3)
        {
            break;
        }
        else
        {
            fflush(stdin);
            printf("输入无效!请输入数字1-4:\n");
            Sleep(1000);
        }
    }

    int date[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    while (1)
    {
        clear_screen();
        printf("========================================================\n");
        printf("当前位置：请假申请->申请假期\n");
        printf("========================================================\n");
        printf("请输入请假开始时间(年/月/日)：\n");
        printf("例：2020/03/25\n");
        printf("========================================================\n");

        if (scanf("%d/%d/%d", &year, &month, &day) != 3)
        {
            fflush(stdin);
            printf("日期不合法,请重新输入\n");
            Sleep(1000);
            continue;
        }

        if (year < 2000 || year > 2100 || month < 1 || month > 12 || day < 1)
        {
            fflush(stdin);
            printf("日期不合法,请重新输入\n");
            Sleep(1000);
            continue;
        }

        if (month == 2 && day == 29)
        {
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
            {
                break;
            }
            else
            {
                fflush(stdin);
                printf("日期不合法,请重新输入\n");
                Sleep(1000);
                continue;
            }
        }

        if (day > date[month])
        {
            fflush(stdin);
            printf("日期不合法,请重新输入\n");
            Sleep(1000);
            continue;
        }

        break;
    }

    while (1)
    {
        clear_screen();
        printf("========================================================\n");
        printf("当前位置：请假申请->申请假期\n");
        printf("========================================================\n");
        printf("请输入请假长度(天)：\n");
        printf("========================================================\n");

        if (scanf("%d", &length) == 1 && length > 0)
        {
            break;
        }
        else
        {
            fflush(stdin);
            printf("输入不合法,请重新输入\n");
            Sleep(1000);
        }
    }

    fprintf(fp, "%s,%s,%s,%d,%d,%d-%02d-%02d,1\n", ID, Name, DEPARTMENT, type, length, year, month, day);

    printf("申请成功！请等待审批！\n");
    Sleep(1000);
    clear_screen();

    fclose(fp);
    return;
}