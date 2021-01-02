#include <algorithm>
#include <cmath>
#include "Tuple.h"
#include "Definitions.h"

using namespace lighting;

Tuple::Tuple(double x, double y, double z, double w) : x(x), y(y), z(z), w(w)
{    
}

Tuple& Tuple::operator=(const Tuple& other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
    return *this;
}

bool Tuple::operator==(const Tuple& other) const
{
    return std::abs(x - other.x) < epsilon() && std::abs(x - other.x) < epsilon() && std::abs(y - other.y) < epsilon() && std::abs(z - other.z) < epsilon();
}

bool Tuple::operator!=(const Tuple& other) const
{
    return !(*this == other);
}

Tuple& Tuple::operator+=(const Tuple& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
    return *this;
}

Tuple Tuple::operator+(const Tuple& other) const
{
    return Tuple(x + other.x, y + other.y, z + other.z, w + other.w);
}

Tuple& Tuple::operator-=(const Tuple& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
    return *this;
}

Tuple Tuple::operator-(const Tuple& other) const
{
    return Tuple(x - other.x, y - other.y, z - other.z, w - other.w);
}

Tuple Tuple::operator-() const
{
    return Tuple(-x, -y, -z, -w);
}

Tuple& Tuple::operator*=(double scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
    return *this;
}

Tuple Tuple::operator*(double scalar) const
{
    return Tuple(x * scalar, y * scalar, z * scalar, w * scalar);
}

Tuple& Tuple::operator*=(const Tuple& other)
{
    x *= other.x;
    y *= other.y;
    z *= other.z;
    w *= other.w;
    return *this;
}

Tuple Tuple::operator*(const Tuple& other) const
{
    return Tuple(x * other.x, y * other.y, z * other.z, w * other.w);
}

Tuple& Tuple::operator/=(double scalar)
{
    x /= scalar;
    y /= scalar;
    z /= scalar;
    w /= scalar;
    return *this;
}

Tuple Tuple::operator/(double scalar) const
{
    return Tuple(x / scalar, y / scalar, z / scalar, w / scalar);
}

double Tuple::length2() const
{
    return x * x + y * y + z * z + w * w;
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
    return w == 0;
}
