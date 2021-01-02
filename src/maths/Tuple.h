#ifndef TUPLE_H
#define TUPLE_H

#include <ostream>

namespace lighting
{
    class Tuple;

    // helpers
    static inline Tuple point(double x, double y, double z);
    static inline Tuple vector(double x, double y, double z);
    static inline std::ostream &operator<<(std::ostream& os, const Tuple& tuple); 

    // maths
    static inline double dot(const Tuple& a, const Tuple& b);
    static inline Tuple cross(const Tuple& a, const Tuple& b);

    /**
     * Tuple class
     */ 
    class Tuple
    {
    public:
        // construction
        Tuple() = default;
        Tuple(double x, double y, double z, double w = 1);
        ~Tuple() = default;

        // comparison
        bool operator==(const Tuple& other) const;
        bool operator!=(const Tuple& other) const;

        // add
        Tuple& operator+=(const Tuple& other);
        Tuple operator+(const Tuple& other) const;

        // sub
        Tuple& operator-=(const Tuple& other);
        Tuple operator-(const Tuple& other) const;

        // negate
        Tuple operator-() const;

        // mult
        Tuple& operator*=(double scalar);
        Tuple operator*(double scalar) const;

        // div
        Tuple& operator/=(double scalar);
        Tuple operator/(double scalar) const;

        // length
        double length2() const;
        double length() const;

        // normalize
        Tuple& normalize();
        Tuple normalized() const;

        // type
        bool isPoint() const;
        bool isVector() const;

    public:
        double x = 0, y = 0, z = 0, w = 0;
    };

    // inlines
    Tuple point(double x, double y, double z)
    {
        return Tuple(x, y, z, 1);
    }
    
    Tuple vector(double x, double y, double z)
    {
        return Tuple(x, y, z, 0);
    }

    double dot(const Tuple& a, const Tuple& b)
    {
        return a.x * b. x + a.y * b. y + a.z * b. z + a.w * b. w;
    }
    
    Tuple cross(const Tuple& a, const Tuple& b)
    {
        return vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
    }

    // streams
    std::ostream &operator<<(std::ostream& os, const Tuple& tuple) 
    { 
        return os << "Tuple:" << (tuple.isVector() ? "point -> " : "vector -> ") << "[" << tuple.x << ", " << tuple.y << ", " << tuple.z << ", " << tuple.w << "]";
    }
}
#endif
