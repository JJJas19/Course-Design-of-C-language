#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "hr_specialist.h"
#include "menu.h"
#include "common.h"

void menu()
{
    // Windows 中文不乱码（最稳定）
    system("chcp 65001");
    setlocale(LC_ALL, "");

    printf("**********欢迎使用考勤管理系统**********\n");
    printf("**************************************\n");
    printf("**********1.登录             **********\n");
    printf("**********2.退出             **********\n");
    printf("***************************************\n");

    int log;
    scanf("%d", &log);

    if (log == 1)
    {
        int role = 0;
        int login_success = 0;  // 标记登录是否成功

        // 3次登录机会
        for (int i = 0; i < 3; i++)
        {
            printf("请输入账号与密码（剩余%d次机会）\n", 3 - i);
            char account[21];
            printf("账号：");
            scanf("%s", account);

            char password[21];
            printf("密码：");
            scanf("%s", password);

            // 密码必须6位
            int password_len = strlen(password);
            if (password_len != 6)
            {
                printf("输入错误！密码长度必须为6个字符，你输入了%d个字符。\n", password_len);
                continue;
            }

            // 验证账号密码
            role = check(account, password);
            if (role > 0)
            {
                printf("登录成功！\n");
                login_success = 1;
                break;
            }
            else
            {
                printf("账号或密码错误！\n");
            }
        }

        // 3次失败直接退出
        if (!login_success)
        {
            printf("3次登录失败，程序自动退出！\n");
            exit(0);
        }

        // 进入对应菜单
        login(role);
    }
    else
    {
        printf("退出成功！");
        exit(0);
    }
}

int check(char account[], char password[])
{
    FILE *fp = fopen("account and password storage.csv", "r");
    if (fp == NULL)
    {
        printf("错误：账号密码文件不存在！\n");
        return 0;
    }

    char line[100];
    fgets(line, sizeof(line), fp); // 跳过表头

    int number = 1;
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        line[strcspn(line, "\n\r")] = '\0';
        char *role = strtok(line, ",");
        char *role_account = strtok(NULL, ",");
        char *role_password = strtok(NULL, ",");

        if (role_account == NULL || role_password == NULL)
        {
            number++;
            continue;
        }

        if (strcmp(role_account, account) == 0 && strcmp(role_password, password) == 0)
        {
            fclose(fp);
            return number;
        }
        number++;
    }

    fclose(fp);
    return 0;
}

void login(int role)
{
    if (role == 4)
    {
        hr_menu();
    }
}

//修改密码
void modify_password()
{
    printf("===== 修改密码 =====\n");

    FILE *aandp2 = fopen("account and password storage.csv", "r+");
    if (aandp2 == NULL)
    {
        printf("错误：账号密码文件不存在！\n");
        return;
    }

    char account[MAX_NAME_LENGTH], password[MAX_NAME_LENGTH];
    printf("请输入原本的账号：");
    scanf("%s", account);
    printf("请输入原本的密码：");
    scanf("%s", password);

    char line2[MAX_NAME_LENGTH];
    long line_start_pos = 0;
    fgets(line2, sizeof(line2), aandp2);
    line_start_pos = ftell(aandp2);

    int found = 0;

    while (fgets(line2, sizeof(line2), aandp2) != NULL)
    {
        long current_line_pos = line_start_pos;
        line_start_pos = ftell(aandp2);
        line2[strcspn(line2, "\n\r")] = '\0';

        char *name = strtok(line2, ",");
        char *name_account = strtok(NULL, ",");
        char *name_password = strtok(NULL, ",");

        if (!name || !name_account || !name_password)
            continue;

        if (strcmp(name_account, account) == 0 && strcmp(name_password, password) == 0)
        {
            found = 1;
            printf("请输入新密码（6位）：");
            char new_password[MAX_NAME_LENGTH];
            scanf("%s", new_password);

            if (strlen(new_password) != 6)
            {
                printf("密码必须6位！\n");
                fclose(aandp2);
                return;
            }

            long pwd_offset = current_line_pos + strlen(name) + 1 + strlen(name_account) + 1;
            fseek(aandp2, pwd_offset, SEEK_SET);
            fputs(new_password, aandp2);
            fflush(aandp2);
            printf("密码修改成功！\n");
            break;
        }
    }

    if (!found)
    {
        printf("账号或密码错误，修改失败！\n");
    }

    fclose(aandp2);
}