// 使用双指针找到倒数第k个节点

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

int find(Node *head, int k)
{
    Node *p1 = head;
    Node *p2 = head;
    for (int i = 0; i < k; i++)
    {
        p2 = p2->next;
    }
    while (p2 != NULL)
    {
        p1 = p1->next;
        p2 = p2->next;
    }
    return p1->data;
}