#include "head/common.h"
#include "head/administrator.h"

int main()
{
    // 设置编码方式，防止中文乱码
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // manager_menu();
    loadData();
    
    return 0;
}