#include "manager.h"
void query_department()
{
    while (1)
    {
        clear_screen();
        printf("========================================================\n");
        printf("当前位置：查询部门信息\n");
        printf("========================================================\n");
        printf("请选择操作：\n");
        printf("1)查询部门人员信息\n");
        printf("2)查询部门请假情况\n");
        printf("3)返回上一步\n");
        printf("========================================================\n");
        int operation;
        scanf("%d", &operation);
        switch (operation)
        {
        case 1:
            clear_screen();
            department_staff();
            break;
        case 2:
            clear_screen();
            break;
        case 3:
            clear_screen();
            return;
            break;
        default:
            printf("\n输入不合法,请重新输入\n");
            Sleep(1000);
            clear_screen();
        }
    }
}