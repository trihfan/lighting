#include "Sphere.h"
#include "Tuple.h"
#include "Ray.h"

using namespace lighting;

void Sphere::intersect(const Ray& ray, std::vector<double>& intersections) const
{
    Tuple sphereToRay = ray.origin() - Tuple::Point(0, 0, 0);
    double a = dot(ray.direction(), ray.direction());
    double b = 2 * dot(ray.direction(), sphereToRay);
    double c = dot(sphereToRay, sphereToRay) - 1;
    double discriminant = b * b - 4 * a * c;

    if (discriminant >= 0)
    {
        intersections.push_back((-b - std::sqrt(discriminant)) / (2 * a));
        intersections.push_back((-b + std::sqrt(discriminant)) / (2 * a));
    }
}