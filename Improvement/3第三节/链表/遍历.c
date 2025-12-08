#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef struct node
{
    ElemType data;
    struct node *next;
} Node;

void listNode(Node *L)
{
    Node *p = L->next;
    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}