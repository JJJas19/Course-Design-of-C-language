#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void menu()
{
printf("**********欢迎使用考勤管理系统**********\n");
printf("**************************************\n");
printf("**********1.登录             **********\n");
printf("**********2.退出             **********\n");
printf("***************************************\n");
    int log;
    scanf("%d",&log);
    if(log == 1){
        for(int i = 0;i < 3;i++){
            printf("请输入账号与密码\n");
            char account[21];//存储账号
            printf("账号：");
            scanf("%s",account);//输入账号
            char password[21];//存储密码
            printf("密码：");
            scanf("%s",password);//输入密码
            
            printf("%s\n",account);
            printf("%s\n",password);
            
        }
    }
}
void login(char account[],char password[])
{


}





