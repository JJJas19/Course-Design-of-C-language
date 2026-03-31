#ifndef EMPLOYEE_H
#define EMPLOYEE_H

//定义FindDay函数，用于查找某日的打卡记录，参数为指向ClockNoting结构体的指针、指向Vacation结构体的指针、年、月、日
ClockNoting* FindDay(ClockNoting** origDate, Vacation* vacationList, int year, int month, int day);

// 定义Clock函数，用于处理员工打卡操作，参数为指向Employee结构体的指针
bool Clock(Employee* employee);

//某日的打卡情况
void ClockNotingByDate(ClockNoting* clockNotingData);

//查询打卡记录的函数
void FindClockNoting(Employee* employee);

//查询请假日期
void FindAbsenceByDate(Vacation* vacation);

//查询某日打卡记录的函数
void FindClockNotingByDate(Employee* employee);

//查询某月打卡情况
void FindClockNotingByMonth(Employee* employee);

//定义GetClockNoting函数，用于查询员工的打卡信息,参数为指向Employee结构体的指针
void GetClockNoting(Employee* employee);

//定义Pop函数，用来为某种信息进行降序排序
//按请假时长
void PopDownByLength(Vacation** messeges, int length);
//按请假日期
void PopDownByDate(Vacation** messeges, int length);

//统计请假信息
void SortAbsenceMessege(Vacation* vacation);

//统计请假天数
void SortAbsenceDays(Vacation* vacation);

//统计迟到、早退天数
void UnpunctuatedDays(ClockNoting* clockNoting);

//定义InformationIntegrety函数，用于统计员工的打卡信息
void SortInformation(Employee* employee);

//定义CalculateDate,用来计算日期
Date CalculateDate(Date date, int length);

//定义AddVacation函数，用来为员工添加请假信息
void AddVacation(Employee* employee, int year,int month,int day, int length);

//定义JudgeDate函数，用来判断日期是否合法
bool JudgeDate(int year, int month, int day);

//定义ApplyForVacation函数，用来为员工请假
void ApplyForVacation(Employee* employee);

//用来实现员工总控
void ControlEmployee(Employee* employee);

//用来保存员工信息
void SaveEmployee(Employee* employee);

//用来判断打卡状态
const char* JudgeClockingState(ClockNoting* clockNoting, int kind);

//用来判断所属部门
char* JudgeDepartment(int departmentID);

//用来读取员工打卡信息
void GetClockInfo(Employee* employee);

//用来读取员工假期信息
void GetVacationInfo(Employee* employee);

//用来判断打卡的类型
int JudgeClockingKind(char* state);

#endif