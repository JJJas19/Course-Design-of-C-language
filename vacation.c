#include "manager.h"
void vacation()
{
    while (1)
    {
        clear_screen();
        printf("========================================================\n");
        printf("当前位置：请假申请\n");
        printf("========================================================\n");
        printf("请选择操作：\n");
        printf("1)申请假期\n");
        printf("2)查看假期申请状态\n");
        printf("3)返回上一步\n");
        printf("========================================================\n");
        int operation;
        scanf("%d", &operation);
        switch (operation)
        {
        case 1:
            clear_screen();
            apply_for_vacation();
            break;
        case 2:
            clear_screen();
            check_my_application();
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