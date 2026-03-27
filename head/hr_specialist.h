#ifndef HR_SPECIALIST_H
#define HR_SPECIALIST_H

// HR 主菜单
void hr_menu();

// 考勤数据打印
void query_attendance(Employee *employeeHead);

// 假期额度打印
void query_leave_quota(Employee *employeeHead);

// 考勤对接薪酬（计算工资）
void attendance_to_salary(Employee *employeeHead);

// 考勤数据查询
void search_attendance(Employee *employeeHead);

// 假期额度查询
void query_leave_quota_search(Employee *employeeHead);

// 薪资查询
void query_salary(Employee *employeeHead);

#endif