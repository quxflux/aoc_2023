#pragma once

#include <cstdint>
#include <ostream>
#include <span>
#include <vector>

namespace quxflux::aoc
{
enum class field {
    none,
    NS,
    WE,
    NE,
    NW,
    SW,
    SE,
    start
};

struct map {
    map(const size_t rows, const size_t cols)
        : rows_(rows)
        , cols_(cols)
        , data_(rows * cols)
    {
    }

    [[nodiscard]] constexpr field& operator[](const size_t row, const size_t col)
    {
        return data_[row * cols_ + col];
    }

    [[nodiscard]] constexpr field operator[](const size_t row, const size_t col) const
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

    [[nodiscard]] constexpr std::span<field> data() { return { data_ }; }

private:
    size_t rows_;
    size_t cols_;
    std::vector<field> data_;
};
}
