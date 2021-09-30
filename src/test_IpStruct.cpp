#define BOOST_TEST_MODULE test_IpStruct

#include "IpStruct.h"

#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(test_IpStruct)

BOOST_AUTO_TEST_CASE(test_valid_empty)
{
    std::vector<std::string> v;
    IpStruct emptyIp(v);
    BOOST_CHECK(emptyIp.isValid() == false);
}

BOOST_AUTO_TEST_SUITE_END() 