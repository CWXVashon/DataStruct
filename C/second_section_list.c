//
//  second_section.c
//  data_struct
//
//  Created by mac on 2020/5/19.
//  Copyright © 2020 mingxi. All rights reserved.
//  数据结构第二章练习题

#include<stdio.h>
#include<stdlib.h>

#define MaxSize 50

typedef char Elem;
typedef struct
{
    Elem data[MaxSize];
    int length;
} SqList;

// 例 2.3
void example2_3(void)
{
    SqList *list = NULL;
    // 初始化
    void initList(SqList **);
    initList(&list);
    // 插入数据
    int listInsert(SqList *, Elem, int);
    int i;
    for(i = 0; i < 10; i++)
    {
        int success = listInsert(list, 'x', i);
        if(success)
            printf("insert success\n");
    }
    int success = listInsert(list, 'a', i);
    if(success)
        printf("insert success\n");
    // 显示列表内的元素
    void displayList(SqList *);
    displayList(list);
    printf("list delete elem x before length：%d\n", list->length);
    // 通过指定元素的值，删除元素
    void listDeleteByElem(SqList *, Elem);
    listDeleteByElem(list, 'x');
    printf("list delete elem x after length：%d\n", list->length);
    // 释放资源
    void destroyList(SqList **);
    destroyList(&list);
}

// 例 2.4
void example2_4(void)
{
    SqList *list = NULL;
    // 初始化
    void initList(SqList **);
    initList(&list);
    // 插入数据
    int listInsert(SqList *, Elem, int);
    listInsert(list, 3, 0);
    listInsert(list, 8, 1);
    listInsert(list, 2, 2);
    listInsert(list, 7, 3);
    listInsert(list, 1, 4);
    listInsert(list, 5, 5);
    listInsert(list, 3, 6);
    listInsert(list, 4, 7);
    listInsert(list, 6, 8);
    listInsert(list, 0, 9);
    // 显示列表内的元素
    printf("顺序表排序前为：");
    void displayList(SqList *);
    displayList(list);
    // 排序
//    void sort_first(SqList *);
//    sort_first(list); // 自增了 9 次，改变了 9 次
    void sort_second(SqList *);
    sort_second(list);  // 自增了 10 次，改变了 7 次
    printf("顺序表排序后为：");
    displayList(list);
    // 释放资源
    void destroyList(SqList **);
    destroyList(&list);
}

// 线性表相关---实验 2.1
void practice2_1(void)
{
//    SqList *list = NULL;
}

// 初始化线性表
void initList(SqList **list)
{
    (*list) = malloc(sizeof(SqList));
    (*list)->length = 0;
}

// 销毁线性表
void destroyList(SqList **list)
{
    free(*list);
}

// 判断线性表是否为空
int listEmpty(SqList *list)
{
    if(list->length == 0)
        return 1;
    return 0;
}

// 获取线性表的长度
int listLength(SqList *list)
{
    return list->length;
}

// 输出线性表
void displayList(SqList *list)
{
    int i;
    for(i = 0; i < list->length; i++)
        printf("%d ", list->data[i]);
    printf("\n");
}

// 获取线性表中某个数据元素值(通过物理序号)
int getElem(SqList *list, int position, Elem *e)
{
    if(position < 0 || position > list->length)
        return 0;
    *e = list->data[position];
    return 1;
}

// 按照元素值查找(返回物理序号)
int locateElem(SqList *list, Elem e)
{
    int i = 0;
    while(i < list->length && list->data[i] != e)
        i++;
    if(i >= list->length)
        return 0;
    else
        return i;
}

// 插入数据元素
int listInsert(SqList *list, Elem e, int position)
{
    int i;
    if(position < 0 || position > list->length)
        return 0;
    // 将插入位置之后的元素往后移动
    for(i = list->length; i > position; i--)
        list->data[i] = list->data[i - 1];
    list->data[position] = e;
    list->length++;
    return 1;
}

// 删除数据元素
int listDelete(SqList *list, Elem *e, int position)
{
    int i;
    if(position < 0 || position >= list->length)
        return 0;
    // 保存需要删除的元素
    *e = list->data[position];
    // 将删除位置之后的元素往前移动
    for(i = position; i < list->length; i++)
        list->data[i] = list->data[i + 1];
    list->length--;
    return 1;
}

// 通过指定元素的值，删除元素
void listDeleteByElem(SqList *list, Elem e)
{
    if(listEmpty(list))
    {
        printf("list is empty\n");
        return;
    }
    int i, j, length = listLength(list);
    for(i = 0, j = i; i < length; i++)
    {
        if(list->data[j] == e)
        {
            j++;
            printf("delete elem success\n");
        }
        else
        {
            list->data[i - j] = list->data[i];
        }
    }
    list->length -= j;
}

void sort_first(SqList *list)
{
    int period = 0, change = 0, i = 0, j = list->length - 1;
    Elem temp, e = list->data[0];
    
    while(i < j)
    {
        while(i < j && list->data[j] > e)
        {
            j--;
            period++;
        }
        while(i < j && list->data[i] <= e)
        {
            i++;
            period++;
        }
        if(i < j)
        {
            temp = list->data[i];
            list->data[i] = list->data[j];
            list->data[j] = temp;
            change += 3;
        }
    }
    
    temp = list->data[0];
    list->data[0] = list->data[j];
    list->data[j] = temp;
    change += 3;
    printf("first 循环了 %d 次，改变了 %d 次\n", period, change);
}

void sort_second(SqList *list)
{
    int period = 0, change = 0, i = 0, j = list->length - 1;
    Elem e = list->data[0];
    
    while(i < j)
    {
        while(i < j && list->data[j] > e)
        {
            j--;
            period++;
        }
        list->data[i] = list->data[j];
        i++;
        period++;
        change++;
        while(i < j && list->data[i] <= e)
        {
            i++;
            period++;
        }
        list->data[j] = list->data[i];
        j--;
        period++;
        change++;
    }
    list->data[i] = e;
    change++;
    printf("second 循环了 %d 次，改变了 %d 次\n", period, change);
}


