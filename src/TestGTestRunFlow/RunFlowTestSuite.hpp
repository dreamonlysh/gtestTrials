#ifndef __RUN_FLOW_TEST_SUITE_HPP__
#define __RUN_FLOW_TEST_SUITE_HPP__
#include <gtest/gtest.h>
#include "RunFlowEnvironment.hpp"

class TestFixture1 : public testing::Test
{
public:
    TestFixture1()
    {
        std::cout << "TestFixture1 construct entered..." << std::endl;
    }

    ~TestFixture1()
    {
        std::cout << "TestFixture1 destruct leaving..." << std::endl;
    }

    static void SetUpTestCase()
    {
        std::cout << "TestFixture1 SetUpTestCase entered..." << std::endl;
    }

    static void TearDownTestCase()
    {
        std::cout << "TestFixture1 TearDownTestCase leaving..." << std::endl;
    }

    void SetUp()
    {
        std::cout << "TestFixture1 SetUp entered..." << std::endl;
    }

    void TearDown()
    {
        std::cout << "TestFixture1 TearDown leaving..." << std::endl;
    }
};

class TestFixture2 : public testing::Test
{
public:
    TestFixture2()
    {
        std::cout << "TestFixture2 construct entered..." << std::endl;
    }

    ~TestFixture2()
    {
        std::cout << "TestFixture2 destruct leaving..." << std::endl;
    }

    static void SetUpTestCase()
    {
        std::cout << "TestFixture2 SetUpTestCase entered..." << std::endl;
    }

    static void TearDownTestCase()
    {
        std::cout << "TestFixture2 TearDownTestCase leaving..." << std::endl;
    }

    void SetUp()
    {
        std::cout << "TestFixture2 SetUp entered..." << std::endl;
    }

    void TearDown()
    {
        std::cout << "TestFixture2 TearDown leaving..." << std::endl;
    }
};

#endif
