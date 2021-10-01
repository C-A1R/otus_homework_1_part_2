#define BOOST_TEST_MODULE test_IpStruct

#include "IpStruct.h"

#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(test_IpStruct)

BOOST_AUTO_TEST_CASE(test_valid_empty)
{
    IpStruct emptyIp(std::vector<std::string>(0));
    BOOST_CHECK(emptyIp.isValid() == false);
}

BOOST_AUTO_TEST_CASE(test_valid_bytes_count)
{
    bool result = false;
    for (int i = 1; i < IpStruct::ipVersion; ++i)
    {
        IpStruct ip(std::vector<std::string>(i, "0"));
        if (ip.isValid())
        {
            result = true;
            break;
        }
    }
    BOOST_CHECK(result == false);
}

BOOST_AUTO_TEST_CASE(test_valid_bytes)
{
    bool result = false;
    IpStruct ip(std::vector<std::string>(IpStruct::ipVersion, "-1"));
    result = ip.isValid();
    if (!result)
    {
        IpStruct _ip(std::vector<std::string>(IpStruct::ipVersion, "256"));
        result = _ip.isValid();
    }
    BOOST_CHECK(result == false);
}

BOOST_AUTO_TEST_CASE(test_getByte)
{
    auto test_func = [](const IpStruct &ip) -> int
    {
        int result = -1;
        result = ip.getByte(-1);
        if (result == -1)
        {
            result = ip.getByte(IpStruct::ipVersion + 1);
        }
        return result;
    };
    
    IpStruct ip(std::vector<std::string>(0));
    int test_result = test_func(ip);
    if (test_result == -1)
    {
        ip = IpStruct(std::vector<std::string>(IpStruct::ipVersion, "-1"));
        test_result = test_func(ip);
    }
    if (test_result == -1)
    {
        ip = IpStruct(std::vector<std::string>(IpStruct::ipVersion, "0"));
        test_result = test_func(ip);
    }
    if (test_result == -1)
    {
        ip = IpStruct(std::vector<std::string>(IpStruct::ipVersion, "256"));
        test_result = test_func(ip);
    }
    
    BOOST_CHECK(test_result == -1);
}

BOOST_AUTO_TEST_SUITE_END() 