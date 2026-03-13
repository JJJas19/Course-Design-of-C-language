#include "manager.h"

void manager_menu()
{
    while (1)
    {
        clear_screen();
        printf("欢迎！\n");
        printf("请选择操作:\n");
        printf("1)请假审批\n");
        printf("2)考勤统计\n");
        printf("3)保存并退出\n");

        int operation;
        scanf("%d", &operation);
        switch (operation)
        {
        case 1:
            clear_screen();
            if (!examine_and_approve())
            {
                printf("打开文件失败，请检查文件是否存在\n");
            }
            break;
        case 2:
            clear_screen();
            break;
        case 3:
            clear_screen();
            return;
            break;
        default:
            printf("\n输入不合法，请重新输入\n");
            Sleep(1000);
            clear_screen();
        }
    }
}
