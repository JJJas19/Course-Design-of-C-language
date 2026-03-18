#include<stdio.h>
#include <windows.h>
#include<string.h>
#include<stdlib.h>
#include"menu.h"



void hr_menu()
{
    printf("**********欢迎使用HR人力资源管理系统**********\n");
    printf("********************************************\n");
    printf("**********1.考勤数据查询      ***************\n");
    printf("**********2.假期额度查询      ***************\n");
    printf("**********3.个人密码维护      ***************\n");
    printf("**********4.考勤对接薪酬      ***************\n");
    printf("**********5.薪酬发放系统      ***************\n");
    printf("**********6.退出             ***************\n");
    printf("********************************************\n");
    int choose;
    printf("请选择您要做的操作：\n");
    scanf("%d",&choose);
    switch (choose)
    {
    case 1:
        
        break;
    case 2:
        
        break;
    case 3:
        modify_password();
        break;
    case 4:
        
        break;
    case 5:
        
        break;
    
    default:
        printf("退出成功");
        hr_menu();
        break;
    }
}
void query_attendance(){
    printf("===== 考勤数据查询 =====\n");
    
}//考勤数据查询

void query_leave_quota(){

}//假期额度查询

void attendance_to_salary(){

}//考勤对接薪酬

void salary_payment(){

}//薪酬发放系统
