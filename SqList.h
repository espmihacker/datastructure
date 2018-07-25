#include <iostream>
#include <iomanip>
#include <stdlib.h> // 该文件包含malloc()、realloc()和free()等函数

using namespace std;

#define LIST_INIT_SIZE 100 // 顺序表(默认的)的初始分配最大容量
#define LISTINCREMENT 10   // (默认的)增补空间量

typedef int ElemType; // 顺序表中元素类型为int

typedef struct
{
    ElemType *elem;    // 存储数据元素的一维数组
    int length;        // 线性表的当前长度
    int listsize;      // 当前分配的数组容量（以ElemType为单位）
    int incrementsize; // 增补空间量（以ElemType为单位）
} SqList;

void InitList_Sq(SqList &L, int maxsize = LIST_INIT_SIZE, int incresize = LISTINCREMENT)
{
    // 构造一个最大容量为maxsize的顺序表 L
    L.elem = (ElemType *)malloc(maxsize * sizeof(ElemType));
    // 为顺序表分配一个最大容量为 maxsize 的数组空间
    if (!L.elem)
        exit(1);                 // 存储分配失败
    L.length = 0;                // 顺序表中当前所含元素个数为 0
    L.listsize = maxsize;        // 该顺序表可以容纳maxsize个数据元素
    L.incrementsize = incresize; // 需要时可扩容incresize个元素空间
} // InitList_Sq

int ListLength_Sq(SqList L)
{
    return L.length;
} // ListLength_Sq

bool ListEmpty_Sq(SqList L)
{
    if (L.length == 0)
        return true;
    else
        return false;
}

int LocateElem_Sq(SqList L, ElemType e)
{
    for (int i = 0; i < L.length; i++)
        if (L.elem[i] == e)
            return i; // 找到满足判定的数据元素为第 i 个元素
    return -1;        // 该线性表中不存在满足判定的数据元素
} //LocateElem_Sq

bool ListInsert_Sq(SqList &L, int i, ElemType e)
{
    // 在顺序表L的第i个元素之前插入新的元素e，
    // 若表中当前容量不足，则按预定义的增量扩容
    int j;
    if (i < 0 || i > L.length)
        return false;           // i值不合法
    if (L.length >= L.listsize) // 当前存储空间已满，增补空间
    {
        L.elem = (ElemType *)realloc(L.elem, (L.listsize + L.incrementsize) * sizeof(ElemType));
        if (!L.elem)
            exit(1);                   // 存储分配失败
        L.listsize += L.incrementsize; // 当前存储容量增加
    }
    for (j = L.length; j > i; j--) // 被插入元素之后的元素左移
        L.elem[j] = L.elem[j - 1];
    L.elem[i] = e; // 插入元素e
    L.length++;    // 表长增1
    return true;
} // ListInsert_Sq

bool ListInsert_Sq_1(SqList &L, ElemType e)
{
    // 在递增有序顺序表L中插入新的元素e，
    // 若表中当前容量不足，则按预定义的增量扩容
    int i, j;
    if (L.length >= L.listsize) // 当前存储空间已满，增补空间
    {
        L.elem = (ElemType *)realloc(L.elem, (L.listsize + L.incrementsize) * sizeof(ElemType));
        if (!L.elem)
            exit(1);                   // 存储分配失败
        L.listsize += L.incrementsize; // 当前存储容量增加
    }
    for (i = 0; i < L.length && e > L.elem[i]; i++)
        ;
    for (j = L.length; j > i; j--) // 被插入元素之后的元素左移
        L.elem[j] = L.elem[j - 1];
    L.elem[i] = e; // 插入元素e
    L.length++;    // 表长增1
    return true;
} // ListInsert_Sq

bool ListDelete_Sq(SqList &L, int i, ElemType &e)
{
    // 在顺序表L中删除第i个元素，并用e返回其值
    int j;
    if (i < 0 || i > L.length)
        return false; // i值不合法
    if (L.length <= 0)
        return false;                       // 表空无数据元素可删
    e = L.elem[i];                          // 被删除元素的值赋给e
    for (j = i + 1; j <= L.length - 1; j++) // 被删除元素之后的元素前移
        L.elem[j - 1] = L.elem[j];
    L.length--; // 表长减1
    return true;
} // ListDelete_Sq

bool GetElem_Sq(SqList L, int i, ElemType &e)
{
    // 取出顺序表L中第i个元素，并用e返回其值。
    if (i < 0 || i > L.length)
        return false; // i值不合法
    if (L.length <= 0)
        return false; // 表空无数据元素可取
    e = L.elem[i];    // 被取元素的值赋给e
    return true;
} // GetElem_Sq

void ListTraverse_Sq(SqList L)
{
    int i;
    for (i = 0; i < L.length; i++)
        cout << setw(6) << L.elem[i];
    cout << endl;
} // ListTraverse_Sq

void DestroyList_Sq(SqList &L)
{
    // 释放顺序表L所占存储空间
    free(L.elem);
    L.elem = NULL;
    L.listsize = 0;
    L.length = 0;
} // DestroyList_Sq

void visualization(SqList L, char *filename)
{
    int temp;
    FILE *stream;
    if (NULL == (stream = fopen(filename, "w")))
    {
        printf("open file error");
        exit(0);
    }
    fprintf(stream, "digraph\n{\nnode [shape = box];\n");
    for (int i = 0; i < L.length; i++)
        if (GetElem_Sq(L, i, temp))
        {
            fprintf(stream, "box%d [label = \"%d\"];\n", i, temp);
        }
    fprintf(stream, "}");
    fclose(stream);
    system("dot -Tpng showsqlist.dot -o showsqlist.png");
    system("showsqlist.png");
}
