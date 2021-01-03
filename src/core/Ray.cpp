#include "Ray.h"

using namespace lighting;

Ray::Ray(const Tuple& origin, const Tuple& direction) : origin_(origin), direction_(direction)
{
}

Ray::Ray(const Ray& other) : origin_(other.origin_), direction_(other.direction_)
{
}

Ray& Ray::operator=(const Ray& other)
{
    origin_ = other.origin_;
    direction_ = other.direction_;
    return *this;
}

const Tuple& Ray::origin() const
{
    return origin_;
}

const Tuple& Ray::direction() const
{
    return direction_;
}

Tuple Ray::position(double distance) const
{
    return origin_ + distance * direction_;
}