#ifndef TUPLE_H
#define TUPLE_H

namespace lighting
{
    class Tuple;

    // helpers
    static inline Tuple point(double x, double y, double z);
    static inline Tuple vector(double x, double y, double z);

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
    static inline Tuple point(double x, double y, double z)
    {
        return Tuple(x, y, z, 1);
    }
    
    static inline Tuple vector(double x, double y, double z)
    {
        return Tuple(x, y, z, 0);
    }
}
#endif
