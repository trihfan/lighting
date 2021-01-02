#include "Matrix.h"
#include "Definitions.h"
#include "Tuple.h"

using namespace lighting;

Matrix::Matrix() : Matrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1)
{
}

Matrix::Matrix(double a11, double a12,
               double a21, double a22) : Matrix(a11, a12, 0, 0, a21, a22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
{
}

Matrix::Matrix(double a11, double a12, double a13,
               double a21, double a22, double a23,
               double a31, double a32, double a33) : Matrix(a11, a12, a13, 0, a21, a22, a23, 0, a31, a32, a33, 0, 0, 0, 0, 0)
{
}

Matrix::Matrix(double a11, double a12, double a13, double a14,
               double a21, double a22, double a23, double a24,
               double a31, double a32, double a33, double a34,
               double a41, double a42, double a43, double a44) : data({ a11, a12, a13, a14, a21, a22, a23, a24, a31, a32, a33, a34, a41, a42, a43, a44 })
{
}

Matrix::Matrix(const Matrix& other) : data(other.data)
{
}

Matrix& Matrix::operator=(const Matrix& other)
{
    data = other.data;
    return *this;
}
        
double& Matrix::operator()(size_t index)
{
    return data[index];
}

const double& Matrix::operator()(size_t index) const
{
    return data[index];
}

double& Matrix::operator()(size_t x, size_t y)
{
    return data[x * 4 + y];
}

const double& Matrix::operator()(size_t x, size_t y) const
{
    return data[x * 4 + y];
}

bool Matrix::operator==(const Matrix& other) const
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

bool Matrix::operator!=(const Matrix& other) const
{
    return !(*this == other);
}

Matrix& Matrix::operator*=(double scalar)
{
    for (size_t i = 0; i < data.size(); i++)
    {
        data[i] *= scalar;
    }
    return *this;
}

Matrix Matrix::operator*(double scalar) const
{
    Matrix m(*this);
    for (size_t i = 0; i < m.data.size(); i++)
    {
        m.data[i] *= scalar;
    }
    return m;
}

Matrix& Matrix::operator*=(const Matrix& other)
{
    *this = *this * other;
    return *this;
}

Matrix Matrix::operator*(const Matrix& other) const
{
    Matrix m;
    for (size_t row = 0; row < 4; row++)
    {
        for (size_t col = 0; col < 4; col++)
        {
            m(row, col) = (*this)(row, 0) * other(0, col) +
                          (*this)(row, 1) * other(1, col) +
                          (*this)(row, 2) * other(2, col) +
                          (*this)(row, 3) * other(3, col);
        }
    }
    return m;
}

Tuple Matrix::operator*(const Tuple& other) const
{
    Tuple t;
    for (size_t row = 0; row < 4; row++)
    {
        t(row) = (*this)(row, 0) * other(0) + (*this)(row, 1) * other(1) + (*this)(row, 2) * other(2) + (*this)(row, 3) * other(3);
    }
    return t;
}

Matrix Matrix::transposed() const
{
    Matrix m(*this);
    for (size_t row = 0; row < 4; row++)
    {
        for (size_t col = 0; col < 4; col++)
        {
            m(row, col) = (*this)(col, row);
        }
    }
    return m;
}

Matrix& Matrix::transpose()
{
    Matrix m(*this);
    for (size_t row = 0; row < 4; row++)
    {
        for (size_t col = 0; col < 4; col++)
        {
            (*this)(row, col) = m(col, row);
        }
    }
    return *this;
}
