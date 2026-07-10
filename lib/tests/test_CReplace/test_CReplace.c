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

void test(char inputPath[], char outputPath[], char searchS[], char replaceS[], char must[], size_t resSize) {
    FILE* input = fopen(inputPath, "r");
    if(!input) {
        printf("Не удалось открыть входной файл!\n");
        TEST_ASSERT_TRUE(0);
        return;
    }
    FILE* output = fopen(outputPath, "w");
    if(!output) {
        printf("Не удалось открыть выходной файл!\n");
        fclose(input);
        TEST_ASSERT_TRUE(0);
        return;
    }
    replace(input, output, searchS, replaceS);
    fclose(input);
    fclose(output);
    FILE* read = fopen(outputPath, "r");
    if(!read) {
        printf("Не удалось открыть выходной файл после записи!\n");
        TEST_ASSERT_TRUE(0);
        return;
    }
    char* res = malloc(resSize);
    fread(res, 1, resSize, read);
    TEST_ASSERT_TRUE(memcmp(must, res, resSize) == 0);
    free(res);
    fclose(read);
}

void test1(void) {
    char must[13] = "ABC\nasd\0\nzxc\n";
    test("test.txt", "output1.txt", "0x313233", "0x414243", must, 13);
}

void test2(void) {
    char must[40] = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\nasd\0\nzxc\n";
    test("test.txt", "output2.txt", "0x313233", "0x414141414141414141414141414141414141414141414141414141414141", must, 40);
}

void test3(void) {
    char must[12] = "123\n123\nzxc\n";
    test("test.txt", "output3.txt", "0x61736400", "0x313233", must, 12);
}

void test4(void) {
    char must[13] = "123\nasd\n\nzxc\n";
    test("test.txt", "output4.txt", "0x00", "0x0a", must, 13);
}

void test5(void) {
    char must[13] = "123\nasd\0\n000\n";
    test("test.txt", "output5.txt", "0x7a7863", "0x303030", must, 13);
}

int main(void) {
    UNITY_BEGIN();
    FILE* testFile = fopen("test.txt", "w");
    fwrite("123\nasd\0\nzxc\n", 1, 13, testFile);
    fflush(testFile);
    fclose(testFile);
    RUN_TEST(test1);
    RUN_TEST(test2);
    RUN_TEST(test3);
    RUN_TEST(test4);
    RUN_TEST(test5);
    return UNITY_END();
}