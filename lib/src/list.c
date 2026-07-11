/*
list.c - реализация двусвязного списка.

Хаиров Егор Вадимович
МК-101
*/

#include "list.h"

// Создание списка
dList* createList(size_t matches) {

    // Выделение памяти под список
    dList* list = (dList*)malloc(sizeof(dList));
    if(!list) {
        printf("Не удалось выделить память под список!\n");
        exit(1);
    }

    // Выделение памяти под узел
    listNode* node = (listNode*)malloc(sizeof(listNode));
    if(!node) {
        printf("Не удалось выделить память под узел списка!\n");
        exit(1);
    }

    node->next = NULL;
    node->prev = NULL;
    node->matches = matches;
    list->head = node;
    list->tail = node;
    return list;

}

// Добавление элемента в список
void appendList(dList* list, size_t matches) {

    // Выделение памяти под новый узел
    listNode* node = (listNode*)malloc(sizeof(listNode));
    if(!node) {
        printf("Не удалось выделить память под новый узел!\n");
        exit(1);
    }
    node->matches = matches;
    node->next = NULL;

    // Добавление в пустой список
    if(!list->head) {
        node->prev = NULL;
        list->head = node;
        list->tail = node;
    }

    // Добавление в непустой список
    else {
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
    }

}

// Удаление узла по адресу
void popList(dList* list, listNode* search) {

    if(!list || !search) {
        printf("Неверный вызов popList()!\n");
        exit(1);
    }

    // Список из одного элемента
    if(list->head == list->tail) {
        list->head = NULL;
        list->tail = NULL;
        free(search);
        return;
    }

    // Удаление первого элемента
    if(search == list->head) {
        list->head = list->head->next;
        list->head->prev = NULL;
        free(search);
        return;
    }

    // Удаление последнего элемента
    if(search == list->tail) {
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        free(search);
        return;
    }

    search->prev->next = search->next;
    search->next->prev = search->prev;
    free(search);

}

// Очистка списка
void freeList(dList* list) {

    if(!list->head) return;

    while(list->head != list->tail) {
        list->tail = list->tail->prev;
        free(list->tail->next);
    }
    free(list->head);

    list->head = NULL;
    list->tail = NULL;

}