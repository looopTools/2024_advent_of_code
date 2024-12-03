#include <cstdint>

#include <vector>

#include <filesystem>
#include <fstream>

#include <algorithm>

#include "../utils.h"


#include <iostream>


std::vector<std::vector<uint64_t>> read_file(const std::filesystem::path &path)
{
    std::vector<std::vector<uint64_t>> values;

    std::ifstream input_file(path);

    std::string line;

    while (std::getline(input_file, line)) {

        if (line.ends_with('\n'))
        {
            line = line.substr(0, line.size() - 1);
        }

        auto data_vec = utils::string_split(line);

        std::vector<uint64_t> data;
        data.reserve(data_vec.size());

        for (const auto entry : data_vec) {
            data.push_back(std::stoull(entry));
        }

        values.push_back(data);
    }
    return values;
}

struct descending_bound
{
    inline bool operator() (const uint64_t& lhs, const uint64_t& rhs)
    {

        return lhs > rhs and rhs <= (lhs - 3);
    }
};


struct ascending_bound
{
    inline bool operator() (const uint64_t& lhs, const uint64_t& rhs)
    {
        return lhs < rhs and (lhs + 3) <= rhs;
    }
};

bool is_valid(const std::vector<uint64_t> &data)
{
    auto value = std::is_sorted(data.begin(), data.end(), descending_bound());
    auto value2 = std::is_sorted(data.begin(), data.end(), ascending_bound());
    std::cout << "value: " << (value ? "True" : "False") << "\n";
    std::cout << "value two: " << (value ? "True" : "False") << "\n";
    return value;
}




int main(int argc, char *argv[]) {

    if (argc == 2)
    {
        std::filesystem::path path = std::string(argv[1]);
        if (std::filesystem::exists(path) &&
            !std::filesystem::is_directory(path))
        {

            auto data = read_file(path);

            for (const auto& entry : data) {
                utils::print_numeric_vector(entry);
                std::cout << (is_valid(entry) ? "True" : "False") << "\n";
            }


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
