/*
CReplace.c - главный модуль библиотеки. 

Хаиров Егор Вадимович
МК-101
*/

#include "CReplace.h"
#include "hex.h"

// Обработка буфера
#define checkBuf() \
for(size_t i = 0; i < bytesRead; ++i) { \
    if(buf[i] == searchS[matches]) ++matches; \
    else { \
        fwrite(searchS, 1, matches, output); \
        fwrite(buf + i, 1, 1, output); \
        matches = 0; \
    } \
    if(matches == searchLen) { \
        fwrite(replaceS, 1, replaceLen, output); \
        matches = 0; \
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
    if(!searchS) {
        printf("Не удалось создать буфер для последовательности замены!\n");
        exit(1);
    }
    for(size_t i = 1; i <= replaceLen; ++i) *(replaceS + i - 1) = htoc(replace + 2 * i);

    while((bytesRead = fread(buf, 1, N, input)) == N) {
        checkBuf()
    }
    checkBuf()

    fflush(output);
    free(searchS);
    free(replaceS);

    return;

}