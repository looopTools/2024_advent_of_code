#include <cstdint>
#include <fstream>
#include <string>
#include <filesystem>
#include <algorithm>
#include <cassert>
#include <map>

#include <iostream>

void read_file(std::filesystem::path input_path, std::vector<uint64_t>& lhs,
               std::vector<uint64_t>& rhs, const std::string delimter = "   ")
{
    std::ifstream input_file(input_path);

    uint64_t lhs_value, rhs_value;

    while (input_file >> lhs_value >> rhs_value)
    {
        lhs.push_back(lhs_value);
        rhs.push_back(rhs_value);
    }

    std::sort(lhs.begin(), lhs.end());
    std::sort(rhs.begin(), rhs.end());
}


uint64_t compute_total_distance(const std::vector<uint64_t>& lhs,
                    const std::vector<uint64_t>& rhs)
{
    uint64_t total_distance = 0;
    for (size_t i = 0; i < lhs.size(); ++i)
    {
        if (lhs.at(i) <= rhs.at(i))
        {
            total_distance = total_distance + (rhs.at(i) - lhs.at(i));
        }
        else
        {
            total_distance = total_distance + (lhs.at(i) - rhs.at(i));
        }
    }
    return total_distance;
}

uint64_t compute_similarity_score(const std::vector<uint64_t> &lhs,
                                  const std::vector<uint64_t> &rhs)
{
    std::map<uint64_t, uint64_t> similarities;

    size_t i = 0;
    size_t j = 0;

    std::map<uint64_t, uint64_t> cache;

    uint64_t similarity_score = 0;

    for (const auto value : lhs)
    {
        if (!cache.contains(value))
        {
            cache[value] = std::count(rhs.begin(), rhs.end(), value);
        }

        similarity_score = similarity_score + (value * cache[value]);
    }

    return similarity_score;
}


int main(int argc, char *argv[]) {

    if (argc == 2)
    {
        std::filesystem::path path = std::string(argv[1]);
        if (std::filesystem::exists(path) &&
            !std::filesystem::is_directory(path))
        {
            std::vector<uint64_t> lhs;
            std::vector<uint64_t> rhs;

            read_file(path, lhs, rhs);

            assert(lhs.size() == rhs.size());
            std::cout << "Total Distance: " << std::to_string(compute_total_distance(lhs, rhs)) << "\n";
            std::cout << "Compute Similarity Score: " << std::to_string(compute_similarity_score(lhs, rhs)) << "\n";
        }
        else
        {
            return -1;
        }

    }
    else
    {
        return -1;
    }
    return 0;
}
