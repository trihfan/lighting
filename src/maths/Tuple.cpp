#include <algorithm>
#include <cmath>
#include "Tuple.h"
#include "Definitions.h"
#include "Matrix.h"

using namespace lighting;

Tuple::Tuple(double x, double y, double z, double w) : data({ x, y, z, w })
{    
}

Tuple::Tuple() : Tuple(0, 0, 0, 0)
{    
}

Tuple::Tuple(const Tuple& other) : data(other.data)
{
}

Tuple& Tuple::operator=(const Tuple& other)
{
    data = other.data;
    return *this;
}

bool Tuple::operator==(const Tuple& other) const
{
    for (size_t i = 0; i < data.size(); i++)
    {
        if (std::abs(data[i] - other.data[i]) >= epsilon())
        {
            return false;
        }
    }
    return true;
}

bool Tuple::operator!=(const Tuple& other) const
{
    return !(*this == other);
}

double& Tuple::operator()(size_t index)
{
    return data[index];
}

const double& Tuple::operator()(size_t index) const
{
    return data[index];
}

Tuple& Tuple::operator+=(const Tuple& other)
{
    for (size_t i = 0; i < data.size(); i++)
    {
        data[i] += other.data[i];
    }
    return *this;
}

Tuple Tuple::operator+(const Tuple& other) const
{
    return Tuple(data[0] + other.data[0], data[1] + other.data[1], data[2] + other.data[2], data[3] + other.data[3]);
}

Tuple& Tuple::operator-=(const Tuple& other)
{
    for (size_t i = 0; i < data.size(); i++)
    {
        data[i] -= other.data[i];
    }
    return *this;
}

Tuple Tuple::operator-(const Tuple& other) const
{
    return Tuple(data[0] - other.data[0], data[1] - other.data[1], data[2] - other.data[2], data[3] - other.data[3]);
}

Tuple Tuple::operator-() const
{
    return Tuple(-data[0], -data[1], -data[2], -data[3]);
}

Tuple& Tuple::operator*=(double scalar)
{
    for (size_t i = 0; i < data.size(); i++)
    {
        data[i] *= scalar;
    }
    return *this;
}

Tuple Tuple::operator*(double scalar) const
{
    return Tuple(data[0] * scalar, data[1] * scalar, data[2] * scalar, data[3] * scalar);
}

Tuple& Tuple::operator*=(const Tuple& other)
{
    for (size_t i = 0; i < data.size(); i++)
    {
        data[i] *= other.data[i];
    }
    return *this;
}

Tuple Tuple::operator*(const Tuple& other) const
{
    return Tuple(data[0] * other.data[0], data[1] * other.data[1], data[2] * other.data[2], data[3] * other.data[3]);
}

Tuple Tuple::operator*(const Matrix& other) const
{
    Tuple t;
    for (size_t row = 0; row < 4; row++)
    {
        t(row) = other(row, 0) * (*this)(0) + other(row, 1) * (*this)(1) + other(row, 2) * (*this)(2) + other(row, 3) * (*this)(3);
    }
    return t;
}

Tuple& Tuple::operator/=(double scalar)
{
    for (size_t i = 0; i < data.size(); i++)
    {
        data[i] /= scalar;
    }
    return *this;
}

Tuple Tuple::operator/(double scalar) const
{
    return Tuple(data[0] / scalar, data[1] / scalar, data[2] / scalar, data[3] / scalar);
}

double Tuple::length2() const
{
    return std::pow(data[0], 2) + std::pow(data[1], 2) + std::pow(data[2], 2) + std::pow(data[3], 2);
}

double Tuple::length() const
{
    return std::sqrt(length2());
}

Tuple& Tuple::normalize() 
{
    *this /= length();   
    return *this;  
}

Tuple Tuple::normalized() const
{
    return *this / length();
}

bool Tuple::isPoint() const
{
    return !isVector();
}

bool Tuple::isVector() const
{
    return data[3] == 0;
}
