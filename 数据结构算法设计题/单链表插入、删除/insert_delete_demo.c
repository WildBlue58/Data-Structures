#include <stdio.h>
#include <stdlib.h>
/*
 * 简单演示：单链表的插入与删除
 * 1. 头插法建立链表
 * 2. 在指定值之后插入新节点
 * 3. 删除指定值的第一个节点
 */

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

// 创建新节点
Node *create_node(int value)
{
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    node->data = value;
    node->next = NULL;
    return node;
}

// 头插法建立链表，返回头指针（带头结点哨兵）
Node *build_list_with_head(int *arr, int n)
{
    Node *head = create_node(0); // 哨兵节点，方便操作
    for (int i = 0; i < n; ++i)
    {
        Node *node = create_node(arr[i]);
        node->next = head->next;
        head->next = node;
    }
    return head;
}

// 在值为target的节点之后插入new_value，成功返回1，失败(未找到)返回0
int insert_after(Node *head, int target, int new_value)
{
    Node *p = head->next;
    while (p && p->data != target)
    {
        p = p->next;
    }
    if (!p)
    {
        return 0; // 未找到
    }
    Node *node = create_node(new_value);
    node->next = p->next;
    p->next = node;
    return 1;
}

// 删除值为target的第一个节点，成功返回1，失败(未找到)返回0
int delete_value(Node *head, int target)
{
    Node *prev = head;
    Node *curr = head->next;
    while (curr && curr->data != target)
    {
        prev = curr;
        curr = curr->next;
    }
    if (!curr)
    {
        return 0; // 未找到
    }
    prev->next = curr->next;
    free(curr);
    return 1;
}

// 打印链表内容
void print_list(Node *head)
{
    Node *p = head->next;
    printf("当前链表: ");
    while (p)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

// 释放链表
void free_list(Node *head)
{
    Node *p = head;
    while (p)
    {
        Node *next = p->next;
        free(p);
        p = next;
    }
}

int main(void)
{
    int data[] = {1, 2, 3, 4};
    int n = sizeof(data) / sizeof(data[0]);

    // 建表（头插法使得链表顺序为4 3 2 1）
    Node *head = build_list_with_head(data, n);
    print_list(head);

    // 在值为2的节点后插入99
    if (insert_after(head, 2, 99))
    {
        printf("在值2后插入99成功。\n");
    }
    else
    {
        printf("未找到值2，插入失败。\n");
    }
    print_list(head);

    // 删除值为3的节点
    if (delete_value(head, 3))
    {
        printf("删除值3成功。\n");
    }
    else
    {
        printf("未找到值3，删除失败。\n");
    }
    print_list(head);

    free_list(head);
    return 0;
}
