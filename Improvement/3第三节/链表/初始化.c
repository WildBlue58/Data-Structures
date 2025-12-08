#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct node
{
    ElemType data;
    struct node *next;
} Node;

Node *initList()
{
    Node *head = (Node *)malloc(sizeof(Node));
    if (head == NULL)
    {
        printf("内存分配失败\n");
        return NULL;
    }
    head->data = 0;
    head->next = NULL;
    return head;
}

int main()
{
    Node *list = initList();
    return 0;
}