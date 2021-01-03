#include "Matrix.h"

using namespace lighting;

template <typename MatrixA, typename MatrixB>
void submatrixImpl(const MatrixA& matrixA, MatrixB& matrixB, size_t rowToRemove, size_t colToRemove)
{
    size_t currentRow = 0, currentCol = 0;
    for (size_t row = 0; row < matrixA.rowCount(); row++)
    {
        if (row != rowToRemove)
        {
            currentCol = 0;
            for (size_t col = 0; col < matrixA.colCount(); col++)
            {
                if (col != colToRemove)
                {
                    matrixB(currentRow, currentCol) = matrixA(row, col);
                    currentCol++;
                }
            }
            currentRow++;
        }
    }
}

Matrix2x2::Matrix2x2() : Matrix<2, 2>({ 1, 0, 0, 1 })
{
}

Matrix2x2::Matrix2x2(double a11, double a12, double a21, double a22) : Matrix<2, 2>({ a11, a12, a21, a22 })
{
}

double Matrix2x2::determinant() const
{
    return data[0] * data[3] - data[1] * data[2];
}

Matrix3x3::Matrix3x3() : Matrix<3, 3>({ 1, 0, 0, 0, 1, 0, 0, 0, 1 })
{
}

Matrix3x3::Matrix3x3(double a11, double a12, double a13, double a21, double a22, double a23, double a31, double a32, double a33) : Matrix<3, 3>({ a11, a12, a13, a21, a22, a23, a31, a32, a33 })
{
}

Matrix2x2 Matrix3x3::submatrix(size_t rowToRemove, size_t colToRemove) const
{
    Matrix2x2 sub;
    submatrixImpl(*this, sub, rowToRemove, colToRemove);
    return sub;
}

double Matrix3x3::minor(size_t rowToRemove, size_t colToRemove) const
{
    return submatrix(rowToRemove, colToRemove).determinant();
}

double Matrix3x3::cofactor(size_t rowToRemove, size_t colToRemove) const
{
    double m = minor(rowToRemove, colToRemove);
    return (rowToRemove + colToRemove) % 2 == 0 ? m : -m;
}

double Matrix3x3::determinant() const
{
    return data[0] * cofactor(0, 0) + data[1] * cofactor(0, 1) + data[2] * cofactor(0, 2);
}

Matrix4x4::Matrix4x4() : Matrix<4, 4>({ 1, 0, 0, 0,  0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 })
{
}

Matrix4x4::Matrix4x4(double a11, double a12, double a13, double a14, double a21, double a22, double a23, double a24,
                     double a31, double a32, double a33, double a34, double a41, double a42, double a43, double a44) : Matrix<4, 4>({ a11, a12, a13, a14, a21, a22, a23, a24, a31, a32, a33, a34, a41, a42, a43, a44 })
{
}

Matrix3x3 Matrix4x4::submatrix(size_t rowToRemove, size_t colToRemove) const
{
    Matrix3x3 sub;
    submatrixImpl(*this, sub, rowToRemove, colToRemove);
    return sub;
}

double Matrix4x4::minor(size_t rowToRemove, size_t colToRemove) const
{
    return submatrix(rowToRemove, colToRemove).determinant();
}

double Matrix4x4::cofactor(size_t rowToRemove, size_t colToRemove) const
{
    double m = minor(rowToRemove, colToRemove);
    return (rowToRemove + colToRemove) % 2 == 0 ? m : -m;
}

double Matrix4x4::determinant() const
{
    return data[0] * cofactor(0, 0) + data[1] * cofactor(0, 1) + data[2] * cofactor(0, 2) + data[3] * cofactor(0, 3);
}

bool Matrix4x4::isInvertible() const
{
    return determinant() != 0;
}

Matrix4x4& Matrix4x4::inverse()
{
    *this = inverted();
    return *this;
}

Matrix4x4 Matrix4x4::inverted() const
{
    Matrix4x4 invertedMatrix;
    double det = determinant();
    if (det != 0)
    {
        for (size_t row = 0; row < rowCount(); row++)
        {
            for (size_t col = 0; col < colCount(); col++)
            {
                double c = cofactor(row, col);
                invertedMatrix(col, row) = c / det;
            }
        }
    }
    return invertedMatrix;
}

Matrix4x4 Matrix4x4::translation(const Tuple& value)
{
    return translation(value.x(), value.y(), value.z());
}

Matrix4x4 Matrix4x4::translation(double x, double y, double z)
{
    Matrix4x4 m;
    m(0, 3) = x;
    m(1, 3) = y;
    m(2, 3) = z;
    return m;
}

Matrix4x4 Matrix4x4::scale(const Tuple& value)
{
    return scale(value.x(), value.y(), value.z());
}

Matrix4x4 Matrix4x4::scale(double x, double y, double z)
{
    Matrix4x4 m;
    m(0, 0) = x;
    m(1, 1) = y;
    m(2, 2) = z;
    return m;
}

Matrix4x4 Matrix4x4::rotateX(double radians)
{
    Matrix4x4 m;
    m(1, 1) = std::cos(radians);
    m(1, 2) = -std::sin(radians);
    m(2, 1) = std::sin(radians);
    m(2, 2) = std::cos(radians);
    return m;
}

Matrix4x4 Matrix4x4::rotateY(double radians)
{
    Matrix4x4 m;
    m(0, 0) = std::cos(radians);
    m(0, 2) = std::sin(radians);
    m(2, 0) = -std::sin(radians);
    m(2, 2) = std::cos(radians);
    return m;
}

Matrix4x4 Matrix4x4::rotateZ(double radians)
{
    Matrix4x4 m;
    m(0, 0) = std::cos(radians);
    m(0, 1) = -std::sin(radians);
    m(1, 0) = std::sin(radians);
    m(1, 1) = std::cos(radians);
    return m;
}

Matrix4x4 Matrix4x4::shearing(double xy, double xz, double yx, double yz, double zx, double zy)
{
    Matrix4x4 m;
    m(0, 1) = xy;
    m(0, 2) = xz;
    m(1, 0) = yx;
    m(1, 2) = yz;
    m(2, 0) = zx;
    m(2, 10) = zy;
    return m;
}