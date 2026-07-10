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
    test("test.txt", "output1.txt", "0x414141", "0x30", "000000000000000000000000000000000", 34);
}

void test2(void) {
    test("test.txt", "output2.txt", "0x42", "0x30", "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", 100);
}

void test3(void) {
    test("test.txt", "output3.txt", "0x00", "0x0a", "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n", 100);
}

int main(void) {
    UNITY_BEGIN();
    FILE* testFile = fopen("test.txt", "w");
    fwrite("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", 1, 100, testFile);
    fflush(testFile);
    fclose(testFile);
    RUN_TEST(test1);
    RUN_TEST(test2);
    RUN_TEST(test3);
    return UNITY_END();
}