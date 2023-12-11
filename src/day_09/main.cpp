#include <aoc23/util.h>

#include <spanstream>

namespace {

auto get_input()
{
    const auto process_line = [](const std::string_view line) {
        std::vector<ptrdiff_t> numbers;

        std::ispanstream iss { line };
        std::ranges::copy(std::istream_iterator<ptrdiff_t> { iss }, std::istream_iterator<ptrdiff_t> {}, std::back_inserter(numbers));

        return numbers;
    };

    return quxflux::from_range<std::vector>(QUXFLUX_GET_INPUT() | std::views::split('\n') | std::views::transform(quxflux::as_string_view) | std::views::transform(process_line));
}

struct add_last { };
struct subtract_from_first { };

template <typename Op>
auto solve(const std::span<const ptrdiff_t> numbers)
{
    auto buf = quxflux::from_range<std::vector>(numbers);
    std::vector<ptrdiff_t> last_elements;

    constexpr auto make_adjacent_diff = std::views::adjacent_transform<2>([](const auto lhs, const auto rhs) { return rhs - lhs; });

    while (!std::ranges::all_of(buf, std::bind_front(std::equal_to {}, ptrdiff_t { 0 }))) {
        last_elements.push_back(std::same_as<Op, add_last> ? buf.back() : buf.front());
        buf = quxflux::from_range<std::vector>(quxflux::from_range<std::vector>(buf | make_adjacent_diff));
    }

    size_t sum = 0;

    while (!last_elements.empty()) {
        if constexpr (std::same_as<Op, add_last>)
            sum = sum + last_elements.back();
        else
            sum = last_elements.back() - sum;

        last_elements.pop_back();
    }

    return sum;
}

template <typename Op>
size_t solve_with_op()
{
    return std::ranges::fold_left(get_input() | std::views::transform(&solve<Op>), ptrdiff_t { 0 }, std::plus {});
}

size_t part_1()
{
    return solve_with_op<add_last>();
}

size_t part_2()
{
    return solve_with_op<subtract_from_first>();
}

} // namespace

int main()
{
    std::cout << part_1() << '\n';
    std::cout << part_2() << '\n';
    return 0;
}
