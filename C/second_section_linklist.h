//
//  second_section_linklist.h
//  data_struct
//
//  Created by mac on 2020/5/23.
//  Copyright © 2020 mingxi. All rights reserved.
//  单链表

#ifndef second_section_linklist_h
#define second_section_linklist_h

#include <stdio.h>
#include <stdlib.h>

typedef int LElem;
typedef struct LNode
{
    LElem data;
    struct LNode *next;
} LinkList;

// 初始化单链表
static void initList(LinkList **list)
{
    (*list) = malloc(sizeof(LinkList));
    (*list)->next = NULL;
}

// 销毁单链表
static void destroyList(LinkList **list)
{
    LinkList *prior = *list, *next = (*list)->next;
    while(next != NULL)
    {
        free(prior);
        prior = next;
        next = prior->next;
    }
    free(prior);
}

// 判断单链表是否为空
static int listEmpty(LinkList *list)
{
    if(list->next == NULL)
        return 1;
    return 0;
}

// 获取单链表的长度
static int listLength(LinkList *list)
{
    int length = 0;
    LinkList *temp = list;
    while(temp->next != NULL)   // 头结点不存放数据，所以不算入长度
    {
        length++;
        temp = temp->next;
    }
    return length;
}

// 输出单链表
static void displayList(LinkList *list)
{
    LinkList *temp = list->next;
    while(temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// 获取单链表中某个数据元素值
// 注意，这里的 position 从 1 开始，因为头结点不存数据
static int getElem(LinkList *list, int position, LElem *e)
{
    int i = 0;
    LinkList *temp = list;
    while(i < position && temp != NULL)
    {
        i++;
        temp = temp->next;
    }
    if(temp == NULL)
        return 0;
    else
        (*e) = temp->data;
    return 1;
}

// 按照元素值查找(返回物理序号，从 1 开始)
static int locateElem(LinkList *list, LElem e)
{
    int i = 1;
    LinkList *temp = list->next;
    while(temp != NULL && temp->data != e)
    {
        i++;
        temp = temp->next;
    }
    if(temp == NULL)
        return 0;
    else
        return i;
}

// 插入数据元素
static int listInsert(LinkList **list, LElem e, int position)
{
    int i = 0;
    LinkList *prior = *list, *next;
    // 找到目标位置的前一个位置
    while(i < position - 1 && prior != NULL)
    {
        i++;
        prior = prior->next;
    }
    if(prior == NULL)
        return 0;
    else
    {
        next = malloc(sizeof(LinkList));
        next->data = e;
        next->next = prior->next;
        prior->next = next;
        return 1;
    }
}

// 删除数据元素
static int listDelete(LinkList **list, LElem *e, int position)
{
    int i = 0;
    LinkList *prior = *list, *next;
    // 找到目标位置的前一个位置
    while(i < position - 1 && prior != NULL)
    {
        i++;
        prior = prior->next;
    }
    if(prior == NULL || prior->next == NULL)
        return 0;
    else
    {
        next = prior->next;
        (*e) = next->data;
        prior->next = next->next;
        free(next);
        return 1;
    }
}
#endif /* second_section_linklist_h */
