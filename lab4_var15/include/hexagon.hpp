#pragma once
#include "figure.hpp"
#include "polygon_utils.hpp"
#include <memory>
#include <array>
#include <initializer_list>

template <Scalar T>
class Hexagon : public Figure<T> 
{
public:
    explicit Hexagon(const std::array<Point<T>, 6>& pts);
    explicit Hexagon(std::initializer_list<Point<T>> list);

    double area() const override;
    Point<double> center() const override;
    bool operator==(const Hexagon<T>& other) const;

private:
    std::array<std::unique_ptr<Point<T>>, 6> vertices;
};
