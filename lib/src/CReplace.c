/*
CReplace.c - главный модуль библиотеки. 

Хаиров Егор Вадимович
МК-101
*/

#include "CReplace.h"
#include "hex.h"

// Обработка буфера
void checkBuf(unsigned char* buf, size_t bufLen, unsigned char* searchS, size_t searchLen, size_t* matches, FILE* output, unsigned char* replaceS, size_t replaceLen) {
    
    for(size_t i = 0; i < bufLen; ++i) {

        // Совпадение, прибавляем счетчки и выводим замену если последовательность полностью совпала
        if(buf[i] == searchS[*matches]) {
            if(++(*matches) == searchLen) {
                fwrite(replaceS, 1, replaceLen, output);
                *matches = 0;
            }
            continue;
        }
        
        // Несовпадение, ищем максимальную подстроку которая может оказаться искомой последовательностью
        if(*matches > 0) {
            size_t tmp = *matches;
            *matches = 0;
            for(size_t k = 1; k <= tmp; ++k) {
                fwrite(&searchS[k - 1], 1, 1, output);
                size_t cur = tmp - k;
                if(memcmp(searchS, searchS + k, cur) == 0 && buf[i] == searchS[cur]) {
                    *matches = cur + 1; // Подстрока найдена
                    break;
                }
            }
        }

        // Полное несовпадение
        if(*matches == 0) fwrite(&buf[i], 1, 1, output);

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
    for(size_t i = 1; i <= searchLen; ++i) searchS[i-1] = htoc(search + 2 * i);

    // Запись последовательности байт для замены
    char* replaceS = (char*)malloc(replaceLen);
    if(!replaceS) {
        printf("Failed allocating memory for bytes to replace with!\n");
        exit(1);
    }
    for(size_t i = 1; i <= replaceLen; ++i) replaceS[i-1] = htoc(replace + 2 * i);

    // Чтение файла в буфер, обработка буфера пока файл не закончится
    while((bytesRead = fread(buf, 1, N, input)) > 0)
        checkBuf(buf, bytesRead, searchS, searchLen, &matches, output, replaceS, replaceLen);

    // Вывод остатков совпавших байтов
    if(matches > 0) fwrite(searchS, 1, matches, output);

    // Очистка выделенной памяти
    free(searchS);
    free(replaceS);

    return;

}