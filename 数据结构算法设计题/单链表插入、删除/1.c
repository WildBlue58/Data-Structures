// 一、单链表操作
// 1、设计算法，在单链表中删除值为x的最后一个节点
// 要求：若未找到x，输出错误信息并返回0；删除成功返回1。

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

// 删除单链表中值为 x 的最后一个节点
// 未找到返回 0，并输出提示；删除成功返回 1
int delete_last_x(Node **head, int x)
{
    if (head == NULL || *head == NULL)
    {
        printf("链表为空，未找到 %d\n", x);
        return 0;
    }

    Node *prev = NULL;      // 当前遍历节点的前驱
    Node *cur = *head;      // 当前节点
    Node *last_prev = NULL; // 最后一个值为 x 的节点的前驱
    Node *last = NULL;      // 最后一个值为 x 的节点

    // 遍历寻找最后一个值为 x 的节点
    while (cur != NULL)
    {
        if (cur->data == x)
        {
            last_prev = prev;
            last = cur;
        }
        prev = cur;
        cur = cur->next;
    }

    if (last == NULL)
    {
        printf("未找到 %d\n", x);
        return 0;
    }

    // 执行删除
    if (last_prev == NULL)
    {
        // 要删的是头结点
        *head = last->next;
    }
    else
    {
        last_prev->next = last->next;
    }
    free(last);
    return 1;
}

// 辅助：头插法建立链表
Node *push_front(Node *head, int val)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = val;
    node->next = head;
    return node;
}

// 辅助：打印链表
void print_list(Node *head)
{
    for (Node *p = head; p != NULL; p = p->next)
    {
        printf("%d", p->data);
        if (p->next)
            printf(" -> ");
    }
    printf("\n");
}

int main(void)
{
    Node *head = NULL;
    // 构建样例链表：1 -> 2 -> 3 -> 2 -> 4
    head = push_front(head, 4);
    head = push_front(head, 2);
    head = push_front(head, 3);
    head = push_front(head, 2);
    head = push_front(head, 1);

    printf("初始链表: ");
    print_list(head);

    int x = 2;
    int ret = delete_last_x(&head, x);
    if (ret)
    {
        printf("删除值为 %d 的最后一个节点后: ", x);
        print_list(head);
    }

    // 释放链表
    while (head)
    {
        Node *tmp = head;
        head = head->next;
        free(tmp);
    }
    return 0;
}
