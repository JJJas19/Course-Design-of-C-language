#ifndef MENU_H
#define MENU_H

// 主菜单函数
void menu();

// 登录验证函数
int check(char account[], char password[]);

// 角色登录跳转函数
void login(int role);

// 修改密码函数
void modify_password();

#endif