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

typedef struct Staff
{
    char staffID[20];
    char staffName[10];
    char staffDepartment[10];
    char staffPosition[10];
    struct Staff *next;
} Staff;

void manager_menu();
int APPexamine();
void vacation();
void apply_for_vacation();
void check_my_application();
void query_department();
void department_staff();

// gcc main.c manager_menu.c clear_screen.c APPexamine.c vacation.c apply_for_vacation.c check_my_application.c query_department.c department_staff.c -o test.exe