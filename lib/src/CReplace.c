/*
CReplace.c - главный модуль библиотеки. 

Хаиров Егор Вадимович
МК-101
*/

#include "CReplace.h"

void replace(FILE *input, FILE *output, char* search, char* replace) {

    char buf[N];
    size_t ind = 0, search_len = strlen(search) / 2 - 1, replace_len = strlen(replace) / 2 - 1;

    char* searchS = (char*)malloc(search_len);
    for(int i = 1; i <= search_len; ++i) sscanf(search + 2 * i, "%2s", searchS + i - 1);

    char* replaceS = (char*)malloc(replace_len);
    for(int i = 1; i <= replace_len; ++i) sscanf(replace + 2 * i, "%2s", replaceS + i - 1);

    printf("Arguments: %s %s\n", searchS, replaceS);

    fflush(output);
    free(searchS);
    free(replaceS);

    return;

}