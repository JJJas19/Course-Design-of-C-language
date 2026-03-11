#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "administrator.h"

typedef struct Staff Staff;
typedef struct Node
{
    Staff data;
    Staff* next;
} Node;

Node *head, *tail;

Node *createNode(Staff data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("CreateNode Error\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void init()
{
    Staff data = {0, NULL, NULL};
    head = createNode(data);
    tail = createNode(data);
    head->next = tail;
}

void addStaff(const char* department, int holidayTime)
{
    Staff data;
    data.holidayTime = holidayTime;
    int size = strlen(department) + 1;
    if (size > MAX_DEPARTMENT_LENGTH) {
        printf("Exceeding the maximum length limit.");
        return;
    }
    memcpy(data.department, department, size); 
    Node *newNode = createNode(data);
    tail->next = newNode;
    tail = newNode;
    printf("Add successfully.");
}

void removeStaff(const char* name)
{
    Node *pointer = head;
    while (pointer->next != NULL) {
        Node *preNode = pointer;
        pointer = pointer->next;
        if (strcmp(pointer->data.name, name) == 0) {
            preNode->next = pointer->next;
            if (pointer == tail) {
                tail = preNode;
            }
            free(pointer);
            printf("Delete Successfully.");
            return;
        }
    }
    printf("There is no such name.");
}

void modifyStaff()
{
    
}

