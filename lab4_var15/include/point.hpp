#pragma once
#include "concepts.hpp"

template <Scalar T>
struct Point 
{
    T x;
    T y;

    Point() : x(0), y(0) {}
    Point(T _x, T _y) : x(_x), y(_y) {}

    template <Scalar U>
    Point(const Point<U>& other)
        : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)) {}

    bool operator==(const Point<T>& other) const noexcept {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Point<T>& other) const noexcept {
        return !(*this == other);
    }
};
