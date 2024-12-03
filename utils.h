#pragma once

#include <vector>
#include <string>
#include <cstddef> // size_t

#include <iostream>
// Stolen from: https://stackoverflow.com/a/14266139

namespace utils
{
std::vector<std::string> string_split(std::string& str,
                                      const std::string& delimiter = " ") {

    std::vector<std::string> tokens;

    size_t pos = 0;
    std::string current_token;

    // the npos is no position and
    // happens when position is after the end of string
    while ((pos = str.find(delimiter)) != std::string::npos)
    {
        current_token = str.substr(0, pos); // pos is start of token
        tokens.push_back(current_token);
        str.erase(0, pos + delimiter.length()); // we remove token from str
    }
    tokens.push_back(str); // we remember to push the remaning token in the string
    return tokens;
}

template<typename T> void print_numeric_vector(const std::vector<T>& data) {

    std::cout << "[";

    for (size_t i = 0; i < data.size() - 1; ++i)
    {
        std::cout << std::to_string(data.at(i)) << ", ";
    }

    std::cout << std::to_string(data.at(data.size() - 1)) << "]\n";


}
}
