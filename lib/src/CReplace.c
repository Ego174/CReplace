/*
CReplace.c - главный модуль библиотеки. 

Хаиров Егор Вадимович
МК-101
*/

#include "CReplace.h"
#include "hex.h"

// Обработка буфера
void checkBuf(char* buf, size_t bufLen, char* searchS, size_t searchLen, size_t* matches, FILE* output, char* replaceS, size_t replaceLen, size_t pos) {
    for(size_t i = 0; i < bufLen; ++i) {
        if(buf[i] == searchS[*matches]) {
            if(++(*matches) == searchLen) {
                fwrite(replaceS, 1, replaceLen, output);
                *matches = 0;
            }
        } else {
            size_t tmp = *matches;
            *matches = 0;
            if(tmp > 1) checkBuf(searchS + pos + 1, tmp - 1, searchS, searchLen, matches, output, replaceS, replaceLen, pos + 1);
            if(pos != 0) break;
            
        }
    }
}

// Заменяет вхождения одной последовательности байт на другую и записывает результат в выходной файл
void replace(FILE* input, FILE* output, char* search, char* replace) {

    char buf[N];
    size_t bytesRead, matches = 0, searchLen = strlen(search) / 2 - 1, replaceLen = strlen(replace) / 2 - 1;

    // Запись искомой последовательности байт
    char* searchS = (char*)malloc(searchLen);
    if(!searchS) {
        printf("Failed allocating memory for bytes to replace!\n");
        exit(1);
    }
    for(size_t i = 1; i <= searchLen; ++i) *(searchS + i - 1) = htoc(search + 2 * i);

    // Запись последовательности байт для замены
    char* replaceS = (char*)malloc(replaceLen);
    if(!replaceS) {
        printf("Failed allocating memory for bytes to replace with!\n");
        exit(1);
    }
    for(size_t i = 1; i <= replaceLen; ++i) *(replaceS + i - 1) = htoc(replace + 2 * i);

    // Чтение файла в буфер, обработка буфера пока файл не закончится
    while((bytesRead = fread(buf, 1, N, input)) > 0) {
        for(size_t i = 0; i < bytesRead; ++i ) checkBuf();
    }

    // Вывод остатков совпавших байтов
    if(matches > 0) fwrite(searchS, 1, matches, output);

    // Очистка выделенной памяти
    free(searchS);
    free(replaceS);

    return;

}