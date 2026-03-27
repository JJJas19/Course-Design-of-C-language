#include "employee/employee.c"

int main() {
	Employee* employeeA = (Employee*)malloc(sizeof(Employee));
	strcpy(employeeA->employeeName, "John Doe");
	employeeA->employeeID = 12345;
	ControlEmployee(employeeA);
	return 0;
}