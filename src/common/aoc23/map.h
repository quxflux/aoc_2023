#pragma once

#include <cstdint>
#include <ranges>
#include <span>
#include <vector>

namespace quxflux::aoc {

template <typename T>
struct map {
    map(const size_t rows, const size_t cols)
        : rows_(rows)
        , cols_(cols)
        , data_(rows * cols)
    {
    }

    [[nodiscard]] constexpr T& operator[](const size_t row, const size_t col)
    {
        return data_[row * cols_ + col];
    }

    [[nodiscard]] constexpr const T& operator[](const size_t row, const size_t col) const
    {
        return data_[row * cols_ + col];
    }

    [[nodiscard]] constexpr size_t rows() const
    {
        return rows_;
    }

    [[nodiscard]] constexpr size_t cols() const
    {
        return cols_;
    }

    [[nodiscard]] constexpr std::span<T> data() { return { data_ }; }
    [[nodiscard]] constexpr std::span<const T> data() const { return { data_ }; }

private:
    size_t rows_;
    size_t cols_;
    std::vector<T> data_;
};

template <typename T>
constexpr auto index_view(const map<T>& m)
{
    return std::views::cartesian_product(std::views::iota(size_t { 0 }, m.rows()), std::views::iota(size_t { 0 }, m.cols()));
}
}
