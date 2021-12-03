#ifndef IPSTRUCT_H
#define IPSTRUCT_H

#include <vector>
#include <string>

class IpStruct
{
    std::vector<int> bytes;

public:
    static const int ipVersion {4};

    explicit IpStruct(const std::vector<std::string> &v);
    int getByte(const int index) const;
    void print() const;
    bool isValid() const;

    friend bool operator < (const IpStruct &left, const IpStruct &right)
    {
        return left.bytes < right.bytes;
    }
    friend bool operator > (const IpStruct &left, const IpStruct &right)
    {
        return !(left.bytes < right.bytes);
    }
};

#endif //IPSTRUCT_H