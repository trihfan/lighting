#include <algorithm>
#include "Tuple.h"
#include "Definitions.h"

using namespace lighting;

Tuple::Tuple(double x, double y, double z, double w) : x(x), y(y), z(z), w(w)
{    
}

bool Tuple::operator==(const Tuple& other) const
{
    return std::abs(x - other.x) < epsilon() && std::abs(x - other.x) < epsilon() && std::abs(y - other.y) < epsilon() && std::abs(z - other.z) < epsilon();
}

bool Tuple::operator!=(const Tuple& other) const
{
    return !(*this == other);
}

bool Tuple::isPoint() const
{
    return w == 1;
}

bool Tuple::isVector() const
{
    return w == 0;
}