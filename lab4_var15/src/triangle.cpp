#include "triangle.hpp"
#include "polygon_utils.hpp"

template <Scalar T>
Triangle<T>::Triangle(Point<T> a, Point<T> b, Point<T> c)
{
    vertices[0] = std::make_unique<Point<T>>(a);
    vertices[1] = std::make_unique<Point<T>>(b);
    vertices[2] = std::make_unique<Point<T>>(c);
}

template <Scalar T>
double Triangle<T>::area() const
{
    std::array<Point<T>, 3> pts;
    for (int i = 0; i < 3; ++i)
        pts[i] = *vertices[i];

    return polygon_area(pts.data(), 3);
}

template <Scalar T>
Point<double> Triangle<T>::center() const
{
    std::array<Point<T>, 3> pts;
    for (int i = 0; i < 3; ++i)
        pts[i] = *vertices[i];

    return polygon_center(pts.data(), 3);
}

template <Scalar T>
bool Triangle<T>::operator==(const Triangle<T>& other) const
{
    for (int i = 0; i < 3; ++i)
        if (!(*vertices[i] == *other.vertices[i]))
            return false;
    return true;
}

template class Triangle<int>;
template class Triangle<double>;
