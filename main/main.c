#include "..\head\common.h"
#include "..\head\manager.h"
#include "..\head\administrator.h"
#include "..\head\employee.h"
#include "..\head\hr_specialist.h"

int main()
{
    // 设置编码方式，防止中文乱码
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    loadData();
    // administrator_menu();
    menu(employeeHead);

    return 0;
}