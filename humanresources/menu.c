#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "../head/hr_specialist.h"
#include "../head/menu.h"
#include "../head/common.h"

void menu()
{
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
        int login_success = 0;

        for (int i = 0; i < 3; i++)
        {
            printf("请输入账号与密码（剩余%d次机会）\n", 3 - i);
            char account[21];
            printf("账号：");
            scanf("%s", account);//输入账号

            char password[21];
            printf("密码：");
            scanf("%s", password);//输入密码

            if (strlen(password) != 6)
            {
                printf("输入错误！密码长度必须为6个字符！\n");
                continue;
            }//判断密码长度

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
        }//判断是否登录成功

        if (!login_success)
        {
            printf("3次登录失败，程序自动退出！\n");
            exit(0);
        }

        login(role);
    }
    else
    {
        printf("退出成功！");
        exit(0);
    }
}

//检查
int check(char account[], char password[])
{
    FILE *fp = fopen("account and password storage.csv", "r");
    if (fp == NULL)
    {
        printf("错误：账号密码文件不存在！\n");
        return 0;
    }//打开文件

    char line[200];
    fgets(line, sizeof(line), fp); // 跳过表头

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        line[strcspn(line, "\n\r")] = '\0';

        // 分割6个字段
        char *role_str = strtok(line, ",");//角色
        char *acc      = strtok(NULL, ",");//账户
        char *pwd      = strtok(NULL, ",");//密码
        char *name     = strtok(NULL, ",");//姓名
        char *id       = strtok(NULL, ",");//ID
        char *role_val = strtok(NULL, ",");//判断

        if (!acc || !pwd || !role_val) continue;//防止误读

        if (strcmp(acc, account) == 0 && strcmp(pwd, password) == 0)
        {
            int real_role = atoi(role_val);
            fclose(fp);
            return real_role; 
        }
    }

    fclose(fp);
    return 0;
}

//登录
void login(int role)
{
    if (role == 1)
    {
        printf("==== 欢迎管理员登录 ====\n");
        administrator_menu();
    }
    else if (role == 2)
    {
        printf("==== 欢迎经理登录 ====\n");
        manager_menu();
    }
    else if (role == 3)
    {
        printf("==== 欢迎人力资源登录 ====\n");
        hr_menu();
    }
    else if (role == 4)
    {
        printf("==== 欢迎员工登录 ====\n");
        //ControlEmployee(Employee* employee)
    }
    else
    {
        printf("未知角色！\n");
    }
}

//密码管理
void modify_password()
{
    printf("===== 修改密码 =====\n");

    FILE *aandp2 = fopen("account and password storage.csv", "r+");
    if (aandp2 == NULL)
    {
        printf("错误：账号密码文件不存在！\n");
        return;
    }

    char account[MAX_NAME_LENGTH], old_pwd[MAX_NAME_LENGTH];
    printf("请输入原本的账号：");
    scanf("%s", account);
    printf("请输入原本的密码：");
    scanf("%s", old_pwd);

    char line2[300];
    long line_start_pos = 0;
    fgets(line2, sizeof(line2), aandp2);
    line_start_pos = ftell(aandp2);

    int found = 0;

    while (fgets(line2, sizeof(line2), aandp2) != NULL)
    {
        long current_line_pos = line_start_pos;
        line_start_pos = ftell(aandp2);
        line2[strcspn(line2, "\n\r")] = '\0';

        // 读取6个字段
        char *role_str = strtok(line2, ",");
        char *acc      = strtok(NULL, ",");
        char *pwd      = strtok(NULL, ",");
        char *name     = strtok(NULL, ",");
        char *id       = strtok(NULL, ",");
        char *role_val = strtok(NULL, ",");

        if (!role_str || !acc || !pwd) continue;

        if (strcmp(acc, account) == 0 && strcmp(pwd, old_pwd) == 0)
        {
            found = 1;
            printf("请输入新密码（6位）：");
            char new_pwd[MAX_NAME_LENGTH];
            scanf("%s", new_pwd);

            if (strlen(new_pwd) != 6)
            {
                printf("密码必须为6位！\n");
                fclose(aandp2);
                return;
            }

            // 计算密码在文件中的真实偏移量
            long pos = current_line_pos
                     + strlen(role_str) + 1
                     + strlen(acc) + 1;

            fseek(aandp2, pos, SEEK_SET);
            fputs(new_pwd, aandp2);
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