#include "common.h"
#include "clear_screen.h"

extern char ID[];
extern char Name[];
extern char DEPARTMENT[];

typedef struct LeaveApplication
{
    char emp_id[20];     // 员工ID
    char emp_name[10];   // 姓名
    char department[10]; // 部门
    int leave_type;      // 请假类型
    int leave_days;      // 请假天数
    char apply_time[20]; // 申请时间
    int status;          // 审批状态
    struct LeaveApplication *next;
} LeaveApplication;

void manager_menu();
int APPexamine();
void vacation();
void apply_for_vacation();
void check_my_application();

// gcc main.c manager_menu.c clear_screen.c APPexamine.c vacation.c apply_for_vacation.c check_my_application.c -o test.exe