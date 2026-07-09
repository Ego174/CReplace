/*
CReplace.c - главный модуль библиотеки. 

Хаиров Егор Вадимович
МК-101
*/

#include "CReplace.h"

void replace(FILE *input, FILE *output, char search[], char replace[]) {

    char buf[N];

    while(fwrite(buf, 1, fread(buf, 1, N, input), output) == N);

    fflush(output);

}