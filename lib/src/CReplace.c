/*
CReplace.c - главный модуль библиотеки. 

Хаиров Егор Вадимович
МК-101
*/

#include "CReplace.h"

void replace(FILE *input, FILE *output, char search[], char replace[]) {

    char buf[N];

    while(fread(buf, 1, N, input) == N) {
        fwrite(buf, 1, N, output);
    }

    fwrite(buf, 1, strlen(buf), output);

    fflush(output);

}