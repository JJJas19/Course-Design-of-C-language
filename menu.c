#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include"hr_specialist.h"
#include"menu.h"
#include"common.h"

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

void login(int role)
{
    if(role==4)
    {
        hr_menu();
    }
} // 登录函数

void modify_password(){

    FILE*aandp=fopen("account and password storage.csv","r+");
    if (aandp == NULL)
    {
        printf("错误：账号密码文件不存在！\n");
        return 0;
    } 
    char line[MAX_NAME_LENGTH];
    fgets(line,sizeof(line),aandp);//不做任何操作，跳过第一行
    
    User userlist[4];
    int i=0;
    while(fgets(line,sizeof(line),aandp)!=NULL)
    {
        line[strcspn(line, "\n\r")] = '\0';
        char* name=strtok(line,",");
        char* name_account=strtok(NULL,",");
        char* name_password=strtok(NULL,",");
        userlist[i].id=i;
        strcpy(userlist[i].name,name_account);
        strcpy(userlist[i].password,name_password);
        userlist[i].roleType=name_account;
        i++;
    }//存入数据体
    fclose("account and password storage.csv");
    printf("请输入原本的账号：\n");
    char account[MAX_NAME_LENGTH],password[MAX_NAME_LENGTH];
    scanf("%s",account);
    printf("请输入原本的密码：\n");
    scanf("%s",password);
    FILE*aandp2=fopen("account and password storage.csv","r+");
    if (aandp == NULL)
    {
        printf("错误：账号密码文件不存在！\n");
        return 0;
    } 
    char line2[MAX_NAME_LENGTH];
    long line_start_pos = 0; // 记录当前行的起始偏移量
    fgets(line2,sizeof(line2),aandp2);
    line_start_pos = ftell(aandp2); // 记录表头后第一行的起始位置
    while (fgets(line2, sizeof(line2), aandp2) != NULL)
    {
        long current_line_pos = line_start_pos;// 保存当前行的起始偏移量（用于后续定位修改）
         line_start_pos = ftell(aandp2);// 更新下一行的起始偏移量
        line[strcspn(line2, "\n\r")] = '\0';
        char* name=strtok(line2,",");
        char* name_account=strtok(NULL,",");
        char* name_password=strtok(NULL,",");
        if (!name || !name_account || !name_password) continue;// 跳过格式错误的行
        if (strcmp(name_account, account) == 0 && strcmp(name_password, password) == 0)
        {
            printf("请输入想要更改的密码：\n");
            char new_password[MAX_NAME_LENGTH];
            scanf("%s",new_password);
            if (strlen(new_password) != strlen(password)) {
                printf("错误：新值长度必须与原值一致！\n");
                fclose(aandp2);
                return 1;
            }
            long pwd_offset = current_line_pos + strlen(name) + 1 + strlen(name_account) + 1;  // 密码字段偏移 = 当前行起始位置 + 角色长度 + 1(逗号) + 账号长度 + 1(逗号)
            fseek(aandp2, pwd_offset, SEEK_SET);
            fputs(new_password, aandp2);
            fflush(aandp2);
            printf("密码修改成功！新密码：%s\n", new_password);
            break; 
        }
    }

    
    
}//个人密码维护

