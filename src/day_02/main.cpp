#include <aoc23/util.h>

#include <map>
#include <spanstream>

namespace {

struct draw {
    std::string color;
    size_t quantity;
};

struct game {
    size_t id {};
    std::vector<std::vector<draw>> draws;
};

game parse_game(const std::string_view line)
{
    game g;

    constexpr std::string_view prefix { "Game " };

    size_t offset = std::string_view { "Game" }.length();
    offset += static_cast<size_t>((std::ispanstream(line.substr(offset)) >> g.id).tellg()) + 1;

    for (const auto game_str : std::views::split(line.substr(offset), ';') | std::views::transform(quxflux::as_string_view)) {
        std::vector<draw> draws;

        for (const auto draw_sv : std::views::split(game_str, ',') | std::views::transform(quxflux::as_string_view)) {

            draw d;
            std::ispanstream { draw_sv } >> d.quantity >> d.color;
            draws.push_back(d);
        }

        g.draws.emplace_back(std::move(draws));
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
