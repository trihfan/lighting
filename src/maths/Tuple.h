#ifndef TUPLE_H
#define TUPLE_H

#include <ostream>
#include <array>

#define DECLARE_ACCESSOR(X, Y) inline double& ##X(){ return Y; } inline const double& ##X() const { return Y; }

namespace lighting
{
    class Tuple;

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
        Tuple();
        Tuple(double x, double y, double z, double w = 1);
        Tuple(const Tuple& other);
        ~Tuple() = default;

        // construction helpers
        static inline Tuple Point(double x, double y, double z) { return Tuple(x, y, z, 1); }
        static inline Tuple Vector(double x, double y, double z) { return Tuple(x, y, z, 0); }

        // assignement
        Tuple& operator=(const Tuple& other);
        
        // comparison
        bool operator==(const Tuple& other) const;
        bool operator!=(const Tuple& other) const;

        // accessor
        double& operator()(size_t index);
        const double& operator()(size_t index) const;
        DECLARE_ACCESSOR(x, data[0])
        DECLARE_ACCESSOR(y, data[1]);
        DECLARE_ACCESSOR(z, data[2]);
        DECLARE_ACCESSOR(w, data[3]);

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
        Tuple& operator*=(const Tuple& other);
        Tuple operator*(const Tuple& other) const;

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

    private:
        std::array<double, 4> data;
    };

    // inlines
    double dot(const Tuple& a, const Tuple& b)
    {
        return a.x() * b.x() + a.y() * b.y() + a.z() * b.z() + a.w() * b.w();
    }
    
    Tuple cross(const Tuple& a, const Tuple& b)
    {
        return Tuple::Vector(a.y() * b.z() - a.z() * b.y(), a.z() * b.x() - a.x() * b.z(), a.x() * b.y() - a.y() * b.x());
    }

    // streams
    static inline std::ostream &operator<<(std::ostream& os, const Tuple& tuple) 
    { 
        return os << "Tuple:" << (tuple.isVector() ? "point -> " : "vector -> ") << "[" << tuple.x() << ", " << tuple.y() << ", " << tuple.z() << ", " << tuple.w() << "]";
    }
}
#endif
