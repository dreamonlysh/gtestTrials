#ifndef __FEA_VAL_PATTERN_TEST_SUITE_HPP_20150823__
#define __FEA_VAL_PATTERN_TEST_SUITE_HPP_20150823__
#include <gtest/gtest.h>
#include "TestSource.hpp"

class TestValPattern 
    : public testing::Test
    , public testing::WithParamInterface<int32_t>
{
public:
    TestValPattern() {}
    virtual ~TestValPattern() {}
};

/**
 * 1.Range [2, 5), so three tests will got here
 * 2.One test with the same value unless how many times GetParam() called
 * 3.Third param is step which default to be 1
 */
class TestValPatternRange : public TestValPattern
{
public:
    TestValPatternRange() {}
    ~TestValPatternRange() {}
};
INSTANTIATE_TEST_CASE_P(TRange, TestValPatternRange, testing::Range(2, 5, 1));


class TestValPatternValues : public TestValPattern
{
public:
    TestValPatternValues() {}
    ~TestValPatternValues() {}
};
INSTANTIATE_TEST_CASE_P(TValues, TestValPatternValues, testing::Values(1, 10));


class TestValPatternValuesInContainer : public TestValPattern
{
public:
    TestValPatternValuesInContainer() {}
    ~TestValPatternValuesInContainer() {}
};
int32_t cContainer[] = {1, 10};
INSTANTIATE_TEST_CASE_P(TValuesInContainer, 
    TestValPatternValuesInContainer, testing::ValuesIn(cContainer));

/**
 * Range [begin(), begin() + 1), so only one test will run 
 */
class TestValPatternValuesInInterator : public TestValPattern
{
public:
    TestValPatternValuesInInterator() {}
    ~TestValPatternValuesInInterator() {}

    static void SetUpTestCase()
    {
    }
};

std::vector<int32_t>& getInt32Data()
{
    static std::vector<int32_t> cppContainer;
    if (cppContainer.empty())
    {
        cppContainer.push_back(1);
        cppContainer.push_back(2);
        cppContainer.push_back(3);
    }
    return cppContainer;
}
INSTANTIATE_TEST_CASE_P(TValuesInInterator, 
    TestValPatternValuesInInterator, 
    testing::ValuesIn(getInt32Data().begin(), getInt32Data().begin() + 1));

#endif
