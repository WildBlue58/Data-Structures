#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#endif

#define MAX 20              // 城市名称最大长度
#define MAXSIZE 11          // 最大顶点数
#define INFINITY 0x7fffffff // 无穷大

// ==================== 数据结构声明 ====================
// 本程序使用的主要数据结构：
// 1. 图（Graph）- 使用邻接矩阵（Adjacency Matrix）表示的无向网
// 2. 邻接矩阵 - 二维数组存储顶点之间的边和权重信息
// 3. 数组（Array）- 用于存储距离、路径、标记等信息
// =====================================================

typedef struct
{
    char vexs[11][MAX];         // 城市名称数组（顶点数组）
    int arcs[MAXSIZE][MAXSIZE]; // 邻接矩阵（存储边的权重）
    int vexnum, arcnum;         // 顶点数和边数
} AMGraph;

// ==================== 基础操作函数 ====================

// 查找顶点位置
int LocateVex(AMGraph G, char v[])
{
    for (int i = 0; i < G.vexnum; i++)
    {
        if (strcmp(G.vexs[i], v) == 0)
            return i;
    }
    return -1;
}

// 初始化城市名称
void InitCityNames(AMGraph *G)
{
    strcpy(G->vexs[0], "九江市");
    strcpy(G->vexs[1], "景德镇");
    strcpy(G->vexs[2], "宜春市");
    strcpy(G->vexs[3], "南昌市");
    strcpy(G->vexs[4], "上饶市");
    strcpy(G->vexs[5], "新余市");
    strcpy(G->vexs[6], "鹰潭市");
    strcpy(G->vexs[7], "吉安市");
    strcpy(G->vexs[8], "萍乡市");
    strcpy(G->vexs[9], "抚州市");
    strcpy(G->vexs[10], "赣州市");
}

// 初始化邻接矩阵
void InitMatrix(AMGraph *G)
{
    for (int i = 0; i < G->vexnum; i++)
    {
        for (int j = 0; j < G->vexnum; j++)
        {
            G->arcs[i][j] = (i == j) ? 0 : INFINITY;
        }
    }
}

// 添加无向边（双向）
void AddEdge(AMGraph *G, int i, int j, int weight)
{
    G->arcs[i][j] = weight;
    G->arcs[j][i] = weight;
}

// 建立城市之间的连接关系
void BuildConnections(AMGraph *G)
{
    // 九江市(0)的连接
    AddEdge(G, 0, 1, 143); // 九江市 <-> 景德镇
    AddEdge(G, 0, 2, 336); // 九江市 <-> 宜春市
    AddEdge(G, 0, 3, 124); // 九江市 <-> 南昌市

    // 景德镇(1)的连接
    AddEdge(G, 1, 3, 180); // 景德镇 <-> 南昌市
    AddEdge(G, 1, 4, 260); // 景德镇 <-> 上饶市

    // 宜春市(2)的连接
    AddEdge(G, 2, 3, 207); // 宜春市 <-> 南昌市
    AddEdge(G, 2, 5, 41);  // 宜春市 <-> 新余市
    AddEdge(G, 2, 8, 74);  // 宜春市 <-> 萍乡市

    // 南昌市(3)的连接
    AddEdge(G, 3, 4, 249); // 南昌市 <-> 上饶市
    AddEdge(G, 3, 5, 153); // 南昌市 <-> 新余市
    AddEdge(G, 3, 6, 178); // 南昌市 <-> 鹰潭市
    AddEdge(G, 3, 7, 214); // 南昌市 <-> 吉安市
    AddEdge(G, 3, 8, 266); // 南昌市 <-> 萍乡市
    AddEdge(G, 3, 9, 96);  // 南昌市 <-> 抚州市

    // 上饶市(4)的连接
    AddEdge(G, 4, 6, 109); // 上饶市 <-> 鹰潭市

    // 新余市(5)的连接
    AddEdge(G, 5, 8, 127); // 新余市 <-> 萍乡市

    // 鹰潭市(6)的连接
    AddEdge(G, 6, 9, 106); // 鹰潭市 <-> 抚州市

    // 吉安市(7)的连接
    AddEdge(G, 7, 8, 177);  // 吉安市 <-> 萍乡市
    AddEdge(G, 7, 9, 270);  // 吉安市 <-> 抚州市
    AddEdge(G, 7, 10, 154); // 吉安市 <-> 赣州市

    // 萍乡市(8)的连接
    AddEdge(G, 8, 10, 372); // 萍乡市 <-> 赣州市

    // 抚州市(9)的连接
    AddEdge(G, 9, 10, 448); // 抚州市 <-> 赣州市
}

// 创建无向网
void CreateUDN(AMGraph *G)
{
    G->vexnum = 11;
    G->arcnum = 0;
    InitCityNames(G);
    InitMatrix(G);
    BuildConnections(G);
}

// ==================== Dijkstra算法核心 ====================

// 选择下一个要观察的顶点
int choose(int distance[], int found[], int vertex_num)
{
    int min = INFINITY;
    int minPos = -1;
    for (int i = 0; i < vertex_num; i++)
    {
        if (distance[i] < min && found[i] == 0)
        {
            min = distance[i];
            minPos = i;
        }
    }
    return minPos;
}

// Dijkstra算法核心：计算从起点到所有顶点的最短距离
void DijkstraCore(AMGraph G, int begin, int distance[], int path[])
{
    int found[MAXSIZE];

    // 初始化
    for (int i = 0; i < G.vexnum; i++)
    {
        found[i] = 0;
        path[i] = -1;
        distance[i] = G.arcs[begin][i];
    }

    found[begin] = 1;
    distance[begin] = 0;

    // 主循环
    for (int i = 1; i < G.vexnum; i++)
    {
        int next = choose(distance, found, G.vexnum);
        if (next == -1)
            break;

        found[next] = 1;

        // 更新距离
        for (int j = 0; j < G.vexnum; j++)
        {
            if (!found[j] && distance[next] != INFINITY && G.arcs[next][j] != INFINITY)
            {
                int newDist = distance[next] + G.arcs[next][j];
                if (newDist < distance[j])
                {
                    distance[j] = newDist;
                    path[j] = next;
                }
            }
        }
    }
}

// 回溯并显示路径
void DisplayPath(AMGraph G, int begin, int end, int path[])
{
    int route[MAXSIZE];
    int count = 0;
    int temp = end;

    // 回溯路径
    while (temp != -1)
    {
        route[count++] = temp;
        temp = path[temp];
    }

    // 输出路径
    printf("路径：");
    for (int i = count - 1; i >= 0; i--)
    {
        printf("%s", G.vexs[route[i]]);
        if (i > 0)
            printf("->");
    }
    printf("\n");
}

// ==================== 业务功能函数 ====================

// 查询两个城市之间的最短路径
void Dijkstra(AMGraph G, char c1[], char c2[])
{
    int begin = LocateVex(G, c1);
    int end = LocateVex(G, c2);

    if (begin == -1 || end == -1)
    {
        printf("城市名称输入错误！\n");
        return;
    }

    int distance[MAXSIZE];
    int path[MAXSIZE];

    DijkstraCore(G, begin, distance, path);

    // 输出结果
    if (distance[end] == INFINITY)
    {
        printf("%s->%s之间没有路径！\n", c1, c2);
    }
    else
    {
        printf("%s->%s的最短距离为%d\n", c1, c2, distance[end]);
        DisplayPath(G, begin, end, path);
    }
}

// 查询某个城市到所有其他城市的最短距离
void QueryAllDistances(AMGraph G, char c[])
{
    int begin = LocateVex(G, c);
    if (begin == -1)
    {
        printf("城市名称输入错误！\n");
        return;
    }

    int distance[MAXSIZE];
    int path[MAXSIZE];

    DijkstraCore(G, begin, distance, path);

    printf("\n========== %s到各城市的最短距离 ==========\n", c);
    for (int i = 0; i < G.vexnum; i++)
    {
        if (i != begin)
        {
            if (distance[i] == INFINITY)
                printf("%s -> %s: 无路径\n", c, G.vexs[i]);
            else
                printf("%s -> %s: %d\n", c, G.vexs[i], distance[i]);
        }
    }
    printf("==========================================\n\n");
}

// 显示所有城市列表
void DisplayAllCities(AMGraph G)
{
    printf("\n========== 江西省城市列表 ==========\n");
    for (int i = 0; i < G.vexnum; i++)
        printf("%2d. %s\n", i + 1, G.vexs[i]);
    printf("=====================================\n\n");
}

// 显示邻接矩阵
void DisplayMatrix(AMGraph G)
{
    printf("\n========== 城市距离邻接矩阵 ==========\n");
    printf("      ");
    for (int i = 0; i < G.vexnum; i++)
        printf("%-8s", G.vexs[i]);
    printf("\n");

    for (int i = 0; i < G.vexnum; i++)
    {
        printf("%-6s", G.vexs[i]);
        for (int j = 0; j < G.vexnum; j++)
        {
            if (G.arcs[i][j] == INFINITY)
                printf("  ∞     ");
            else
                printf("%-8d", G.arcs[i][j]);
        }
        printf("\n");
    }
    printf("=====================================\n\n");
}

// 显示主菜单
void DisplayMenu()
{
    printf("\n");
    printf("╔══════════════════════════════════════╗\n");
    printf("║    北斗卫星导航系统 - 功能菜单       ║\n");
    printf("╠══════════════════════════════════════╣\n");
    printf("║  1. 查询两个城市之间的最短路径       ║\n");
    printf("║  2. 查询某城市到所有城市的最短距离   ║\n");
    printf("║  3. 显示所有城市列表                 ║\n");
    printf("║  4. 显示城市距离邻接矩阵             ║\n");
    printf("║  0. 退出系统                         ║\n");
    printf("╚══════════════════════════════════════╝\n");
    printf("请选择功能 (0-4): ");
}

// ==================== 主函数 ====================

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif

    AMGraph G;
    char city1[20], city2[20];
    int choice;

    CreateUDN(&G);
    printf("欢迎使用北斗卫星导航系统！\n");

    while (1)
    {
        DisplayMenu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("\n请输入两个城市名（用空格分隔）: ");
            scanf("%s%s", city1, city2);
            Dijkstra(G, city1, city2);
            break;

        case 2:
            printf("\n请输入城市名: ");
            scanf("%s", city1);
            QueryAllDistances(G, city1);
            break;

        case 3:
            DisplayAllCities(G);
            break;

        case 4:
            DisplayMatrix(G);
            break;

        case 0:
            printf("\n感谢使用北斗卫星导航系统，再见！\n");
            system("pause");
            return 0;

        default:
            printf("\n输入错误，请输入0-4之间的数字！\n");
            break;
        }
    }

    return 0;
}
