#include "manager.h"
#include <string.h>

int APPexamine()
{
    FILE *fp = fopen("../data/leave_applications.csv", "r");
    FILE *fp_temp = fopen("../data/temp.csv", "w");

    // 文件打开校验
    if (fp == NULL)
    {
        printf("错误！无法打开原CSV文件！\n");
        return 0;
    }
    if (fp_temp == NULL)
    {
        printf("错误！无法创建临时文件!\n");
        fclose(fp);
        return 0;
    }

    char buffer[1024];
    int count = 0;
    LeaveApplication app;
    int goback = 1;

    printf("打开成功，开始处理请假申请...\n");

    if (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        fprintf(fp_temp, "%s", buffer);
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL && goback)
    {
        sscanf(buffer, "%[^,],%[^,],%[^,],%d,%d,%[^,],%d",
               app.emp_id,
               app.emp_name,
               app.department,
               &app.leave_type,
               &app.leave_days,
               app.apply_time,
               &app.status);

        if (app.status != 1)
        {
            fprintf(fp_temp, "%s,%s,%s,%d,%d,%s,%d\n",
                    app.emp_id,
                    app.emp_name,
                    app.department,
                    app.leave_type,
                    app.leave_days,
                    app.apply_time,
                    app.status);
            continue;
        }

        count++;
        int valid = 1;
        while (valid == 1)
        {
            system("cls");
            printf("========================================================\n");
            printf("                请假申请审批 - 第%d条\n", count);
            printf("========================================================\n");
            printf("  员工ID：%s\n", app.emp_id);
            printf("  姓名：%s\n", app.emp_name);
            printf("  部门：%s\n", app.department);
            printf("  请假类型：%d\n", app.leave_type);
            printf("  请假天数：%d天\n", app.leave_days);
            printf("  申请时间：%s\n", app.apply_time);
            printf("========================================================\n");
            printf("请选择操作：\n");
            printf("1) 通过\n");
            printf("2) 拒绝\n");
            printf("3) 暂不处理，下一条\n");
            printf("4) 结束处理，保存并退出\n");
            printf("请输入操作编号：");

            int op;
            while (scanf("%d", &op) != 1)
            {
                while (getchar() != '\n')
                    ;
                printf("输入无效！请输入数字1-4：");
            }

            switch (op)
            {
            case 1:
                valid = 0;
                app.status = 2;
                printf("已批准该申请！\n");
                Sleep(1000);
                break;
            case 2:
                valid = 0;
                app.status = 3;
                printf("已拒绝该申请！\n");
                Sleep(1000);
                break;
            case 3:
                valid = 0;
                printf("暂不处理，跳至下一条...\n");
                Sleep(1000);
                break;
            case 4:
                valid = 0;
                goback = 0;
                printf("结束处理，正在保存数据...\n");
                Sleep(1000);
                break;
            default:
                printf("无效输入！请输入1-4之间的数字！\n");
                Sleep(1000);
                break;
            }
        }

        fprintf(fp_temp, "%s,%s,%s,%d,%d,%s,%d\n",
                app.emp_id,
                app.emp_name,
                app.department,
                app.leave_type,
                app.leave_days,
                app.apply_time,
                app.status);
    }

    fclose(fp);
    fclose(fp_temp);

    remove("../data/leave_applications.csv");
    rename("../data/temp.csv", "../data/leave_applications.csv");

    printf("审批完成！数据已保存\n");
    return 1;
}