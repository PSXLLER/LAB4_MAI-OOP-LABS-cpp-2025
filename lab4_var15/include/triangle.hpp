#pragma once
#include "point.hpp"
#include "concepts.hpp"
#include "polygon_utils.hpp"
#include "figure.hpp"
#include <array>

template <Scalar T>
class Triangle : public Figure<T> 
{
public:
    Triangle(Point<T> a, Point<T> b, Point<T> c);

    double area() const override;
    Point<double> center() const override;   

    bool operator==(const Triangle<T>& other) const;

private:
    std::array<Point<T>, 3> vertices;
};
