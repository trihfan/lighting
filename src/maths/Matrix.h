#ifndef MATRIX_H
#define MATRIX_H

#include <ostream>
#include <array>
#include <initializer_list>
#include "Definitions.h"
#include "Tuple.h"

namespace lighting
{
    /**
     * Base matrix class
     */ 
    template <size_t rows, size_t cols> 
    class Matrix
    {
    public:
        // destructor
        virtual ~Matrix() = default;

        // size
        inline constexpr size_t rowCount() const { return rows; }
        inline constexpr size_t colCount() const { return cols; }
        inline constexpr size_t valueCount() const { return rowCount() * colCount(); }

        // assignement
        Matrix& operator=(const Matrix& other) { data = other.data; return *this; }
        
        // accessor
        double& operator()(size_t index) { return data[index]; }
        const double& operator()(size_t index) const { return data[index]; }
        double& operator()(size_t x, size_t y) { return data[x * cols + y]; }
        const double& operator()(size_t x, size_t y) const { return data[x * cols + y]; }

        // comparison
        bool operator==(const Matrix& other) const
        {
            for (size_t i = 0; i < data.size(); i++)
            {
                if (std::abs(data[i] - other.data[i]) >= epsilon())
                {
                    return false;
                }
            }
            return true;
        }

        bool operator!=(const Matrix& other) const{ return !(*this == other); }

        // mult scalar
        Matrix& operator*=(double scalar) { *this = *this * scalar; return *this; }
        Matrix operator*(double scalar) const
        {
            Matrix copy(*this);
            for (size_t i = 0; i < copy.data.size(); i++)
            {
                copy.data[i] *= scalar;
            }
            return copy;
        }

        // mult matrix
        Matrix& operator*=(const Matrix& other) { *this = *this * other; return *this; }
        Matrix operator*(const Matrix& other) const
        {
            Matrix copy;
            for (size_t row = 0; row < rowCount(); row++)
            {
                for (size_t col = 0; col < colCount(); col++)
                {
                    copy(row, col) = (*this)(row, 0) * other(0, col) + (*this)(row, 1) * other(1, col) + (*this)(row, 2) * other(2, col) + (*this)(row, 3) * other(3, col);
                }
            }
            return copy;
        }

        // mult tuple
        virtual Tuple operator*(const Tuple& other) const
        {
            Tuple t(0, 0, 0, 0);
            for (size_t row = 0; row < rowCount(); row++)
            {
                for (size_t col = 0; col < colCount(); col++)
                {
                    t(row) += (*this)(row, col) * other(col);
                }
            }
            return t;
        }

        // transpose
        Matrix& transpose() { *this = transposed(); return *this; }
        Matrix transposed() const
        {
            Matrix copy(*this);
            for (size_t row = 0; row < rowCount(); row++)
            {
                for (size_t col = 0; col < colCount(); col++)
                {
                    copy(row, col) = (*this)(col, row);
                }
            }
            return copy;
        }

    protected:
        std::array<double, rows * cols> data;

        // null constructor 
        Matrix() = default;

        // constructor from value
        Matrix(std::initializer_list<double> values) { std::copy(values.begin(), values.end(), data.begin()); }

        // copy constructor
        Matrix(const Matrix& other) : data(other.data) {}
    };

    /**
     * Specialization of Matrix to a matrix of 2 rows and 2 columns
     */ 
    class Matrix2x2 : public Matrix<2, 2>
    {
    public:
        /**
         * identity constructor
         */
        Matrix2x2();

        /**
         * constructor from values
         */
        Matrix2x2(double a11, double a12, double a21, double a22);

        /**
         * determinant
         */
        double determinant() const;
    };

    /**
     * Specialization of Matrix to a matrix of 3 rows and 3 columns
     */ 
    class Matrix3x3 : public Matrix<3, 3>
    {
    public:
        /**
         * identity constructor
         */
        Matrix3x3();

        /**
         * constructor from values
         */
        Matrix3x3(double a11, double a12, double a13, double a21, double a22, double a23, double a31, double a32, double a33);

        /**
         * compute submatrix
         */
        Matrix2x2 submatrix(int rowToRemove, int colToRemove) const;

        /**
         * minor
         */
        double minor(int rowToRemove, int colToRemove) const;

        /**
         * cofactor
         */
        double cofactor(int rowToRemove, int colToRemove) const;

        /**
         * determinant
         */
        double determinant() const;
    };

    /**
     * Specialization of Matrix to a matrix of 4 rows and 4 columns
     */ 
    class Matrix4x4 : public Matrix<4, 4>
    {
    public:
        /**
         * identity constructor
         */
        Matrix4x4();

        /**
         * constructor from values
         */
        Matrix4x4(double a11, double a12, double a13, double a14, double a21, double a22, double a23, double a24, double a31, double a32, double a33, double a34, double a41, double a42, double a43, double a44);

        /**
         * compute submatrix
         */
        Matrix3x3 submatrix(int rowToRemove, int colToRemove) const;

        /**
         * minor
         */
        double minor(int rowToRemove, int colToRemove) const;

        /**
         * cofactor
         */
        double cofactor(int rowToRemove, int colToRemove) const;

        /**
         * determinant
         */
        double determinant() const;
        
        /**
         * is the matrix invertible
         */
        bool isInvertible() const;

        /**
         * inverse the matrix
         */
        Matrix4x4& inverse();
        Matrix4x4 inverted() const;
    };

    // other operators
    template <size_t rows, size_t cols> 
    static inline Tuple operator*(const Tuple& tuple, const Matrix<rows, cols>& matrix)
    {
        Tuple t(0, 0, 0, 0);
        for (size_t row = 0; row < matrix.rowCount(); row++)
        {
            for (size_t col = 0; col < matrix.colCount(); col++)
            {
                t(row) += matrix(row, col) * tuple(col);
            }
        }
        return t;
    }

    // streams
    template<int rows, int cols> 
    static inline std::ostream &operator<<(std::ostream& os, const Matrix<rows, cols>& matrix) 
    { 
        os << "Matrix" << rows << "x" << cols << " -> " << std::endl;
        for (size_t i = 0; i < matrix.rowCount(); i++)
        {
            os << "[ ";
            for (size_t j = 0; j < matrix.colCount(); j++)
            {
                os << matrix(i, j);
                if (j < matrix.colCount() - 1)
                {
                    os << ", ";
                }
            }
            os << " ]" << std::endl;
        }
        return os;
    }

    static inline std::ostream &operator<<(std::ostream& os, const Matrix2x2& matrix)
    {
        os << *static_cast<const Matrix<2, 2>*>(&matrix);
        return os;
    } 

    static inline std::ostream &operator<<(std::ostream& os, const Matrix3x3& matrix)
    {
        os << *static_cast<const Matrix<3, 3>*>(&matrix);
        return os;
    } 

    static inline std::ostream &operator<<(std::ostream& os, const Matrix4x4& matrix)
    {
        os << *static_cast<const Matrix<4, 4>*>(&matrix);
        return os;
    } 
}
#endif
