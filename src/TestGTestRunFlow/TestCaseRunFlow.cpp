#include "RunFlowTestSuite.hpp"

TEST(TestNoFixture, NoName)
{
    std::cout << "TEST TestNoFixture" << std::endl;
    SUCCEED();
}

TEST_F(TestFixture1, NoName)
{
    std::cout << "TEST TestFixture1 NoName" << std::endl;
    SUCCEED();
}

TEST_F(TestFixture1, WithName)
{
    std::cout << "TEST TestFixture1 WithName" << std::endl;
    SUCCEED();
}

TEST_F(TestFixture2, NoName)
{
    std::cout << "TEST TestFixture2" << std::endl;
    SUCCEED();
}
