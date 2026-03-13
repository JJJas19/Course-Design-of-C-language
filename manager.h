#include "common.h"
#include "clear_screen.h"

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
int examine_and_approve();