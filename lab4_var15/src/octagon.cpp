#include "octagon.hpp"
#include <algorithm>
#include <stdexcept>

template <Scalar T>
Octagon<T>::Octagon(const std::array<Point<T>, 8>& pts)
{
    for (size_t i = 0; i < 8; ++i)
        vertices[i] = std::make_unique<Point<T>>(pts[i]);
}

template <Scalar T>
Octagon<T>::Octagon(std::initializer_list<Point<T>> list)
{
    if (list.size() != 8)
        throw std::invalid_argument("Octagon must have 8 points");

    size_t i = 0;
    for (const auto& p : list)
        vertices[i++] = std::make_unique<Point<T>>(p);
}

template <Scalar T>
double Octagon<T>::area() const
{
    std::array<Point<T>, 8> pts;
    for (size_t i = 0; i < 8; ++i)
        pts[i] = *vertices[i];

    return polygon_area(pts.data(), 8);
}

template <Scalar T>
Point<double> Octagon<T>::center() const
{
    std::array<Point<T>, 8> pts;
    for (size_t i = 0; i < 8; ++i)
        pts[i] = *vertices[i];

    return polygon_center(pts.data(), 8);
}

template <Scalar T>
bool Octagon<T>::operator==(const Octagon<T>& other) const
{
    for (size_t i = 0; i < 8; ++i)
        if (!(*vertices[i] == *other.vertices[i]))
            return false;
    return true;
}

template class Octagon<int>;
template class Octagon<double>;
