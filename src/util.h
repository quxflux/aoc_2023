#pragma once

#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

namespace quxflux {

inline bool is_digit(const char c) { return std::isdigit(c); }

inline std::string read_file(const std::filesystem::path& path)
{
    std::ifstream file(path);
    std::ostringstream oss;
    std::ranges::copy(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), std::ostreambuf_iterator<char>(oss));
    return oss.str();
}
constexpr auto as_string_view = [](const auto& str) { return std::string_view { str }; };
}

#define QUXFLUX_GET_INPUT() [] { const static auto str = quxflux::read_file(std::filesystem::path(__FILE__).parent_path() / "input.txt"); \
                                 return std::string_view{str}; }()