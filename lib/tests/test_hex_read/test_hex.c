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

int main(void) {
    UNITY_BEGIN();
    TEST_ASSERT_EQUAL_INT(0x61, htoc("61"));
    TEST_ASSERT_EQUAL_INT(0x00, htoc("00"));
    TEST_ASSERT_EQUAL_INT(0x0a, htoc("0a"));
    TEST_ASSERT_EQUAL_INT(0xa1, htoc("A1"));
    TEST_ASSERT_EQUAL_INT(0xaa, htoc("aA"));
    return UNITY_END();
}