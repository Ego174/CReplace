/*
hex.c - модуль для чтения hex строк.

Хаиров Егор Вадимович
МК-101
*/

#include "hex.h"

// Перевод hex-байта записанного в строке в char
char htoc(char* hex) {

    char ret = 0, c0 = hex[0], c1 = hex[1];

    if(c1 < 0x41) ret += c1 - 0x30;
    else if(c1 < 0x61) ret += c1 - 0x37;
    else ret += c1 - 0x57;

    if(c0 < 0x41) ret += (c0 - 0x30) * 16;
    else if(c0 < 0x61) ret += (c0 - 0x37) * 16;
    else ret += (c0 - 0x57) * 16;

    return ret;

}