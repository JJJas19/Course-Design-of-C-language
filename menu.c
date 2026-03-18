#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include"hr_specialist.h"
#include"menu.h"

void menu()
{
    printf("**********欢迎使用考勤管理系统**********\n");
    printf("**************************************\n");
    printf("**********1.登录             **********\n");
    printf("**********2.退出             **********\n");
    printf("***************************************\n");
    int log;
    scanf("%d", &log);
    if (log == 1)
    {
        int role;
        for (int i = 0; i < 3; i++)
        {
            printf("请输入账号与密码（剩余%d次机会）\n", 3 - i);
            char account[21]; // 存储账号
            printf("账号：");
            scanf("%s", account); // 输入账号

            char password[21]; // 存储密码
            printf("密码：");
            scanf("%s", password); // 输入密码

            int password_len = strlen(password);
            if (password_len != 6)
            {
                printf("输入错误！密码长度必须为6个字符，你输入了%d个字符。\n", password_len);
                if (i < 2)
                {
                    printf("剩余登录机会：%d次\n", 2 - i);
                } // 输入剩余登录机会
                continue;
            } // 判断密码数目是否合格
            role = check(account, password);

            if (role > 0)
            {

                printf("登录成功！\n");
                break; // 立即退出for循环
            }
            else
            {
                printf("账号或密码错误！\n");
                if (i < 2)
                {
                    printf("剩余登录机会：%d次\n", 2 - i);
                }
            }
        }
        // login(role);
    }
    else
    {
        printf("退出成功！");
        exit(0);
    }
}
int check(char account[], char password[])
{
    setlocale(LC_ALL, "zh_CN.UTF-8");                          // 规定中文编码格式
    FILE *fp = fopen("account and password storage.csv", "r"); // 打开文件只读模式
    if (fp == NULL)
    {
        printf("错误：账号密码文件不存在！\n");
        return 0;
    } // 验证账号密码文件
    char line[100];
    fgets(line, sizeof(line), fp); // 读取账号密码文件的一行
    // 不做任何处理，跳过第一行
    int number = 1; // 判断身份
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        line[strcspn(line, "\n\r")] = '\0';
        char *role = strtok(line, ",");         // 字符串分割函数，按，,（中英文都可）分割
        char *role_account = strtok(NULL, ","); // 当第一个参数是NULL时，从上一次分割的地方开始分割
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
        number++; // 是否匹配下一个身份
    }
    fclose(fp);
    return 0;
} // 登录验证函数
// void login(int role)
// {
//     if(role==4)
//     {
//         hr_menu();
//     }
// } // 登录函数
