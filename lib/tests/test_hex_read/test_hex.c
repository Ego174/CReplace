/*
test_hex.c - модуль проверки библиотеки hex.h. 

Хаиров Егор Вадимович
МК-101
*/

#include "unity.h"

#include "hex.h"

void setUp(void) {
    // Вызывается перед каждым тестом (можно оставить пустым)
}

void tearDown(void) {
    // Вызывается после каждого теста (можно оставить пустым)
}

void test1(void) {
    TEST_ASSERT_EQUAL_INT(0x61, htoc("61"));
}

void test2(void) {
    TEST_ASSERT_EQUAL_INT(0x00, htoc("00"));
}

void test3(void) {
    TEST_ASSERT_EQUAL_INT(0x0a, htoc("0a"));
}

void test4(void) {
    TEST_ASSERT_EQUAL_INT(0xa1, htoc("a1"));
}

void test5(void) {
    TEST_ASSERT_EQUAL_INT(0xaa, htoc("aa"));
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