#include "../util.h"

#include <map>

namespace {

const std::map<std::string_view, size_t> num_map {
    { "one", 1 },
    { "two", 2 },
    { "three", 3 },
    { "four", 4 },
    { "five", 5 },
    { "six", 6 },
    { "seven", 7 },
    { "eight", 8 },
    { "nine", 9 }
};

size_t extract_line_with_digits(const std::string_view line)
{
    if (line.empty())
        return 0;

    const auto first = std::ranges::find_if(line, &quxflux::is_digit);
    const auto last = std::ranges::find_if(line | std::views::reverse, &quxflux::is_digit);

    return std::stoi(std::string { *first }) * 10 + std::stoi(std::string { *last });
}

size_t process_input(const auto& line_extract)
{
    auto line_nums = QUXFLUX_GET_INPUT() | std::views::split('\n') | std::views::transform(quxflux::as_string_view) | std::views::transform(line_extract);
    return std::ranges::fold_left(line_nums, size_t { 0 }, std::plus {});
}

size_t part_1()
{
    return process_input(extract_line_with_digits);
}

size_t extract_line_with_digits_and_words(const std::string_view line)
{
    if (line.empty())
        return 0;

    const auto reversed_line = line | std::views::reverse;

    std::map<size_t, size_t> pos_and_values;

    const auto first_digit = std::ranges::find_if(line, &quxflux::is_digit);
    if (first_digit != line.end())
        pos_and_values[std::distance(line.begin(), first_digit)] = std::stoi(std::string { *first_digit });

    const auto last_digit = std::ranges::find_if(reversed_line, &quxflux::is_digit);
    if (last_digit != reversed_line.end())
        pos_and_values[line.size() - std::distance(reversed_line.begin(), last_digit)] = std::stoi(std::string { *last_digit });

    for (size_t i = 0; i < line.size(); ++i) {
        for (auto& [key, value] : num_map) {
            if (line.substr(i, key.size()) == key) {
                pos_and_values[i] = value;
                break;
            }
        }
    }

    return pos_and_values.begin()->second * 10 + pos_and_values.rbegin()->second;
}

size_t part_2()
{
    return process_input(extract_line_with_digits_and_words);
}
} // namespace

int main()
{
    std::cout << part_1() << std::endl;
    std::cout << part_2() << std::endl;

    return 0;
}
