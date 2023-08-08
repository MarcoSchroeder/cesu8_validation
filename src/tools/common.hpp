#pragma once
#ifndef COMMON_HPP
#define COMMON_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<char> read_file_as_binary(std::string const& path)
{
    std::ifstream file(path, std::ios::in |std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open filepath: " + path);
    }

    std::vector<char> ret((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    if(file.fail()) {
        throw std::runtime_error("Failed to open filepath: " + path);
    }
    file.close();

    return ret;
}

#endif // #ifndef COMMON_HPP