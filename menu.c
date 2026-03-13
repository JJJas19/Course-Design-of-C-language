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
            scanf("%s",account);
            printf("%s\n",account);
            int password[21];//存储密码
            printf("密码：");
            char temp;
            do{                        
            temp = getchar();//临时存储密码的每一位
            password[i] = temp-'0';
            }while(temp != "\n");
            login(account,password);
        }
    }
}
void login(char account[],int password[])
{
    

}





