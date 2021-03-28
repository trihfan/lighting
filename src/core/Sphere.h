#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"

namespace lighting
{   
    class Sphere : public Shape
    {
    public:
        // construction
        Sphere() = default;
        virtual ~Sphere() = default;

        // intersection
        void intersect(const Ray& ray, std::vector<double>& intersections) const override;
    };
}
#endif
