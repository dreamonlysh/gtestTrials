#include "FeaValPatternTestSuite.hpp"

TEST_P(TestValPatternRange, TestByRange)
{
    ASSERT_EQ(0, minus(GetParam(), GetParam()));
    ASSERT_EQ(2*GetParam(), add(GetParam(), GetParam()));
}

TEST_P(TestValPatternValues, TestByValues)
{
    ASSERT_EQ(0, minus(GetParam(), GetParam()));
    ASSERT_EQ(2*GetParam(), add(GetParam(), GetParam()));
}

TEST_P(TestValPatternValuesInContainer, TestByValuesInContainer)
{
    ASSERT_EQ(0, minus(GetParam(), GetParam()));
    ASSERT_EQ(2*GetParam(), add(GetParam(), GetParam()));
}

TEST_P(TestValPatternValuesInInterator, TestByValuesInInterator)
{
    ASSERT_EQ(0, minus(GetParam(), GetParam()));
    ASSERT_EQ(2*GetParam(), add(GetParam(), GetParam()));
}

