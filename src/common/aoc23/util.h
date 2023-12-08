#pragma once

#include <algorithm>
#include <array>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

namespace quxflux {

constexpr bool is_digit(const char c) { return c >= '0' && c <= '9'; }
constexpr auto as_string_view = [](const std::constructible_from<std::string_view> auto& str) { return std::string_view { str }; };

inline std::string read_file(const std::filesystem::path& path)
{
    std::ifstream file(path);
    std::ostringstream oss;
    std::ranges::copy(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), std::ostreambuf_iterator<char>(oss));
    return oss.str();
}

}

#define QUXFLUX_GET_INPUT() [] { const static auto str = quxflux::read_file(std::filesystem::path(__FILE__).parent_path() / "input.txt"); \
                                 return std::string_view{str}; }()
