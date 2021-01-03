#ifndef COLOR_H
#define COLOR_H

#include "Tuple.h"

#
namespace lighting
{
    class Color : public Tuple
    {
    public:
        Color() : Tuple(0, 0, 0, 0) {}
        Color(double r, double g, double b, double a = 1) : Tuple(r, g, b, a) {}
        Color(const Tuple& tuple) : Tuple(tuple) {}
        DECLARE_ACCESSOR(r, x())
        DECLARE_ACCESSOR(g, y());
        DECLARE_ACCESSOR(b, z());
        DECLARE_ACCESSOR(a, w());
    };
}
#endif
