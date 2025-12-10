#include <stdio.h>
#include <stdlib.h>

// 定义元素类型为int，方便以后修改数据类型（比如改成char、double等）
typedef int ElemType;

// 定义单链表节点结构体
// 每个节点包含两部分：
// 1. data: 存储数据元素
// 2. next: 指向下一个节点的指针（链表的"链"就是这个指针）
typedef struct node
{
    ElemType data;     // 节点的数据域，存储实际数据
    struct node *next; // 节点的指针域，指向下一个节点（如果没有下一个，则为NULL）
} Node;                // 给struct node起一个别名Node，方便使用

int insertHead(Node *L, ElemType e)
{
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = e;
    p->next = L->next;
    L->next = p;
    return 1;
}

Node *insertTail(Node *tail, ElemType e)
{
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = e;
    tail->next = p;
    p->next = NULL;
    return p;
}

int insertNode(Node *L, int pos, ElemType e)
{
    Node *p = L;
    int i = 0;
    while (i < pos - 1)
    {
        p = p->next;
        i++;
        if (p == NULL)
            return 0;
    }
    Node *q = (Node *)malloc(sizeof(Node));
    q->data = e;
    q->next = p->next;
    p->next = q;
    return 1;
}

int deleteNode(Node *L, int pos)
{
    Node *p = L;
    int i = 0;
    while (i < pos - 1)
    {
        p = p->next;
        i++;
        if (p == NULL)
            return 0;
    }
    if (p->next == NULL)
    {
        printf("找不到\n");
        return 0;
    }
    Node *q = p->next;
    p->next = q->next;
    free(q);
    return 1;
}