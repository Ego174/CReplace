/*
CReplace.h - заголовочный файл модуля CReplace.c.

Хаиров Егор Вадимович
МК-101
*/

#pragma once

#define N 10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void replace(FILE *input, FILE *output, char search[], char replace[]);