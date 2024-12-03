#include <algorithm>

#include <iostream>
#include <cstdint>
// #include <vector>

struct descending_bound
{
    inline bool operator() (const uint64_t& lhs, const uint64_t& rhs)
    {
        return lhs != rhs and lhs > rhs;
   }
};


struct ascending_bound
{
    inline bool operator() (const uint64_t& lhs, const uint64_t& rhs)
    {
        return lhs != rhs and lhs < rhs;
    }
};

bool is_valid(const std::vector<uint64_t> &data)
{
    return std::is_sorted(data.begin(), data.end(), descending_bound()) or std::is_sorted(data.begin(), data.end(), ascending_bound());
}



int main(void)
{
    const std::vector<uint64_t> data = {8, 6, 4, 4, 1};
    std::cout << "Is valid: " << (is_valid(data) ? "True" : "False")  << "\n";
}
