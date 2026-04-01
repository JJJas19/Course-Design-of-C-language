#ifndef MENU_H
#define MENU_H

#include "common.h"
#include "administrator.h"
#include "employee.h"
#include "hr_specialist.h"
#include "manager.h"

extern char employeename[100];
extern int employeeID;
extern char managername[100];
extern char managerID[100];
extern char managedepartment[100];

// 主菜单函数
void menu(Employee* employeehead);

// 登录验证函数
int check(char account[], char password[]);

// 角色登录跳转函数
void login(int role,Employee* employeehead);

// 修改密码函数
void modify_password();

#endif