/*
test_app.c - модуль проверки программы. 

Хаиров Егор Вадимович
МК-101
*/

#include "unity.h"

#include "CReplace.h"

void setUp(void) {
    // Вызывается перед каждым тестом (можно оставить пустым)
}

void tearDown(void) {
    // Вызывается после каждого теста (можно оставить пустым)
}

void test1(void) {
    FILE* input = fopen("test.txt", "r");
    FILE* output = fopen("output1.txt", "w");
    replace(input, output, "0x414141", "0x30");
    fclose(input);
    fclose(output);
    FILE* read = fopen("output1.txt", "r");
    char must[35] = "000000000000000000000000000000000";
    char res[35];
    fread(res, 1, 35, read);
    TEST_ASSERT_TRUE(memcmp(must, res, 35) == 0);
    fclose(read);
}

void test2(void) {
    FILE* input = fopen("test.txt", "r");
    FILE* output = fopen("output2.txt", "w");
    replace(input, output, "0x42", "0x30");
    fclose(input);
    fclose(output);
    FILE* read = fopen("output2.txt", "r");
    char must[100] = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
    char res[100];
    fread(res, 1, 100, read);
    TEST_ASSERT_TRUE(memcmp(must, res, 100) == 0);
    fclose(read);
}

void test3(void) {
    FILE* input = fopen("test.txt", "r");
    FILE* output = fopen("output3.txt", "w");
    replace(input, output, "0x00", "0x10");
    fclose(input);
    fclose(output);
    FILE* read = fopen("output3.txt", "r");
    char must[100] = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n";
    char res[100];
    fread(res, 1, 100, read);
    TEST_ASSERT_TRUE(memcmp(must, res, 100) == 0);
    fclose(read);
}

int main(void) {
    UNITY_BEGIN();
    FILE* test = fopen("test.txt", "w");
    fwrite("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", 1, 100, test);
    fflush(test);
    fclose(test);
    RUN_TEST(test1);
    RUN_TEST(test2);
    RUN_TEST(test3);
    return UNITY_END();
}