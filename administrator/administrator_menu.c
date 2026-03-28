#include "../head/administrator.h"
#include <windows.h>

void departmentMenu()
{
    while (1)
    {
        int choice;
        printf("进入部门管理菜单...\n");
        printf("请选择操作：\n");
        printf("0. 返回上一级菜单\n");
        printf("1. 添加部门\n");
        printf("2. 删除部门\n");
        printf("3. 修改部门\n");
        printf("4. 显示部门列表\n");
        scanf("%d", &choice);
        system("cls"); // 清屏
        switch (choice) {
            case 0:
                return;
            case 1:
                addDepartment();
                system("pause");
                system("cls");
                break;
            case 2:
                displayDepartmentList();
                removeDepartment();
                system("pause");
                system("cls");
                break;
            case 3:
                modifyDepartment();
                system("pause");
                system("cls");
                break;
            case 4:
                displayDepartmentList();
                system("pause");
                system("cls");
                break;
            default:
                printf("无效的操作编号，请重新选择。\n");
                system("pause");
                system("cls");
                break;
        }
    }
}

void employeeMenu()
{
    while (1)
    {
        int choice;
        printf("进入员工管理菜单...\n");
        printf("请选择操作：\n");
        printf("0. 返回上一级菜单\n");
        printf("1. 添加员工\n");
        printf("2. 删除员工\n");
        printf("3. 修改员工\n");
        printf("4. 显示员工列表\n");
        scanf("%d", &choice);
        system("cls");
        switch (choice) {
            case 0:
                return;
            case 1:
                addEmployee();
                system("pause");
                system("cls");
                break;
            case 2:
                displayEmployeeList();
                removeEmployee();
                system("pause");
                system("cls");
                break;
            case 3:
                modifyEmployee();
                system("pause");
                system("cls");
                break;
            case 4:
                displayEmployeeList();
                system("pause");
                system("cls");
                break;
            default:
                printf("无效的操作编号，请重新选择。\n");
                system("pause");
                system("cls");
                break;
        }
    }
}

void holidayMenu()
{
    while (1)
    {
        int choice;
        printf("进入假期管理菜单...\n");
        printf("请选择操作：\n");
        printf("0. 返回上一级菜单\n");
        printf("1. 添加假期\n");
        printf("2. 删除假期\n");
        printf("3. 修改假期\n");
        printf("4. 显示假期列表\n");
        scanf("%d", &choice);
        system("cls"); // 清屏
        switch (choice) {
            case 0:
                return;
            case 1:
                addHoliday();
                system("pause");
                system("cls");
                break;
            case 2:
                displayHolidayList();
                removeHoliday();
                system("pause");
                system("cls");
                break;
            case 3:
                modifyHoliday();
                system("pause");
                system("cls");
                break;
            case 4:
                displayHolidayList();
                system("pause");
                system("cls");
                break;
            default:
                printf("无效的操作编号，请重新选择。\n");
                system("pause");
                system("cls");
                break;
        }
    }
}

void userMenu()
{
    while (1)
    {
        int choice;
        printf("进入用户管理菜单...\n");
        printf("请选择操作：\n");
        printf("0. 返回上一级菜单\n");
        printf("1. 添加用户\n");
        printf("2. 删除用户\n");
        printf("3. 修改用户\n");
        printf("4. 显示用户列表\n");
        scanf("%d", &choice);
        system("cls"); // 清屏
        switch (choice) {
            case 0:
                return;
            case 1:
                addUser();
                system("pause");
                system("cls");
                break;
            case 2:
                removeUser();
                system("pause");
                system("cls");
                break;
            case 3:
                modifyUser();
                system("pause");
                system("cls");
                break;
            case 4:
                displayUserList();
                system("pause");
                system("cls");
                break;
            default:
                printf("无效的操作编号，请重新选择。\n");
                system("pause");
                system("cls");
                break;
        }
    }
}

void maintainMenu()
{
    while (1)
    {
        int choice;
        printf("进入系统维护菜单...\n");
        printf("请选择操作：\n");
        printf("0. 返回上一级菜单\n");
        printf("1. 设置密码\n");
        printf("2. 设置假期时间\n");
        printf("3. 设置员工部门\n");
        scanf("%d", &choice);
        system("cls"); // 清屏
        switch (choice) {
            case 0:
                return;
            case 1:
                setpasswordMenu();
                system("pause");
                system("cls");
                break;
            case 2:
                setHolidayTimeMenu();
                system("pause");
                system("cls");
                break;
            case 3:
                setEmployeeDepartmentMenu();
                system("pause");
                system("cls");
                break;
            default:
                printf("无效的操作编号，请重新选择。\n");
                system("pause");
                system("cls");
                break;
        }
    }
}

void administrator_menu()
{
    int choice;
    printf("欢迎来到管理员菜单！\n");
    printf("请选择操作：\n");
    printf("0. 退出\n");
    printf("1. 管理部门\n");
    printf("2. 管理员工\n");
    printf("3. 管理假期\n");
    printf("4. 管理用户\n");
    printf("5. 系统维护\n");
    scanf("%d", &choice);
    system("cls");
    switch (choice) {
        case 0:
            printf("退出管理员菜单。\n");
            exit(0);
        case 1:
            departmentMenu();
            break;
        case 2:
            employeeMenu();
            break;
        case 3:
            holidayMenu();
            break;
        case 4:
            userMenu();
            break;
        case 5:
            maintainMenu();
        default:
            printf("无效的操作编号，请重新选择。\n");
            system("pause");
            system("cls");
            break;
    }
}