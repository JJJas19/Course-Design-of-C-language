#include "common.h"
#include "clear_screen.h"

extern char ID[];
extern char name[];
extern char department[];

typedef struct
{
    char emp_id[20];     // 员工ID
    char emp_name[10];   // 姓名
    char department[10]; // 部门
    char leave_type[20]; // 请假类型
    int leave_days;      // 请假天数
    char apply_time[20]; // 申请时间
    int status;          // 审批状态
} LeaveApplication;

void manager_menu();
int APPexamine();
void vacation();
void apply_for_vacation();

// gcc main.c manager_menu.c clear_screen.c APPexamine.c vacation.c apply_for_vacation.c -o test.exe