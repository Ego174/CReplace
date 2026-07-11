/*
CReplace.c - главный модуль библиотеки. 

Хаиров Егор Вадимович
МК-101
*/

#include "CReplace.h"
#include "hex.h"
#include "list.h"

// Обработка буфера
#define checkBuf() \
for(size_t i = 0; i < bytesRead; ++i) { \
    if(buf[i] == searchS[0]) appendList(matchesList, 0); \
    listNode* cur = matchesList->head; \
    while(cur) { \
        if(buf[i] == searchS[cur->matches]) { \
            if(++(cur->matches) == searchLen) { \
                fwrite(replaceS, 1, replaceLen, output); \
                clearList(matchesList); \
                break; \
            } \
        } \
        else if(cur != matchesList->head) popList(matchesList, cur); \
        else { \
            if(cur->next) fwrite(searchS, 1, cur->matches - cur->next->matches, output); \
            else { \
                fwrite(searchS, 1, cur->matches, output); \
                fwrite(&buf[i], 1, 1, output); \
            } \
            popList(matchesList, cur); \
        } \
        cur = cur->next; \
    } \
}

// Заменяет вхождения одной последовательности байт на другую и записывает результат в выходной файл.
void replace(FILE* input, FILE* output, char* search, char* replace) {

    char buf[N];
    size_t bytesRead, matches = 0, searchLen = strlen(search) / 2 - 1, replaceLen = strlen(replace) / 2 - 1;

    // Запись искомой последовательности байт
    char* searchS = (char*)malloc(searchLen);
    if(!searchS) {
        printf("Не удалось создать буфер для искомой последовательности!\n");
        exit(1);
    }
    for(size_t i = 1; i <= searchLen; ++i) *(searchS + i - 1) = htoc(search + 2 * i);

    // Запись последовательности байт для замены
    char* replaceS = (char*)malloc(replaceLen);
    if(!replaceS) {
        printf("Не удалось создать буфер для последовательности замены!\n");
        exit(1);
    }
    for(size_t i = 1; i <= replaceLen; ++i) *(replaceS + i - 1) = htoc(replace + 2 * i);

    // Чтение файла в буфер, обработка буфера пока файл не закончится
    dList* matchesList = createList();
    while((bytesRead = fread(buf, 1, N, input)) == N) {
        checkBuf()
    }
    checkBuf()

    // Вывод остатков совпавших байтов
    if(matchesList->head) fwrite(searchS, 1, matchesList->head->matches, output);

    // Очистка выделенной памяти
    clearList(matchesList);
    free(matchesList);
    free(searchS);
    free(replaceS);

    return;

}