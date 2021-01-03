#ifndef RAY_H
#define RAY_H

#include "Tuple.h"

namespace lighting
{
    class Ray
    {
    public:
        // construction
        Ray() = default;
        Ray(const Tuple& origin, const Tuple& direction);
        Ray(const Ray& other);
        ~Ray() = default;

        // assignement
        Ray& operator=(const Ray& other);
       
        // accessor
        const Tuple& origin() const;
        const Tuple& direction() const;

        // get point on ray
        Tuple position(double distance) const;

    private:
        Tuple origin_;
        Tuple direction_;
    };
}
#endif
