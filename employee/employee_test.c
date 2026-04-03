#include <Windows.h>
#include "employee.c"

Employee* CreateEmployee(char* name, int ID, char* departmentName) {
    Employee* emp = (Employee*)malloc(sizeof(Employee));
    strcpy(emp->employeeName, name);
    emp->employeeID = ID;
    strcpy(emp->departmentName, departmentName);
    emp->clockNotingData = NULL;
    emp->vacation = NULL;
    emp->next = NULL;
    return emp;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    char empAName[] =  "李四" ;
    char empADepartment[] =  "人事部" ;
    Employee* empA=CreateEmployee(empAName, 002, empADepartment);
    GetEmployeeInfo(empA);
    printf("输入任意键继续\n");
    ControlEmployee(empA);
    return 0;
}

//cl /source-charset:utf-8 /execution-charset:utf-8 /Fe:main.exe employee_test.c