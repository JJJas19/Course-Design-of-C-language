#include "manager.h"

int examine_and_approve()
{
    FILE *fp = fopen("leave_applications.csv", "w");
    if (fp == NULL)
    {
        printf("错误！无法打开文件！\n");
        return 0;
    }

    // 读取缓冲及以读取数量
    char buffer[1024];
    int count = 0;
    LeaveApplication apps[100];

    fgets(buffer, sizeof(buffer), fp);
    printf("打开成功，正在读取...\n");

    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        sscanf(buffer, "%[^,],%[^,],%[^,],%[^,],%d,%[^,],%[^\n]",
               apps[count].emp_id,      // 解析员工ID
               apps[count].emp_name,    // 解析姓名
               apps[count].department,  // 解析部门
               apps[count].leave_type,  // 解析请假类型
               &apps[count].leave_days, // 解析请假天数（int类型要加&）
               apps[count].apply_time,  // 解析申请时间
               apps[count].status);     // 解析审批状态
        count++;
    }

    printf("------------------------------------------------------------\n");
    for (int i = 0; i < count; i++)
    {
        printf("  第%d条：\n", i + 1);
        printf("  员工ID：%s\n", apps[i].emp_id);
        printf("  姓名：%s\n", apps[i].emp_name);
        printf("  部门：%s\n", apps[i].department);
        printf("  请假类型：%s\n", apps[i].leave_type);
        printf("  请假天数：%d天\n", apps[i].leave_days);
        printf("  申请时间：%s\n", apps[i].apply_time);
        printf("  审批状态：%s\n", apps[i].status);
        printf("------------------------------------------------------------\n");
    }

    return 1;
}