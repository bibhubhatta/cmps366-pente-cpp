#include <gtest/gtest.h>

// Test if the Google Test framework is working.
TEST(FrameworkTest, BasicAssertions)
{
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}