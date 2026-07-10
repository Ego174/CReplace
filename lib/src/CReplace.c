/*
CReplace.c - главный модуль библиотеки. 

Хаиров Егор Вадимович
МК-101
*/

#include "CReplace.h"
#include "hex.h"

// Запись буфера в выходной файл
#define writeBuf() \
fwrite(buf, 1, ind, output); \
ind = 0

// Запись замены в выходной файл
#define writeReplace() \
fwrite(replaceS, 1, replace_len, output); \
ind = 0

// Заменяет вхождения одной последовательности байт на другую и записывает результат в выходной файл.
void replace(FILE* input, FILE* output, char* search, char* replace) {

    char buf[N];
    size_t ind = 0, search_len = strlen(search) / 2 - 1, replace_len = strlen(replace) / 2 - 1;

    if(search_len > N) {
        printf("Искомая последовательность больше буфера!\n");
        exit(1);
    }

    // Запись искомой последовательности байт
    char* searchS = (char*)malloc(search_len);
    if(!searchS) {
        printf("Не удалось создать буфер для искомой последовательности!\n");
        exit(1);
    }
    for(int i = 1; i <= search_len; ++i) *(searchS + i - 1) = htoc(search + 2 * i);

    // Запись последовательности байт для замены
    char* replaceS = (char*)malloc(replace_len);
    if(!searchS) {
        printf("Не удалось создать буфер для последовательности замены!\n");
        exit(1);
    }
    for(int i = 1; i <= replace_len; ++i) *(replaceS + i - 1) = htoc(replace + 2 * i);

    while(1) {
        buf[ind] = getc(input);
        if(buf[ind] == EOF) {
            writeBuf();
            break;
        } else if(buf[ind] != searchS[ind++]) {
            writeBuf();
        } else if(ind == search_len) {
            writeReplace();
        }
    }

    fflush(output);
    free(searchS);
    free(replaceS);

    return;

}