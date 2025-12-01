#pragma once
#include "figure.hpp"
#include "polygon_utils.hpp"
#include <array>
#include <memory>

template <Scalar T>
class Octagon : public Figure<T> 
{
public:
    explicit Octagon(const std::array<Point<T>, 8>& pts);
    explicit Octagon(std::initializer_list<Point<T>> list);

    double area() const override;
    Point<double> center() const override;
    bool operator==(const Octagon<T>& other) const;

private:
    std::array<std::unique_ptr<Point<T>>, 8> vertices;
};
