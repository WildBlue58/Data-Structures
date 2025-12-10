#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct stack
{
    ElemType data;
    struct stack *next;
} Stack;

int push(Stack *s, ElemType e)
{
    Stack *p = (Stack *)malloc(sizeof(Stack));
    p->data = e;
    p->next = s->next;
    s->next = p;
    return 1;
}

int pop(Stack *s, ElemType *e)
{
    if (s->next == NULL)
    {
        printf("栈为空\n");
        return 0;
    }
    *e = s->next->data;
    Stack *q = s->next;
    s->next = q->next;
    free(q);
    return 1;
}