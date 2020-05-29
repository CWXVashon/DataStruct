//
//  second_section_dlinklist.h
//  data_struct
//
//  Created by mac on 2020/5/25.
//  Copyright © 2020 mingxi. All rights reserved.
//

#ifndef second_section_dlinklist_h
#define second_section_dlinklist_h

#include <stdio.h>
#include <stdlib.h>

typedef int DLElem;
typedef struct DLNode
{
    DLElem data;
    struct DLNode *prior;
    struct DLNode *next;
} DLinkList;

static void initList(DLinkList **list)
{
    (*list) = malloc(sizeof(DLinkList));
    (*list)->prior = NULL;
    (*list)->next = NULL;
}

static void destroyList(DLinkList **list)
{
    DLinkList *prior = *list, *next = (*list)->next;
    while(next->next != NULL)
    {
        prior->next = next->next;
        prior->next->prior = prior;
        free(next);
        next = prior->next;
    }
    prior->next = NULL;
    free(next);
    free(prior);
}

static int listEmpty(DLinkList *list)
{
    while(list->next == NULL)
        return 1;
    return 0;
}

static int listLength(DLinkList *list)
{
    int length = 0;
    DLinkList *temp = list;
    while(temp->next != NULL)
    {
        length++;
        temp = temp->next;
    }
    return length;
}

static void displayList(DLinkList *list)
{
    DLinkList *temp = list->next;
    while(temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

static int getElem(DLinkList *list, int position, DLElem *e)
{
    int i = 0;
    DLinkList *temp = list;
    while(temp != NULL && i < position)
    {
        i++;
        temp = temp->next;
    }
    
    if(temp == NULL)
        return 0;
    (*e) = temp->data;
    return 1;
}

static int locateElem(DLinkList *list, DLElem e)
{
    int position = 0;
    DLinkList *temp = list;
    while(temp != NULL && temp->data != e)
    {
        position++;
        temp = temp->next;
    }
    if(temp == NULL)
        return 0;
    return position;
}

static int listInsert(DLinkList **list, DLElem e, int position)
{
    int i = 1;
    DLinkList *prior = *list, *node;
    while(prior != NULL && i < position)
    {
        i++;
        prior = prior->next;
    }
    if(prior == NULL)
        return 0;
    node = malloc(sizeof(DLinkList));
    node->data = e;
    node->next = prior->next;
    node->prior = prior;
    if(prior->next != NULL)
        prior->next->prior = node;
    prior->next = node;
    return 1;
}

static int listDelete(DLinkList **list, DLElem *e, int position)
{
    int i = 0;
    DLinkList *temp = *list;
    while(temp != NULL && i < position)
    {
        i++;
        temp = temp->next;
    }
    if(temp == NULL)
        return 0;
    *e = temp->data;
    temp->prior->next = temp->next;
    if(temp->next != NULL)
        temp->next->prior = temp->prior;
    free(temp);
    return 1;
}
#endif /* second_section_dlinklist_h */
