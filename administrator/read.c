#include "..\head\administrator.h"

void clearbuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int readint()
{
    char buffer[MAX_NAME_LENGTH];
    int num;
    int pos;

    clearbuffer();  // 清空输入缓冲区
    while (1) {
        fgets(buffer, sizeof(buffer), stdin);
        
        // 检查输入是否过长
        if (buffer[strlen(buffer) - 1] != '\n') {
            printf("输入过长，请重新输入: ");
            clearbuffer();
            continue;
        }
        
        // 尝试转换为整数
        if (sscanf(buffer, "%d%n", &num, &pos) == 1 && 
            num > 0 && 
            buffer[pos] == '\n') {
            return num;  // 输入合法，返回整数
        }
        else {
            printf("输入非法（必须为正整数），请重新输入: ");
        }
    }
}

int readID(int nowID)
{
    User *head = userHead;
    int id;
    char buffer[MAX_NAME_LENGTH];
    clearbuffer();
    while (1) {
        printf("请输入用户ID: ");

        fgets(buffer, sizeof(buffer), stdin);
        if (buffer[strlen(buffer) - 1] != '\n') {
            printf("输入过长，请重新输入\n");
            clearbuffer();
            continue;
        }
        int pos;
        // 尝试转换为整数
        if (sscanf(buffer, "%d%n", &id, &pos) == 1 && id > 0 && buffer[pos] == '\n') {
            // 检查ID是否重复
            int found = 0;
            User *temp = head->next;
            while (temp != NULL) {
                if (temp->id == id && id != nowID) {
                    found = 1;
                    break;
                }
                temp = temp->next;
            }
            if (!found) {
                break;  // ID合法且不重复，退出循环
            }
            else {
                printf("ID %d 已被使用，请重新输入: \n", id);
            }
        }
        else {
            printf("输入ID非法（必须为正整数），请重新输入: ");
        }
    }
    return id;
}

int readDepartmentID()
{
    int departmentID;
    char buffer[100];

    clearbuffer();
    while (1) {
        printf("请输入部门ID: ");

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("读取失败，请重试\n");
            continue;
        }

        int len = strlen(buffer);

        // 处理输入过长
        if (len == 0 || buffer[len - 1] != '\n') {
            printf("输入过长，请重新输入\n");
            clearbuffer();
            continue;
        }

        int pos;

        // 判断是否是合法整数
        if (sscanf(buffer, "%d%n", &departmentID, &pos) != 1 || buffer[pos] != '\n') {
            printf("输入非法（必须是整数），请重新输入\n");
            continue;
        }

        if (departmentID <= 0) {
            printf("部门ID必须为正整数，请重新输入\n");
            continue;
        }

        // 检查重复
        int found = 0;
        Department *point = departmentHead->next;

        while (point != NULL) {
            if (point->departmentID == departmentID) {
                found = 1;
                break;
            }
            point = point->next;
        }

        if (found) {
            printf("部门ID已存在，请重新输入\n");
            continue;
        }

        return departmentID; 
    }
}

int readEmployeeID()
{
    int employeeID;
    char buffer[100];
    
    clearbuffer();
    while (1) {
        printf("请输入员工ID: ");

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("读取失败，请重试\n");
            continue;
        }

        int len = strlen(buffer);

        // 处理输入过长
        if (len == 0 || buffer[len - 1] != '\n') {
            printf("输入过长，请重新输入\n");
            clearbuffer();
            continue;
        }

        int pos;

        // 判断是否是合法整数
        if (sscanf(buffer, "%d%n", &employeeID, &pos) != 1 || buffer[pos] != '\n') {
            printf("输入非法（必须是整数），请重新输入\n");
            continue;
        }

        if (employeeID <= 0) {
            printf("员工ID必须为正整数，请重新输入\n");
            continue;
        }

        // 检查重复
        int found = 0;
        Employee *point = employeeHead->next;

        while (point != NULL) {
            if (point->employeeID == employeeID) {
                found = 1;
                break;
            }
            point = point->next;
        }

        if (found) {
            printf("员工ID已存在，请重新输入\n");
            continue;
        }

        return employeeID; 
    }
}

int readHolidayID()
{
    int holidayID;
    char buffer[100];

    clearbuffer();
    while (1) {
        printf("请输入假期ID: ");


        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("读取失败，请重试\n");
            continue;
        }

        int len = strlen(buffer);

        // 处理输入过长
        if (len == 0 || buffer[len - 1] != '\n') {
            printf("输入过长，请重新输入\n");
            clearbuffer();
            continue;
        }

        int pos;

        // 判断是否是合法整数
        if (sscanf(buffer, "%d%n", &holidayID, &pos) != 1 || buffer[pos] != '\n') {
            printf("输入非法（必须是整数），请重新输入\n");
            continue;
        }

        if (holidayID <= 0) {
            printf("假期ID必须为正整数，请重新输入\n");
            continue;
        }

        // 检查重复
        int found = 0;
        HolidayType *point = holidayHead->next;

        while (point != NULL) {
            if (point->holidayID == holidayID) {
                found = 1;
                break;
            }
            point = point->next;
        }

        if (found) {
            printf("假期ID已存在，请重新输入\n");
            continue;
        }

        return holidayID; 
    }
}