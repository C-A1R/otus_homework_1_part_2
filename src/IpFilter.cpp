// 
#include "IpFilter.h"

#include <iostream>
#include <algorithm>


std::vector<std::string> IpFilter::split(const std::string &str, const char d)
{
    std::vector<std::string> result;
    if (str.empty())
    {
        return result;
    }

    result.reserve(IpStruct::ipVersion);

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos)
    {
        result.emplace_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    result.emplace_back(str.substr(start));

    return result;
}

IpFilter IpFilter::operator << (const std::string &line)
{
    if (line.empty())
    {
        return *this;
    }
    std::vector<std::string> v = split(line, '\t');
    auto bytesVector = split(v.at(0), '.');
    IpStruct ip(bytesVector);
    if (ip.isValid())
    {
        ip_pool.push_back(ip);
    }
    return *this;
}

void IpFilter::doFilter()
{
    if (ip_pool.empty())
    {
        return;
    }

    // reverse lexicographically sort
    std::sort(ip_pool.begin(), ip_pool.end(), [](IpStruct &first, IpStruct &second) -> bool
    {
        return first > second;
    });

    // print sorted
    for (const auto &ip : ip_pool)
    {
        ip.print();
    }

    // doFilter by first byte
    ip_print_if(ip_pool.begin(), ip_pool.end(), [](const IpStruct &ip) -> bool
    {
        return ip.getByte(0) == 1;
    });


    // doFilter by first and second bytes
    ip_print_if(ip_pool.begin(), ip_pool.end(), [](const IpStruct &ip) -> bool
    {
        return ip.getByte(0) == 46 && ip.getByte(1) == 70;
    });

    // doFilter by any byte
    ip_print_if(ip_pool.begin(), ip_pool.end(), [](const IpStruct &ip) -> bool
    {
        return ip.getByte(0) == 46
            || ip.getByte(1) == 46
            || ip.getByte(2) == 46
            || ip.getByte(3) == 46;
    });
}