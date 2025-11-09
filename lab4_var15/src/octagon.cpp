#include "octagon.hpp"
#include <algorithm>
#include <stdexcept>

template <Scalar T>
Octagon<T>::Octagon(const std::array<Point<T>, 8>& pts)
    : vertices(pts) {}

template <Scalar T>
Octagon<T>::Octagon(std::initializer_list<Point<T>> list) 
{
    if (list.size() != 8)
        throw std::invalid_argument("Octagon must have 8 vertices");
    std::copy(list.begin(), list.end(), vertices.begin());
}

template <Scalar T>
double Octagon<T>::area() const 
{
    return polygon_area(vertices.data(), vertices.size());
}

template <Scalar T>
Point<double> Octagon<T>::center() const 
{
    return polygon_center(vertices.data(), vertices.size());
}

template <Scalar T>
bool Octagon<T>::operator==(const Octagon<T>& other) const 
{
    return vertices == other.vertices;
}

template class Octagon<int>;
template class Octagon<double>;
