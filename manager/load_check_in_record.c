#include "manager.h"

CheckInRecord *load_check_in_record()
{
    FILE *fp = fopen("./data/check_in_record.csv", "r");
    if (fp == NULL)
    {
        printf("打开打卡记录文件失败！\n");
        Sleep(1500);
        return NULL;
    }

    // 创建头节点
    CheckInRecord *head = (CheckInRecord *)malloc(sizeof(CheckInRecord));
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
        CheckInRecord *node = (CheckInRecord *)malloc(sizeof(CheckInRecord));
        if (node == NULL)
            break;

        memset(node, 0, sizeof(CheckInRecord));

        // 按 CSV 格式解析
        sscanf(buffer, "%[^,],%[^,],%[^,],%[^,],%[^\n]",
               node->emp_id,
               node->emp_name,
               node->department,
               node->check_time,
               node->check_status);

        // 头插法插入链表
        node->next = head->next;
        head->next = node;
    }

    fclose(fp);
    return head;
}