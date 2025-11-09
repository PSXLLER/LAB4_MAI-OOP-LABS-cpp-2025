#include "hexagon.hpp"
#include <algorithm>
#include <stdexcept>

template <Scalar T>
Hexagon<T>::Hexagon(const std::array<Point<T>, 6>& pts)
    : vertices(pts) {}

template <Scalar T>
Hexagon<T>::Hexagon(std::initializer_list<Point<T>> list) 
{
    if (list.size() != 6)
        throw std::invalid_argument("Hexagon must have 6 vertices");
    std::copy(list.begin(), list.end(), vertices.begin());
}

template <Scalar T>
double Hexagon<T>::area() const 
{
    return polygon_area(vertices.data(), vertices.size());
}

template <Scalar T>
Point<double> Hexagon<T>::center() const 
{
    return polygon_center(vertices.data(), vertices.size());
}

template <Scalar T>
bool Hexagon<T>::operator==(const Hexagon<T>& other) const 
{
    return vertices == other.vertices;
}

template class Hexagon<int>;
template class Hexagon<double>;
