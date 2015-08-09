#ifndef __RUN_FLOW_ENVIRONMENT_HPP_20150809__
#define __RUN_FLOW_ENVIRONMENT_HPP_20150809__
#include <gtest/gtest.h>

class RunFlowEnvironment : public testing::Environment
{
public:
    RunFlowEnvironment()
    {
        std::cout << "Environment construct entered..." << std::endl;
    }

    ~RunFlowEnvironment()
    {
        std::cout << "Environment destruct leaving..." << std::endl;
    }

    void SetUp()
    {
        std::cout << "Environment SetUp entered..." << std::endl;
    }

    void TearDown()
    {
        std::cout << "Environment TearDown leaving..." << std::endl;
    }
};

#endif
