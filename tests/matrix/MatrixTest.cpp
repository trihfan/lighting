#include <gtest/gtest.h>
#include <cmath>
#include "maths/Matrix.h"
#include "maths/Tuple.h"

using namespace lighting;

int main(int argc, char **argv) 
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(Matrix, Construction2x2) 
{
  Matrix m(-3, 5, 1, -2);
  ASSERT_DOUBLE_EQ(m(0, 0), -3);
  ASSERT_DOUBLE_EQ(m(0, 1), 5);
  ASSERT_DOUBLE_EQ(m(1, 0), 1);
  ASSERT_DOUBLE_EQ(m(1, 1), -2);
}

TEST(Matrix, Construction3x3) 
{
  Matrix m(-3, 5, 0, 1, -2, -7, 0, 1, 1);
  ASSERT_DOUBLE_EQ(m(0, 0), -3);
  ASSERT_DOUBLE_EQ(m(1, 1), -2);
  ASSERT_DOUBLE_EQ(m(2, 2), 1);
}

TEST(Matrix, Construction4x4) 
{
  Matrix m(1, 2, 3, 4, 5.5, 6.5, 7.5, 8.5, 9, 10, 11, 12, 13.5, 14.5, 15.5, 16.5);
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
  ASSERT_TRUE(Matrix(1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2) == Matrix(1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2));
}

TEST(Matrix, NotEquals) 
{
  ASSERT_TRUE(Matrix(1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2) != Matrix(2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2, 1));
}

TEST(Matrix, MultMatrix) 
{
  ASSERT_EQ(Matrix(1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2) * Matrix(-2, 1, 2, 3, 3, 2, 1, -1, 4, 3, 6, 5, 1, 2, 7, 8), Matrix(20, 22, 50, 48, 44, 54, 114, 108, 40, 58, 110, 102, 16, 26, 46, 42));
}

TEST(Matrix, MultTuple) 
{
  ASSERT_EQ(Matrix(1, 2, 3, 4, 2, 4, 4, 2, 8, 6, 4, 1, 0, 0, 0, 1) * Tuple(1, 2, 3, 1), Tuple(18, 24, 33, 1));
  ASSERT_EQ(Tuple(1, 2, 3, 1) * Matrix(1, 2, 3, 4, 2, 4, 4, 2, 8, 6, 4, 1, 0, 0, 0, 1), Tuple(18, 24, 33, 1));
}

TEST(Matrix, Identity) 
{
  Matrix m (0, 1, 2, 4, 1, 2, 4, 8, 2, 4, 8, 16, 4, 8, 16, 32);
  ASSERT_EQ(Matrix() * m, m);
}

TEST(Matrix, Transpose) 
{
  ASSERT_EQ(Matrix(0, 9, 3, 0, 9, 8, 0, 8, 1, 8, 5, 3, 0, 0, 5, 8).transposed(), Matrix(0, 9, 1, 0, 9, 8, 8, 0, 3, 0, 5, 5, 0, 8, 3, 8));
  ASSERT_EQ(Matrix(0, 9, 3, 0, 9, 8, 0, 8, 1, 8, 5, 3, 0, 0, 5, 8).transpose(), Matrix(0, 9, 1, 0, 9, 8, 8, 0, 3, 0, 5, 5, 0, 8, 3, 8));
  ASSERT_EQ(Matrix().transposed(), Matrix());
}