#pragma once

#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

namespace quxflux
{
  inline std::string read_file(const std::filesystem::path& path)
  {
    std::ifstream file(path);
    std::ostringstream oss;
    std::ranges::copy(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), std::ostreambuf_iterator<char>(oss));
    return oss.str();
  }
}