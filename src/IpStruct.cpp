#include "IpStruct.h"

#include <iostream>

IpStruct::IpStruct(const std::vector<std::string> &v)
{
    if (v.size() != ipVersion)
    {
        return;
    }

    bytes.reserve(ipVersion);
    for (const auto &byte_str : v)
    {
        int byte = std::stoi(byte_str);
        if (byte < 0 || byte > 255)
        {
            bytes.clear();
            break;
        }
        bytes.emplace_back(byte);
    }
}

int IpStruct::getByte(const int index) const
{
    if (index > 0 && index <= ipVersion)
    {
        return bytes[index];
    }
    return -1;
}

void IpStruct::print() const
{
    for (auto iter = bytes.cbegin(); iter != bytes.cend(); ++iter)
    {
        if (iter != bytes.cbegin())
        {
            std::cout << '.';
        }
        std::cout << *iter;
    }
    std::cout << std::endl;
}

bool IpStruct::isValid() const
{
    return (!bytes.empty());
}