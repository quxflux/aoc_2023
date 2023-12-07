#include "../util.h"

#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <ranges>
#include <regex>
#include <string>

namespace {
struct draw {
    std::string color;
    size_t quantity;
};

struct game {
    size_t id {};
    std::vector<std::vector<draw>> draws;
};

game parse_game(std::string_view line)
{
    const std::string t { line };

    game g;

    {
        const std::regex game_regex { R"(Game (\d+): )" };
        const std::sregex_iterator it { t.begin(), t.end(), game_regex };

        g.id = std::stoul((*it)[1]);
        line = line.substr((*it)[0].length());
    }

    {
        const std::regex draw_regex { R"(\s*(\d+) ([a-z]+))" };

        for (const auto game_str : std::views::split(line, ';') | std::views::transform(quxflux::as_string_view)) {
            std::vector<draw> draws;

            for (const auto draw_sv : std::views::split(game_str, ',') | std::views::transform(quxflux::as_string_view)) {

                const std::string draw_str { draw_sv };
                const std::sregex_iterator it { draw_str.begin(), draw_str.end(), draw_regex };

                draws.push_back(draw { .color = (*it)[2], .quantity = std::stoul((*it)[1]) });
            }

            g.draws.emplace_back(std::move(draws));
        }
    }

    return g;
}

std::vector<game> extract_games(const std::string_view lines)
{
    std::vector<game> result;
    std::ranges::copy(std::views::split(lines, '\n') | std::views::transform(quxflux::as_string_view) | std::views::transform(parse_game), std::back_inserter(result));
    return result;
}

size_t part_1()
{
    const std::map<std::string_view, size_t> available_quantities {
        { "red", 12 },
        { "green", 13 },
        { "blue", 14 }
    };

    const auto games = extract_games(QUXFLUX_GET_INPUT());

    const auto is_valid_game = [&](const game& g) {
        const auto is_valid_draw = [&](const draw& d) {
            const auto it = available_quantities.find(d.color);
            return it != available_quantities.end() && it->second >= d.quantity;
        };

        return std::ranges::all_of(g.draws | std::views::join, is_valid_draw);
    };

    return std::ranges::fold_left(games | std::views::filter(is_valid_game) | std::views::transform(&game::id), size_t { 0 }, std::plus {});
}

size_t part_2()
{
    const auto games = extract_games(QUXFLUX_GET_INPUT());

    const auto power_per_game = games | std::views::transform([](const game& g) {
        std::map<std::string_view, size_t> color_quantities;

        for (const draw& d : g.draws | std::views::join) {
            const auto it = color_quantities.find(d.color);
            if (it != color_quantities.end()) {
                it->second = std::max(it->second, d.quantity);
            } else {
                color_quantities.insert(it, { d.color, d.quantity });
            }
        }

        return std::ranges::fold_left(color_quantities | std::views::values, size_t { 1 }, std::multiplies {});
    });

    return std::ranges::fold_left(power_per_game, size_t { 0 }, std::plus {});
}

} // namespace

int main()
{
    std::cout << part_1() << '\n';
    std::cout << part_2() << '\n';
    return 0;
}
