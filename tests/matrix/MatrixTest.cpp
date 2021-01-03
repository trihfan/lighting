#include <gtest/gtest.h>
#include <cmath>
#include "maths/Matrix.h"

using namespace lighting;

int main(int argc, char **argv) 
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(Matrix, Construction2x2) 
{
  Matrix2x2 m(-3, 5, 1, -2);
  ASSERT_DOUBLE_EQ(m(0, 0), -3);
  ASSERT_DOUBLE_EQ(m(0, 1), 5);
  ASSERT_DOUBLE_EQ(m(1, 0), 1);
  ASSERT_DOUBLE_EQ(m(1, 1), -2);
}

TEST(Matrix, Construction3x3) 
{
  Matrix3x3 m(-3, 5, 0, 1, -2, -7, 0, 1, 1);
  ASSERT_DOUBLE_EQ(m(0, 0), -3);
  ASSERT_DOUBLE_EQ(m(1, 1), -2);
  ASSERT_DOUBLE_EQ(m(2, 2), 1);
}

TEST(Matrix, Construction4x4) 
{
  Matrix4x4 m(1, 2, 3, 4, 5.5, 6.5, 7.5, 8.5, 9, 10, 11, 12, 13.5, 14.5, 15.5, 16.5);
  ASSERT_DOUBLE_EQ(m(0, 0), 1);
  ASSERT_DOUBLE_EQ(m(0, 3), 4);
  ASSERT_DOUBLE_EQ(m(1, 0), 5.5);
  ASSERT_DOUBLE_EQ(m(1, 2), 7.5);
  ASSERT_DOUBLE_EQ(m(2, 2), 11);
  ASSERT_DOUBLE_EQ(m(3, 0), 13.5);
  ASSERT_DOUBLE_EQ(m(3, 2), 15.5);
}

TEST(Matrix, Equals) 
{
  ASSERT_TRUE(Matrix4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2) == Matrix4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2));
}

TEST(Matrix, NotEquals) 
{
  ASSERT_TRUE(Matrix4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2) != Matrix4x4(2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2, 1));
}

TEST(Matrix, MultMatrix) 
{
  ASSERT_EQ(Matrix4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2) * Matrix4x4(-2, 1, 2, 3, 3, 2, 1, -1, 4, 3, 6, 5, 1, 2, 7, 8), Matrix4x4(20, 22, 50, 48, 44, 54, 114, 108, 40, 58, 110, 102, 16, 26, 46, 42));
}

TEST(Matrix, MultTuple) 
{
  ASSERT_EQ(Matrix4x4(1, 2, 3, 4, 2, 4, 4, 2, 8, 6, 4, 1, 0, 0, 0, 1) * Tuple(1, 2, 3, 1), Tuple(18, 24, 33, 1));
  ASSERT_EQ(Tuple(1, 2, 3, 1) * Matrix4x4(1, 2, 3, 4, 2, 4, 4, 2, 8, 6, 4, 1, 0, 0, 0, 1), Tuple(18, 24, 33, 1));
}

TEST(Matrix, Identity) 
{
  Matrix4x4 m (0, 1, 2, 4, 1, 2, 4, 8, 2, 4, 8, 16, 4, 8, 16, 32);
  ASSERT_EQ(Matrix4x4() * m, m);
}

TEST(Matrix, Transpose) 
{
  ASSERT_EQ(Matrix4x4(0, 9, 3, 0, 9, 8, 0, 8, 1, 8, 5, 3, 0, 0, 5, 8).transposed(), Matrix4x4(0, 9, 1, 0, 9, 8, 8, 0, 3, 0, 5, 5, 0, 8, 3, 8));
  ASSERT_EQ(Matrix4x4(0, 9, 3, 0, 9, 8, 0, 8, 1, 8, 5, 3, 0, 0, 5, 8).transpose(), Matrix4x4(0, 9, 1, 0, 9, 8, 8, 0, 3, 0, 5, 5, 0, 8, 3, 8));
  ASSERT_EQ(Matrix4x4().transposed(), Matrix4x4());
}

TEST(Matrix, Determinant2x2) 
{
  ASSERT_DOUBLE_EQ(Matrix2x2(1, 5, -3, 2).determinant(),  17);
}

TEST(Matrix, Submatrix3x3) 
{
  ASSERT_EQ(Matrix3x3(1, 5, 0, -3, 2, 7, 0, 6, -3).submatrix(0, 2), Matrix2x2(-3, 2, 0, 6));
}

TEST(Matrix, Submatrix4x4) 
{
  ASSERT_EQ(Matrix4x4(-6, 1, 1, 6, -8, 5, 8, 6, -1, 0, 8, 2, -7, 1, -1, 1).submatrix(2, 1), Matrix3x3(-6, 1, 6, -8, 8, 6, -7, -1, 1));
}

TEST(Matrix, Minor3x3) 
{
  Matrix3x3 m(3, 5, 0, 2, -1, -7, 6, -1, 5);
  ASSERT_DOUBLE_EQ(m.submatrix(1, 0).determinant(), 25);
  ASSERT_DOUBLE_EQ(m.minor(1, 0), 25);
}

TEST(Matrix, Cofactor3x3) 
{
  Matrix3x3 m(3, 5, 0, 2, -1, -7, 6, -1, 5);
  ASSERT_DOUBLE_EQ(m.minor(0, 0), -12);
  ASSERT_DOUBLE_EQ(m.cofactor(0, 0), -12);
  ASSERT_DOUBLE_EQ(m.minor(1, 0), 25);
  ASSERT_DOUBLE_EQ(m.cofactor(1, 0), -25);
}

TEST(Matrix, Determinant3x3) 
{
  Matrix3x3 m(1, 2, 6, -5, 8, -4, 2, 6, 4);
  ASSERT_DOUBLE_EQ(m.cofactor(0, 0), 56);
  ASSERT_DOUBLE_EQ(m.cofactor(0, 1), 12);
  ASSERT_DOUBLE_EQ(m.cofactor(0, 2), -46);
  ASSERT_DOUBLE_EQ(m.determinant(), -196);
}

TEST(Matrix, Determinant4x4) 
{
  Matrix4x4 m(-2, -8, 3, 5, -3, 1, 7, 3, 1, 2, -9, 6, -6, 7, 7, -9);
  ASSERT_DOUBLE_EQ(m.cofactor(0, 0), 690);
  ASSERT_DOUBLE_EQ(m.cofactor(0, 1), 447);
  ASSERT_DOUBLE_EQ(m.cofactor(0, 2), 210);
  ASSERT_DOUBLE_EQ(m.cofactor(0, 3), 51);
  ASSERT_DOUBLE_EQ(m.determinant(), -4071);
}

TEST(Matrix, Invertible4x4) 
{
  Matrix4x4 m(6, 4, 4, 4, 5, 5, 7, 6, 4, -9, 3, -7, 9, 1, 7, -6);
  ASSERT_TRUE(m.isInvertible());
}

TEST(Matrix, NotInvertible4x4) 
{
  Matrix4x4 m(-4, 2, -2, -3, 9, 6, 2, 6, 0, -5, 1, -5, 0, 0, 0, 0);
  ASSERT_FALSE(m.isInvertible());
}

TEST(Matrix, Inverse1) 
{
  Matrix4x4 m(-5, 2, 6, -8, 1, -5, 1, 8, 7, 7, -6, -7, 1, -3, 7, 4);
  ASSERT_TRUE(m.isInvertible());
  Matrix4x4 inverse = m.inverted();
  ASSERT_DOUBLE_EQ(m.determinant(), 532);
  ASSERT_DOUBLE_EQ(m.cofactor(2, 3), -160);
  ASSERT_DOUBLE_EQ(inverse(3, 2), -160. / 532);
  ASSERT_DOUBLE_EQ(m.cofactor(3, 2), 105);
  ASSERT_DOUBLE_EQ(inverse(2, 3), 105. / 532);
  ASSERT_EQ(inverse, Matrix4x4(0.2180451128, 0.4511278195, 0.2406015038, -0.04511278195, 
                               -0.8082706767, -1.456766917, -0.4436090226, 0.5206766917, 
                               -0.07894736842, -0.2236842105, -0.05263157895, 0.1973684211, 
                               -0.522556391, -0.8139097744, -0.3007518797, 0.3063909774));  
}

TEST(Matrix, Inverse2) 
{
  Matrix4x4 m(8, -5, 9, 2, 7, 5, 6, 1, -6, 0, 9, 6, -3, 0, -9, -4);
  Matrix4x4 inverse = m.inverted();
  ASSERT_EQ(inverse, Matrix4x4(-0.1538461538, -0.1538461538, -0.2820512821, -0.5384615385,
                               -0.07692307692, 0.1230769231, 0.02564102564, 0.03076923077,
                               0.358974359, 0.358974359, 0.4358974359, 0.9230769231,
                               -0.6923076923, -0.6923076923, -0.7692307692, -1.923076923));  
}

TEST(Matrix, Inverse3) 
{
  Matrix4x4 m(9, 3, 0, 9, -5, -2, -6, -3, -4, 9, 6, 4, -7, 6, 6, 2);
  Matrix4x4 inverse = m.inverted();
  ASSERT_EQ(inverse, Matrix4x4(-0.04074074074, -0.07777777778, 0.1444444444, -0.2222222222,
                               -0.07777777778, 0.03333333333, 0.3666666667, -0.3333333333,
                               -0.02901234568, -0.1462962963, -0.1092592593, 0.1296296296,
                               0.1777777778, 0.06666666667, -0.2666666667, 0.3333333333));  
}

TEST(Matrix, Inverse4) 
{
  Matrix4x4 m1(3, -9, 7, 3, 3, -8, 2, -9, -4, 4, 4, 1, -6, 5, -1, 1);
  Matrix4x4 m2(8, 2, 2, 2, 3, -1, 7, 0, 7, 0, 5, 4, 6, -2, 0, 5);
  ASSERT_EQ(m1 * m2 * m2.inverted(), m1);
}