#define BOOST_TEST_MODULE test_IpFilter

#include "IpFilter.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_IpFilter)

BOOST_AUTO_TEST_CASE(test_insert_ip_empty)
{
    IpFilter ipFiter;
    ipFiter << "";
    BOOST_CHECK(ipFiter.ipCount() == 0);
}

BOOST_AUTO_TEST_CASE(test_insert_ip_not_valid)
{
    IpFilter ipFiter;
    ipFiter << "0"
            << "0.0"
            << "0.0.0"
            << "-1.0.0.0"
            << "256.0.0.0"
            << "0.0.0.0.0"
            << "1346dfsf515fd";
    BOOST_CHECK(ipFiter.ipCount() == 0);
}

BOOST_AUTO_TEST_SUITE_END() 