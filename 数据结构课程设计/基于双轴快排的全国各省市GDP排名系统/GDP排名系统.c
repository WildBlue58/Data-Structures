#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#endif

#define MAXSIZE 50

// 省市GDP信息结构体
typedef struct
{
    char province[10]; // 省市名称
    float gdp;         // GDP数据
} KeyType;

// GDP表结构体
typedef struct
{
    KeyType R[MAXSIZE]; // 存储省市GDP信息的数组
    int length;         // 当前元素的个数
} GDPTable;

// 函数声明
void Menu();
int data_read(char filename[], GDPTable *L);
void swap(KeyType *a, KeyType *b);
void DPQuicksort(KeyType *arr, int left, int right);
void display_raw_data(GDPTable *L);
void display_ranked_data(GDPTable *L);

// 菜单函数
void Menu()
{
    printf("========================================\n");
    printf("    全国各省市GDP排名系统\n");
    printf("========================================\n");
    printf("* 1: 数据导入                          *\n");
    printf("* 2: 原始数据                          *\n");
    printf("* 3: GDP排名                           *\n");
    printf("* 0: 系统退出                          *\n");
    printf("========================================\n");
}

// 数据导入函数
int data_read(char filename[], GDPTable *L)
{
    FILE *fp;
    char line[100];
    int count = 0;

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("无法打开文件: %s\n", filename);
        return 0;
    }

    printf("从指定文件导入数据(%s)!\n", filename);

    // 读取文件内容
    while (fgets(line, sizeof(line), fp) != NULL && count < MAXSIZE)
    {
        // 去除换行符
        line[strcspn(line, "\r\n")] = 0;

        // 解析每行数据：格式为 "省市名称 GDP值"
        if (sscanf(line, "%s %f", L->R[count].province, &L->R[count].gdp) == 2)
        {
            count++;
        }
    }

    fclose(fp);
    L->length = count;

    if (count > 0)
    {
        printf("文件导入数组成功!\n");
        printf("可根据菜单进行下一步操作\n");
        return 1;
    }
    else
    {
        printf("文件导入失败或文件为空!\n");
        return 0;
    }
}

// 交换两个数据元素的值
void swap(KeyType *a, KeyType *b)
{
    KeyType temp = *a;
    *a = *b;
    *b = temp;
}

// 双轴快排函数
void DPQuicksort(KeyType *arr, int left, int right)
{
    // 递归终止条件
    if (left >= right)
        return;

    // 确保左轴值小于右轴值
    if (arr[left].gdp > arr[right].gdp)
    {
        swap(&arr[left], &arr[right]);
    }

    // 选双轴：arr[left]为左轴，arr[right]为右轴
    float pivot1 = arr[left].gdp;  // 左轴值
    float pivot2 = arr[right].gdp; // 右轴值

    // 设置初值：index=left+1, lower=left+1, upper=right-1
    int index = left + 1;  // 当前访问的元素下标，代表中间待考察区间需要判断的数据起始位置
    int lower = left + 1;  // pivot1最终位置，[left, lower)为区间1（小于左轴）
    int upper = right - 1; // pivot2最终位置，(upper, right]为区间3（大于右轴）

    // index向右移动遍历过程中与两轴不断对比，进行适当交换
    // [lower, index)为区间2（在左右轴之间），[index, upper]为待考察区间
    while (index <= upper)
    {
        if (arr[index].gdp < pivot1)
        {
            // 小于左轴，放入区间1
            swap(&arr[index], &arr[lower]);
            lower++;
            index++;
        }
        else if (arr[index].gdp > pivot2)
        {
            // 大于右轴，放入区间3
            swap(&arr[index], &arr[upper]);
            upper--;
            // 注意：这里不移动index，因为交换后的元素需要重新判断
        }
        else
        {
            // 在区间2中（在左右轴之间）
            index++;
        }
    }

    // 将轴值放到正确位置
    // lower-1位置应该放左轴，upper+1位置应该放右轴
    swap(&arr[left], &arr[lower - 1]);
    swap(&arr[right], &arr[upper + 1]);

    // 对于划分好的三个区间，继续进行递归排序
    // 区间1: [left, lower-2]（小于左轴的元素）
    DPQuicksort(arr, left, lower - 2);
    // 区间2: [lower, upper]（在左右轴之间的元素）
    if (lower <= upper)
    {
        DPQuicksort(arr, lower, upper);
    }
    // 区间3: [upper+2, right]（大于右轴的元素）
    DPQuicksort(arr, upper + 2, right);
}

// 显示原始数据
void display_raw_data(GDPTable *L)
{
    printf("显示原始数据(单位: 亿元):\n");
    for (int i = 0; i < L->length; i++)
    {
        printf("%s: %.2f\n", L->R[i].province, L->R[i].gdp);
    }
}

// 显示排名数据（降序排列）
void display_ranked_data(GDPTable *L)
{
    // 创建副本进行排序，不改变原始数据
    KeyType temp[MAXSIZE];
    for (int i = 0; i < L->length; i++)
    {
        temp[i] = L->R[i];
    }

    // 使用双轴快排进行排序（升序）
    DPQuicksort(temp, 0, L->length - 1);

    printf("GDP排名(单位: 亿元):\n");
    // 降序输出（从大到小）
    for (int i = L->length - 1; i >= 0; i--)
    {
        printf("%d. %s: %.2f\n", L->length - i, temp[i].province, temp[i].gdp);
    }
}

// 主函数
int main()
{
// 设置Windows控制台编码为UTF-8，解决中文乱码问题
#ifdef _WIN32
    SetConsoleOutputCP(65001); // UTF-8编码
    SetConsoleCP(65001);       // UTF-8编码
#endif

    GDPTable gdpTable;
    gdpTable.length = 0;
    int choice;
    int data_loaded = 0; // 标记数据是否已加载

    while (1)
    {
        Menu();
        printf("根据菜单提示进行输入: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1: // 数据导入
            // 先尝试从当前目录读取，如果失败则尝试从d:\读取
            if (data_read("821data.txt", &gdpTable))
            {
                data_loaded = 1;
            }
            else if (data_read("d:\\821data.txt", &gdpTable))
            {
                data_loaded = 1;
            }
            break;

        case 2: // 原始数据
            if (data_loaded)
            {
                display_raw_data(&gdpTable);
            }
            else
            {
                printf("请先导入数据!\n");
            }
            break;

        case 3: // GDP排名
            if (data_loaded)
            {
                display_ranked_data(&gdpTable);
            }
            else
            {
                printf("请先导入数据!\n");
            }
            break;

        case 0: // 系统退出
            printf("感谢使用，再见!\n");
            exit(0);

        default:
            printf("无效的选择，请重新输入!\n");
            break;
        }

        printf("\n");
    }

    return 0;
}
