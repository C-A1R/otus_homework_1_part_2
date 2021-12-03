#include "IpFilter.h"

#include <iostream>


// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]

int main()
{
    try
    {
        IpFilter filter;
        for (std::string line; std::getline(std::cin, line);)
        {
            if (line.empty())
            {
                break;
            }
            filter << line;
        }
        filter.doFilter();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}