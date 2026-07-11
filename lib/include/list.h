/*
list.h - заголовочный файл модуля list.c.

Хаиров Егор Вадимович
МК-101
*/

#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct listNode {
    struct listNode* next;
    struct listNode* prev;
    size_t matches;
} listNode;

typedef struct dList {
    listNode* head;
    listNode* tail;
} dList;

dList* createList(size_t matches);
void appendList(dList* list, size_t matches);
void popList(dList* list, listNode* search);
void freeList(dList* list);