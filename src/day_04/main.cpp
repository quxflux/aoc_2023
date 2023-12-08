#include "../util.h"

#include <set>

namespace {

struct card {
    size_t id = 0;
    size_t quantity = 1;
    std::array<size_t, 10> winning_numbers {};
    std::array<size_t, 25> our_numbers {};
};

card card_from_line(const std::string_view line)
{
    const std::vector numbers {
        std::from_range, std::views::chunk_by(line, [](const auto a, const auto b) { return quxflux::is_digit(a) == quxflux::is_digit(b); }) //
            | std::views::filter([](const auto range) {
                  return quxflux::is_digit(range.front());
              }) //
            | std::views::transform([](const auto r) {
                  return std::stoul(std::string { r.begin(), r.end() });
              })
    };

    card c { .id = numbers.front() };
    std::ranges::copy(numbers | std::views::drop(1) | std::views::take(10), c.winning_numbers.begin());
    std::ranges::copy(numbers | std::views::drop(11), c.our_numbers.begin());
    return c;
}

size_t num_winnings_cards(const card& c)
{
    const std::set<size_t> a(std::from_range, c.winning_numbers);
    const std::set<size_t> b(std::from_range, c.our_numbers);

    std::vector<size_t> intersection;
    std::ranges::set_intersection(a, b, std::back_inserter(intersection));

    return intersection.size();
}

size_t calculate_points(const std::string_view line)
{
    const auto winning_cards = num_winnings_cards(card_from_line(line));
    return winning_cards == 0 ? 0 : (0x1 << (winning_cards - 1));
}

size_t part_1()
{
    return std::ranges::fold_left(std::views::split(QUXFLUX_GET_INPUT(), '\n') | std::views::transform(quxflux::as_string_view) | std::views::transform(&calculate_points), size_t { 0 }, std::plus<>());
}

size_t part_2()
{
    std::vector cards { std::from_range, std::views::split(QUXFLUX_GET_INPUT(), '\n') | std::views::transform(quxflux::as_string_view) | std::views::transform(&card_from_line) };

    for (const auto&& [idx, card] : cards | std::views::enumerate) {
        const auto num_win = num_winnings_cards(card);

        for (auto& next : std::span { cards }.subspan(idx + 1, num_win))
            next.quantity += card.quantity;
    }

    return std::ranges::fold_left(cards | std::views::transform(&card::quantity), size_t { 0 }, std::plus {});
}

} // namespace

int main()
{
    std::cout << part_1() << '\n';
    std::cout << part_2() << '\n';
    return 0;
}
