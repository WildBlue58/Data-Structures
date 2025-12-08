#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;
typedef struct TreeNode
{
    ElemType data;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
} TreeNode;
typedef TreeNode *BiTree;
void preOrder(BiTree T)
{
    if (T != NULL)
    {
        printf("%c", T->data);
        preOrder(T->lchild);
        preOrder(T->rchild);
    }
}

void inOrder(BiTree T)
{
    if (T != NULL)
    {
        inOrder(T->lchild);
        printf("%c", T->data);
        inOrder(T->rchild);
    }
}

void postOrder(BiTree T)
{
    if (T != NULL)
    {
        postOrder(T->lchild);
        postOrder(T->rchild);
        printf("%c", T->data);
    }
}