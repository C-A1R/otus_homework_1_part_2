#include "IpStruct.h"

#include <vector>
#include <string>
#include <functional>


class IpFilter
{
    std::vector<IpStruct> ip_pool;

public:
    IpFilter() = default;

    void doFilter();
    IpFilter operator << (const std::string &line);
    inline size_t ipCount() const { return ip_pool.size(); }

private:
    std::vector<std::string> split(const std::string &str, const char d);

    template<typename Iterator>
    void ip_print_if(Iterator begin, Iterator end, std::function<bool(const IpStruct&)> func)
    {
        if (!func)
        {
            return;
        }
        for (auto iter = begin; iter != end; ++iter)
        {
            auto ip = static_cast<IpStruct>(*iter);
            if (func(ip))
            {
                ip.print();
            }
        }
    }
};
