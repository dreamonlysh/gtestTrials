#ifndef __TEST_SOURCE_HPP_20150823__
#define __TEST_SOURCE_HPP_20150823__
#include "stdint.h"

int32_t add(int32_t x, int32_t y)
{
    return x + y;
}

int32_t minus(int32_t x, int32_t y)
{
    return x - y;
}

template <typename T>
std::string join(const std::vector<T>& tVec, 
    const std::string& sep = ",")
{
    std::ostringstream oss;
    std::vector<T>::const_iterator iter = tVec.begin();
    while (!tVec.empty())
    {
        oss << *iter;
        if (++iter == tVec.end()) break;
        oss << sep;
    }
    return oss.str();
}

#endif
