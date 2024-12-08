#include <cstdint>
#include <string>
#include <vector>

#include <filesystem>
#include <fstream>

#include <algorithm>

#include "../utils.h"


#include <iostream>


std::vector<std::vector<int>> read_file(const std::filesystem::path &path)
{
    std::vector<std::vector<int>> values;

    std::ifstream input_file(path);

    std::string line;

    while (std::getline(input_file, line)) {

        if (line.ends_with('\n'))
        {
            line = line.substr(0, line.size() - 1);
        }

        auto data_vec = utils::string_split(line);

        std::vector<int> data;
        data.reserve(data_vec.size());

        for (const auto entry : data_vec) {
            data.push_back(std::stoi(entry));
        }

        values.push_back(data);
    }
    return values;
}

// struct descending_bound
// {
//     inline bool operator() (const uint64_t& lhs, const uint64_t& rhs)
//     {

//         return lhs > rhs and rhs <= (lhs - 3);
//     }
// };


// struct ascending_bound
// {
//     inline bool operator() (const uint64_t& lhs, const uint64_t& rhs)
//     {
//         return lhs < rhs and (lhs + 3) <= rhs;
//     }
// };

bool follows_descending_bound(const auto &vec, bool first_try=true) {

    for (size_t i = 0; i < std::size(vec) - 1; ++i) {
        if (!(vec.at(i) > vec.at(i + 1) and vec.at(i) - 3 <= vec.at(i + 1)))
        {
            if (first_try) {
                auto vec2 = vec;
                vec2.erase(vec2.begin() + i);
                return follows_descending_bound(vec2, false);
            }
            return false;
        }
    }
    return true;
}

bool follows_ascending_bound(const auto &vec, bool first_try=true) {

    for (size_t i = 0; i < std::size(vec) - 1; ++i) {
        if (!(vec.at(i) < vec.at(i + 1) and vec.at(i + 1) <= vec.at(i) + 3))
        {
            if (first_try) {
                auto vec2 = vec;
                vec2.erase(vec2.begin() + i);
                return follows_ascending_bound(vec2, false);
            }

            return false;
        }
    }
    return true;
}


bool is_safe(const auto& data)
{
    return follows_descending_bound(data) or follows_ascending_bound(data);
}




int main(int argc, char *argv[]) {

    if (argc == 2)
    {
        std::filesystem::path path = std::string(argv[1]);
        if (std::filesystem::exists(path) &&
            !std::filesystem::is_directory(path))
        {

            size_t count_valid = 0;
            auto data = read_file(path);

            for (const auto& entry : data) {
                if (is_safe(entry)) {
                    count_valid = count_valid + 1;
                }
            }

            std::cout << "Number of valids: " << std::to_string(count_valid) << "\n";

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
