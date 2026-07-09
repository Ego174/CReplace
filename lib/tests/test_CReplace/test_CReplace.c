/*
test_CReplace.c - модуль проверки библиотеки CReplace.h.

Хаиров Егор Вадимович
МК-101
*/

#include "unity.h"

#include "CReplace.h"
#include <stdio.h>

void setUp(void) {
    // Вызывается перед каждым тестом (можно оставить пустым)
}

void tearDown(void) {
    // Вызывается после каждого теста (можно оставить пустым)
}

void test1(void) {
    FILE* input = fopen("test.txt", "r");
    FILE* output = fopen("output1.txt", "w");
    replace(input, output, "0x313233", "0x414243");
    fclose(input);
    fclose(output);
    FILE* read = fopen("output1.txt", "r");
    char must[13] = {'A', 'B', 'C', '\n', 'a', 's', 'd', '\0', '\n', 'z', 'x', 'c', '\n'};
    char res[13];
    fread(res, 1, 13, read);
    TEST_ASSERT(memcmp(must, res, 13) == 0);
    fclose(read);
}

void test2(void) {
    FILE* input = fopen("test.txt", "r");
    FILE* output = fopen("output2.txt", "w");
    replace(input, output, "0x313233", "0x414141414141414141414141414141414141414141414141414141414141");
    fclose(input);
    fclose(output);
    FILE* read = fopen("output2.txt", "r");
    char must[42] = {'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'B', 'C', '\n', 'a', 's', 'd', '\0', '\n', 'z', 'x', 'c', '\n'};
    char res[42];
    fread(res, 1, 42, read);
    TEST_ASSERT(memcmp(must, res, 42) == 0);
    fclose(read);
}

void test3(void) {
    FILE* input = fopen("test.txt", "r");
    FILE* output = fopen("output3.txt", "w");
    replace(input, output, "0x61736400", "0x313233");
    fclose(input);
    fclose(output);
    FILE* read = fopen("output3.txt", "r");
    char must[12] = {'1', '2', '3', '\n', '1', '2', '3', '\n', 'z', 'x', 'c', '\n'};
    char res[12];
    fread(res, 1, 12, read);
    TEST_ASSERT(memcmp(must, res, 12) == 0);
    fclose(read);
}

void test4(void) {
    FILE* input = fopen("test.txt", "r");
    FILE* output = fopen("output4.txt", "w");
    replace(input, output, "0x00", "0x0a");
    fclose(input);
    fclose(output);
    FILE* read = fopen("output4.txt", "r");
    char must[13] = {'A', 'B', 'C', '\n', 'a', 's', 'd', '\n', '\n', 'z', 'x', 'c', '\n'};
    char res[13];
    fread(res, 1, 13, read);
    TEST_ASSERT(memcmp(must, res, 13) == 0);
    fclose(read);
}

void test5(void) {
    FILE* input = fopen("test.txt", "r");
    FILE* output = fopen("output5.txt", "w");
    replace(input, output, "0x7a7863", "0x303030");
    fclose(input);
    fclose(output);
    FILE* read = fopen("output5.txt", "r");
    char must[13] = {'A', 'B', 'C', '\n', 'a', 's', 'd', '\0', '\n', '0', '0', '0', '\n'};
    char res[13];
    fread(res, 1, 13, read);
    TEST_ASSERT(memcmp(must, res, 13) == 0);
    fclose(read);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test1);
    RUN_TEST(test2);
    RUN_TEST(test3);
    RUN_TEST(test4);
    RUN_TEST(test5);
    return UNITY_END();
}