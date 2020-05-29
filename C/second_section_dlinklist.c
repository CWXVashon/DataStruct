//
//  second_section_dlinklist.c
//  data_struct
//
//  Created by mac on 2020/5/25.
//  Copyright © 2020 mingxi. All rights reserved.
//

#include "second_section_dlinklist.h"

// 例 2.8，头插法，逆序双链表中的结点
void example2_8(void)
{
    int i;
    DLinkList *list = NULL;
    // 创建双链表
    initList(&list);
    // 初始化双链表
    for(i = 1; i <= 8; i++)
        listInsert(&list, i, i);
    // 输出双链表中的值
    printf("双链表中结点的值为：");
    displayList(list);
    // 双链表逆序
    void reverse(DLinkList *);
    reverse(list);
    // 输出双链表中的值
    printf("双链表中结点的值为：");
    displayList(list);
    // 释放双链表
    destroyList(&list);
}

// 例 2.9，使双链表元素递增有序的排列
void example2_9(void)
{
    DLinkList *list = NULL;
    // 创建双链表
    initList(&list);
    // 初始化双链表
    listInsert(&list, 8, 1);
    listInsert(&list, 3, 2);
    listInsert(&list, 9, 3);
    listInsert(&list, 6, 4);
    // 输出双链表中的值
    printf("双链表中结点的值为：");
    displayList(list);
    // 排序
    void sortDLinkList(DLinkList *);
    sortDLinkList(list);
    printf("双链表中结点的值为：");
    displayList(list);
    // 释放双链表
    destroyList(&list);
}

// 例 2.11，删除循环双链表中第一个值域为 5 的结点
void example2_11(void)
{
    DLinkList *list = NULL;
    // 创建双链表
    initList(&list);
    // 初始化双链表
    listInsert(&list, 8, 1);
    listInsert(&list, 3, 2);
    listInsert(&list, 9, 3);
    listInsert(&list, 6, 4);
    listInsert(&list, 5, 5);
    // 形参循环双链表
    void linkDHeadAndStern(DLinkList *);
    linkDHeadAndStern(list);
    // 输出双链表中的值
    printf("双链表中结点的值为：");
    void displayDLinkList(DLinkList *);
    displayDLinkList(list);
    // 删除值域为 5 的结点
    int deleteDLinkListNode(DLinkList **, DLElem);
    int success = deleteDLinkListNode(&list, 5);
    if(success)
        printf("删除结点成功\n");
    else
        printf("不存在需要删除的结点\n");
    printf("双链表中结点的值为：");
    displayDLinkList(list);
    // 释放资源
    void destroyCirculationDList(DLinkList **);
    destroyCirculationDList(&list);
}

// 双链表逆序
void reverse(DLinkList *list)
{
    // 获取双链表中第二个结点
    DLinkList *prior = list->next->next, *next;
    // 双链表中只有第一结点，无论怎么倒叙还是自己，所以在这里切断下面的循环可以少一次
    list->next->next = NULL;
    while(prior != NULL)
    {
        // 存下当前结点的后继结点
        next = prior->next;
        // 将 prior 指针指向的结点插入到 list 中
        prior->prior = list;
        prior->next = list->next;
        list->next->prior = prior;
        list->next = prior;
        prior = next;
    }
}

// 排序双链表
void sortDLinkList(DLinkList *list)
{
    // 只有一个元素也算有序
    DLinkList *first = list->next->next, *target, *next;
    list->next->next = NULL;
    while(first != NULL)
    {
        next = first->next;
        target = list;
        while(target->next != NULL && target->next->data < first->data)
            target = target->next;
        first->next = target->next;
        first->prior = target;
        if(target->next != NULL)
            target->next->prior = first;
        target->next = first;
        first = next;
    }
}

// 形成循环链表
void linkDHeadAndStern(DLinkList *list)
{
    DLinkList *temp = list->next;
    while(temp->next != NULL)
        temp = temp->next;
    // 尾结点的后继指向头结点，头结点的前驱指向尾节点
    temp->next = list;
    list->prior = temp;
}

// 打印循环双链表中的结点的值
void displayDLinkList(DLinkList *list)
{
    DLinkList *temp = list->next;
    while(temp != list)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// 删除循环双链表中第一个值域为 e 的结点
int deleteDLinkListNode(DLinkList **list, DLElem e)
{
    DLinkList *temp = (*list)->next;
    while(temp != (*list) && temp->data != e)
        temp = temp->next;
    // 不存在需要删除的结点
    if(temp == (*list))
        return 0;
    // 找到结点，删除结点
    temp->prior->next = temp->next;
    temp->next->prior = temp->prior;
    free(temp);
    return 1;
}

// 销毁循环双链表
void destroyCirculationDList(DLinkList **list) {
    DLinkList *prior = (*list)->next, *next;
    // 切断循环双链表
    (*list)->next = NULL;
    if(prior != NULL)
    {
        prior->prior = NULL;
        while(prior->next != NULL)
        {
            next = prior->next;
            next->prior = NULL;
            prior->next = NULL;
            free(prior);
            prior = next;
        }
    }
    // 释放头结点
    free(*list);
}
