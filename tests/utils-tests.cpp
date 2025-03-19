#include<gtest/gtest.h>
#include "../include/utils.h"


/* Tests generating hamming window gives correct output */
TEST(UtilsTests, GenerateWindow) {
    int windowLen = 32;
    ASSERT_EQ(Utils::generateWindow(windowLen).size(), windowLen);
}

/* Call sinc with a zero and non-zero input*/
TEST(UtilsTests, Sinc) {
    ASSERT_EQ(Utils::sinc(0), 1.0);
    ASSERT_EQ(floor(Utils::sinc(1)), 0.0);
}

/* Ensure proper behavior of nextPowerOfTwo */

TEST(UtilsTests, NextPowerOfTwo) {
    ASSERT_EQ(Utils::nextPowerOfTwo(2), 2);
    ASSERT_EQ(floor(Utils::nextPowerOfTwo(3)), 4);
}

