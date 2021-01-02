#ifndef MATRIX_H
#define MATRIX_H

#include <ostream>
#include <array>

namespace lighting
{
    class Tuple;
    class Matrix;

    // helpers
    static inline std::ostream &operator<<(std::ostream& os, const Matrix& matrix); 

    class Matrix
    {
    public:
        // construction -> identity matrix
        Matrix();

        // 2x2 matrix
        Matrix(double a11, double a12,
               double a21, double a22);

        // 3x3 matrix
        Matrix(double a11, double a12, double a13,
               double a21, double a22, double a23,
               double a31, double a32, double a33);

        // 4x4 matrix
        Matrix(double a11, double a12, double a13, double a14,
               double a21, double a22, double a23, double a24,
               double a31, double a32, double a33, double a34,
               double a41, double a42, double a43, double a44);

        Matrix(const Matrix& other);
        ~Matrix() = default;

        // assignement
        Matrix& operator=(const Matrix& other);
        
        // accessor
        double& operator()(size_t index);
        const double& operator()(size_t index) const;
        double& operator()(size_t x, size_t y);
        const double& operator()(size_t x, size_t y) const;

        // comparison
        bool operator==(const Matrix& other) const;
        bool operator!=(const Matrix& other) const;

        // mult
        Matrix& operator*=(double scalar);
        Matrix operator*(double scalar) const;
        Matrix& operator*=(const Matrix& other);
        Matrix operator*(const Matrix& other) const;
        Tuple operator*(const Tuple& other) const;

        // transpose
        Matrix transposed() const;
        Matrix& transpose();

    private:
        std::array<double, 4 * 4> data;
    };

    // streams
    std::ostream &operator<<(std::ostream& os, const Matrix& matrix) 
    { 
        return os << "Matrix -> " << std::endl;
        for (size_t i = 0; i < 4; i++)
        {
            os << "[" << matrix(i, 0) << ", " << matrix(i, 1) << ", " << matrix(i, 2) << ", " << matrix(i, 3) << "]" << std::endl;
        }
    }
}
#endif
