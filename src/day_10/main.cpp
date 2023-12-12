#include "map.h"
#include <aoc23/util.h>

#include <cassert>
#include <set>
#include <utility>

namespace quxflux::aoc {
namespace {

    map get_input()
    {
        constexpr auto map_element = [](const char c) {
            constexpr auto map_values = std::to_array<std::pair<char, field>>({ //
                { '|', field::NS },
                { '-', field::WE },
                { 'L', field::NE },
                { 'J', field::NW },
                { '7', field::SW },
                { 'F', field::SE },
                { '.', field::none },
                { 'S', field::start } });

            return std::ranges::find(map_values, c, &std::pair<char, field>::first)->second;
        };

        auto lines = quxflux::from_range<std::vector>(QUXFLUX_GET_INPUT() | std::views::split('\n') | std::views::transform(as_string_view));

        map m(lines.size(), lines.front().size());
        std::ranges::transform(lines | std::views::join, m.data().begin(), map_element);
        return m;
    }

    using position = std::pair<ptrdiff_t, ptrdiff_t>;
    constexpr std::vector<position> possible_neighbors(const field p)
    {
        switch (p) {
        case field::none:
            return {};
        case field::NS:
            return { { -1, 0 }, { 1, 0 } };
        case field::WE:
            return { { 0, -1 }, { 0, 1 } };
        case field::NE:
            return { { -1, 0 }, { 0, 1 } };
        case field::NW:
            return { { -1, 0 }, { 0, -1 } };
        case field::SW:
            return { { 1, 0 }, { 0, -1 } };
        case field::SE:
            return { { 1, 0 }, { 0, 1 } };
        case field::start:
            return { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };
        }

        std::unreachable();
    }

    std::vector<position> find_loop_inner(const position current_pos, const position rel_origin, const map& m, std::set<position>& visited)
    {
        std::vector<std::vector<position>> found_paths_to_start;

        const auto current_value = m[current_pos.first, current_pos.second];

        if (current_value == field::start)
            found_paths_to_start.push_back({ current_pos });

        for (auto delta_pos : possible_neighbors(current_value)) {

            if (delta_pos == rel_origin)
                continue;

            const auto offset_pos = position { current_pos.first + delta_pos.first, current_pos.second + delta_pos.second };

            if (offset_pos.first < 0 || offset_pos.first >= m.rows() || //
                offset_pos.second < 0 || offset_pos.second >= m.cols())
                continue;

            if (visited.contains(offset_pos))
                continue;

            visited.insert(offset_pos);

            auto path = find_loop_inner(offset_pos, { -delta_pos.first, -delta_pos.second }, m, visited);

            if (!path.empty()) {
                path.insert(path.begin(), current_pos);
                found_paths_to_start.push_back(std::move(path));
            }
        }

        if (found_paths_to_start.empty())
            return {};

        return std::ranges::max(found_paths_to_start, std::less {}, [](const auto& t) { return t.size(); });
    }

    auto find_loop(const map& m)
    {
        auto indices = std::views::cartesian_product(std::views::iota(size_t { 0 }, m.rows()), std::views::iota(size_t { 0 }, m.cols()));

        const auto [start_row, start_col] = *std::ranges::find_if(indices, [&](const auto indices) {
            const auto [row, col] = indices;
            return m[row, col] == field::start;
        });

        std::set<std::pair<ptrdiff_t, ptrdiff_t>> visited;
        return find_loop_inner({ start_row, start_col }, { 0, 0 }, m, visited);
    }

    size_t part_1()
    {
        const auto map = get_input();
        return (find_loop(map).size() - 2) / 2 + 1;
    }

    size_t part_2()
    {
        return 0;
    }

} // namespace
}

int main()
{
    std::cout << quxflux::aoc::part_1() << '\n';
    std::cout << quxflux::aoc::part_2() << '\n';
    return 0;
}
