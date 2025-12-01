#pragma once
#include "point.hpp"
#include "concepts.hpp"
#include <cstddef>
#include <cmath>

template <Scalar T>
double polygon_area(const Point<T>* pts, size_t n)
{
    double area = 0.0;
    for (size_t i = 0; i < n; ++i) {
        const Point<T>& p1 = pts[i];
        const Point<T>& p2 = pts[(i + 1) % n];
        area += static_cast<double>(p1.x) * p2.y
              - static_cast<double>(p2.x) * p1.y;
    }
    return std::abs(area) / 2.0;
}

template <Scalar T>
Point<double> polygon_center(const Point<T>* pts, size_t n)
{
    if (n == 3) {
        double cx = (static_cast<double>(pts[0].x) +
                     static_cast<double>(pts[1].x) +
                     static_cast<double>(pts[2].x)) / 3.0;
        double cy = (static_cast<double>(pts[0].y) +
                     static_cast<double>(pts[1].y) +
                     static_cast<double>(pts[2].y)) / 3.0;
        return {cx, cy};
    }

    double cx = 0.0, cy = 0.0;
    double A = polygon_area(pts, n);

    for (size_t i = 0; i < n; ++i) {
        const Point<T>& p1 = pts[i];
        const Point<T>& p2 = pts[(i + 1) % n];
        double cross = static_cast<double>(p1.x) * p2.y
                     - static_cast<double>(p2.x) * p1.y;
        cx += (static_cast<double>(p1.x) + p2.x) * cross;
        cy += (static_cast<double>(p1.y) + p2.y) * cross;
    }

    double factor = 1.0 / (6.0 * A);
    return {cx * factor, cy * factor};
}
