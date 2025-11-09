#include "triangle.hpp"

template <Scalar T>
Triangle<T>::Triangle(Point<T> a, Point<T> b, Point<T> c) 
{
    vertices[0] = a;
    vertices[1] = b;
    vertices[2] = c;
}

template <Scalar T>
double Triangle<T>::area() const 
{
    return polygon_area(vertices.data(), 3);
}

template <Scalar T>
Point<double> Triangle<T>::center() const 
{
    return polygon_center(vertices.data(), 3);
}

template <Scalar T>
bool Triangle<T>::operator==(const Triangle<T>& other) const 
{
    for (int i = 0; i < 3; ++i)
        if (!(vertices[i] == other.vertices[i]))
            return false;
    return true;
}

template class Triangle<int>;
template class Triangle<double>;
