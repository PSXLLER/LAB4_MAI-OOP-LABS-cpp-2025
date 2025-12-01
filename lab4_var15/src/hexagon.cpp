#include "hexagon.hpp"
#include <algorithm>
#include <stdexcept>

template <Scalar T>
Hexagon<T>::Hexagon(const std::array<Point<T>, 6>& pts)
{
    for (size_t i = 0; i < 6; ++i)
        vertices[i] = std::make_unique<Point<T>>(pts[i]);
}

template <Scalar T>
Hexagon<T>::Hexagon(std::initializer_list<Point<T>> list)
{
    if (list.size() != 6)
        throw std::invalid_argument("Hexagon must have 6 points");

    size_t i = 0;
    for (const auto& p : list)
        vertices[i++] = std::make_unique<Point<T>>(p);
}

template <Scalar T>
double Hexagon<T>::area() const
{
    std::array<Point<T>, 6> pts;
    for (size_t i = 0; i < 6; ++i)
        pts[i] = *vertices[i];

    return polygon_area(pts.data(), 6);
}

template <Scalar T>
Point<double> Hexagon<T>::center() const
{
    std::array<Point<T>, 6> pts;
    for (size_t i = 0; i < 6; ++i)
        pts[i] = *vertices[i];

    return polygon_center(pts.data(), 6);
}

template <Scalar T>
bool Hexagon<T>::operator==(const Hexagon<T>& other) const
{
    for (size_t i = 0; i < 6; ++i)
        if (!(*vertices[i] == *other.vertices[i]))
            return false;
    return true;
}

template class Hexagon<int>;
template class Hexagon<double>;
