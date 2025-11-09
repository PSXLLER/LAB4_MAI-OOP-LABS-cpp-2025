#pragma once
#include "point.hpp"
#include "concepts.hpp"

template <Scalar T>
class Figure 
{
public:
    virtual double area() const = 0;
    virtual Point<double> center() const = 0;  
    virtual ~Figure() = default;               
};
