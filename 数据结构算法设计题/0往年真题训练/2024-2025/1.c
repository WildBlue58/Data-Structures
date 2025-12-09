// 请设计一个算法，在顺序表中删除第一个值为x的元素, 未找到x打印错误信息并返回0，删除成功返回1

#include <stdio.h>
#include <stdlib.h>

// 定义顺序表中存放的数据类型，这里用 int 方便演示
typedef int ElemType;

// 顺序表的结构体：list 指向动态分配的数组，len 表示当前元素个数
typedef struct
{
    ElemType *list;
    int len;
} SeqList;

// 在顺序表 La 中删除第一个值等于 x 的元素
// 找到并删除返回 1；如果不存在该元素，打印提示并返回 0
int Sqlist_DeleteX(SeqList *La, int x)
{
    int i, pos; // i 为循环变量，pos 记录要删除的元素下标

    // 线性扫描，找到第一个值为 x 的元素位置
    for (i = 0; i < La->len; i++)
    {
        if (La->list[i] == x)
        {
            break;
        }
    }
    // 扫描结束仍未找到，说明不存在目标元素
    if (i >= La->len)
    {
        printf("不存在删除结点\n");
        return 0;
    }
    pos = i; // 保存要删除的位置，后续用于元素前移

    // 从被删除位置开始，将后续元素依次前移，覆盖被删元素
    for (i = pos; i < La->len - 1; i++)
    {
        La->list[i] = La->list[i + 1];
    }
    La->len--; // 顺序表长度减 1
    return 1;  // 删除成功
}

int main()
{
    SeqList La;

    // 简单演示：为顺序表分配容量为 100 的存储空间，并初始化长度为 0
    La.list = (ElemType *)malloc(sizeof(ElemType) * 100);
    La.len = 0;

    // 此处可自行填充数据并调用 Sqlist_DeleteX(&La, x) 进行测试

    // 申请的内存使用完毕后应 free，这里省略释放是因为示例程序立即结束
    return 0;
}