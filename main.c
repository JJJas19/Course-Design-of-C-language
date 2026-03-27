#include "common.h"
#include "manager.h"

int main()
{
    // 设置编码方式，防止中文乱码
    SetConsoleOutputCP(CP_UTF8);
    //
    // SetConsoleOutputCP(936); // 输出编码：GBK
    SetConsoleCP(CP_UTF8);

    manager_menu();

    return 0;
}