#ifndef SHAPE_H
#define SHAPE_H

#include <vector>

namespace lighting
{   
    class Ray;

    /**
     * Shape interface
     */ 
    class Shape
    {
    public:
        // construction
        Shape() = default;
        virtual ~Shape() = default;

        // intersection
        void intersect(const Ray& ray, std::vector<double>& intersections) const = 0;
    };
}
#endif
