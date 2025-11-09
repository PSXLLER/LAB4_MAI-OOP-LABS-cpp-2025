#pragma once
#include "point.hpp"
#include "concepts.hpp"
#include <cstddef>  

template <Scalar T>
double polygon_area(const Point<T>* pts, size_t n);

template <Scalar T>
Point<double> polygon_center(const Point<T>* pts, size_t n);
