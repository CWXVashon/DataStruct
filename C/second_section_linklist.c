//
//  second_section_linklist.c
//  data_struct
//
//  Created by mac on 2020/5/23.
//  Copyright © 2020 mingxi. All rights reserved.
//

#include "second_section_linklist.h"

// 例 2.5 一个链表中元素为：{a1,b1,a2,b2,a3,b3...}，拆分成两个都带头结点的链表：{a1,a2...}、{bn,bn-1...}
void example2_5(void)
{
    int i;
    LinkList *L, *L1, *L2, *L1_P, *L1_N, *L2_N;
    // 创建总链表 L
    initList(&L);
    // 初始化数据
    for(i = 1; i <= 8; i++)
        listInsert(&L, i, i);
    // 打印数据
    printf("链表 L 的数据元素为：");
    displayList(L);
    // 拆分链表
    L1 = L;
    L1_P = L1;
    L1_N = L->next;
    initList(&L2);
    while(L1_N != NULL)
    {
        // L1 使用尾插法
        L1_P->next = L1_N;
        L1_P = L1_N;
        L1_N = L1_N->next;
        // L2 使用头插法
        L2_N = L1_N->next;
        L1_N->next = L2->next;
        L2->next = L1_N;
        L1_N = L2_N;
    }
    L1_P->next = NULL;
    // 打印数据
    printf("链表 L1 的数据元素为：");
    displayList(L1);
    printf("链表 L2 的数据元素为：");
    displayList(L2);
    // 释放资源
    destroyList(&L1);
    destroyList(&L2);
}

// 例 2.6 将链表中最大的结点删除
void example2_6(void)
{
    LinkList *list = NULL;
    initList(&list);
    listInsert(&list, 4, 1);
    listInsert(&list, 5, 2);
    listInsert(&list, 1, 3);
    listInsert(&list, 2, 4);
    printf("链表 L 的数据元素为：");
    displayList(list);
    printf("删除链表中数据元素最大的节点\n");
    void deleteMaxNode(LinkList **);
    deleteMaxNode(&list);
    printf("链表 L 的数据元素为：");
    displayList(list);
    destroyList(&list);
}

// 例 2.7 将链表排序
void example2_7(void)
{
    LinkList *list = NULL;
    initList(&list);
    listInsert(&list, 4, 1);
    listInsert(&list, 5, 2);
    listInsert(&list, 1, 3);
    listInsert(&list, 2, 4);
    printf("链表 L 的数据元素为：");
    displayList(list);
    printf("链表排序\n");
    void sortInsert(LinkList *);
    sortInsert(list);
    printf("链表 L 的数据元素为：");
    displayList(list);
    destroyList(&list);
}

// 例 2.10 统计循环单链表中元素 data 域为 5 的结点个数
void example2_10(void)
{
    LinkList *list = NULL;
    initList(&list);
    listInsert(&list, 4, 1);
    listInsert(&list, 5, 2);
    listInsert(&list, 1, 3);
    listInsert(&list, 2, 4);
    listInsert(&list, 5, 5);
    // 链接首尾，形成循环单链表
    void linkHeadAndStern(LinkList *);
    linkHeadAndStern(list);
    printf("循环链表 L 的数据元素为：");
    void displayCirculationList(LinkList *);
    displayCirculationList(list);
    int count(LinkList *, LElem);
    printf("链表 L 中结点 data 域为 5 的结点有 %d 个\n", count(list, 5));
    void destroyCirculationList(LinkList **);
    destroyCirculationList(&list);
}

// 链表相关---实验 2.2
void practice2_2(void)
{
    
}

// 删除链表中最大的结点
void deleteMaxNode(LinkList **list)
{
    LinkList *prior = *list, *current = (*list)->next, *maxPrior = prior, *max = current;
    while(current != NULL)
    {
        while(max->data < current->data)
        {
            maxPrior = prior;
            max = current;
        }
        prior = current;
        current = current->next;
    }
    // 断开链接
    maxPrior->next = max->next;
    free(max);
}

// 链表排序
void sortInsert(LinkList *list)
{
    LinkList *block = list->next->next, *nextBlock, *target;
    // 切断原链，重新组建
    list->next->next = NULL;
    while(block != NULL)
    {
        // 存起当前块的下一块
        nextBlock = block->next;
        // 复位拼接后的链表
        target = list;
        while(target->next != NULL && target->next->data < block->data)
            target = target->next;
         // 通过上面的循环，可知目标链表的下一个区域的数据比当前块的数据大，所以将该数据拼接在当前块的后面
        block->next = target->next;
        target->next = block;
        block = nextBlock;
    }
}

// 统计链表中的特定元素个数
int count(LinkList *list, LElem e)
{
    int count = 0;
    LinkList *temp = list->next;
    // 当前指向的结点不是头结点
    while(temp != list)
    {
        if(temp->data == e)
            count++;
        temp = temp->next;
    }
    return count;
}

// 形成循环链表
void linkHeadAndStern(LinkList *list)
{
    LinkList *temp = list;
    while(temp->next != NULL)
        temp = temp->next;
    temp->next = list;
}

// 打印循环链表
void displayCirculationList(LinkList *list)
{
    LinkList *temp = list->next;
    while(temp != list)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// 销毁循环链表
void destroyCirculationList(LinkList **list)
{
    LinkList *prior = (*list)->next, *next = prior->next;
    // 将循环链表切断
    (*list)->next = NULL;
    while(next != NULL)
    {
        free(prior);
        prior = next;
        next = prior->next;
    }
    free(prior);
}
