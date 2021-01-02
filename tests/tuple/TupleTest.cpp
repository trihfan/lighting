#include <gtest/gtest.h>
#include <cmath>
#include "maths/Tuple.h"

using namespace lighting;

int main(int argc, char **argv) 
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(Tuple, IsPoint) 
{
    Tuple a(4.3, -4.2, 3.1, 1);
    ASSERT_DOUBLE_EQ(a.x, 4.3);
    ASSERT_DOUBLE_EQ(a.y, -4.2);
    ASSERT_DOUBLE_EQ(a.z, 3.1);
    ASSERT_DOUBLE_EQ(a.w, 1);
    ASSERT_TRUE(a.isPoint());
    ASSERT_FALSE(a.isVector());
}

TEST(Tuple, IsVector) 
{
    Tuple a(4.3, -4.2, 3.1, 0);
    ASSERT_DOUBLE_EQ(a.x, 4.3);
    ASSERT_DOUBLE_EQ(a.y, -4.2);
    ASSERT_DOUBLE_EQ(a.z, 3.1);
    ASSERT_DOUBLE_EQ(a.w, 0);
    ASSERT_FALSE(a.isPoint());
    ASSERT_TRUE(a.isVector());
}

TEST(Tuple, Point) 
{
    ASSERT_EQ(point(4.3, -4.2, 3.1), Tuple(4.3, -4.2, 3.1, 1));
}

TEST(Tuple, Vector) 
{
    ASSERT_EQ(vector(4.3, -4.2, 3.1), Tuple(4.3, -4.2, 3.1, 0));
}

TEST(Tuple, Add) 
{
    ASSERT_EQ(Tuple(3, -2, 5, 1) + Tuple(-2, 3, 1, 0), Tuple(1, 1, 6, 1));
}

TEST(Tuple, Sub) 
{
    ASSERT_EQ(point(3, 2, 1) - point(5, 6, 7), vector(-2, -4, -6));
    ASSERT_EQ(point(3, 2, 1) -= point(5, 6, 7), vector(-2, -4, -6));
    ASSERT_EQ(point(3, 2, 1) - vector(5, 6, 7), point(-2, -4, -6));
    ASSERT_EQ(point(3, 2, 1) -= vector(5, 6, 7), point(-2, -4, -6));
    ASSERT_EQ(vector(3, 2, 1) - vector(5, 6, 7), vector(-2, -4, -6));
    ASSERT_EQ(vector(3, 2, 1) -= vector(5, 6, 7), vector(-2, -4, -6));
}

TEST(Tuple, Negate) 
{
    ASSERT_EQ(-Tuple(1, -2, 3, -4), Tuple(-1, 2, -3, 4));
}

TEST(Tuple, Mult) 
{
    ASSERT_EQ(Tuple(1, -2, 3, -4) * 3.5, Tuple(3.5, -7, 10.5, -14));
    ASSERT_EQ(Tuple(1, -2, 3, -4) *= 3.5, Tuple(3.5, -7, 10.5, -14));
    ASSERT_EQ(Tuple(1, -2, 3, -4) * 0.5, Tuple(0.5, -1, 1.5, -2));
    ASSERT_EQ(Tuple(1, -2, 3, -4) *= 0.5, Tuple(0.5, -1, 1.5, -2));
}

TEST(Tuple, Div) 
{
    ASSERT_EQ(Tuple(1, -2, 3, -4) / 2, Tuple(0.5, -1, 1.5, -2));
    ASSERT_EQ(Tuple(1, -2, 3, -4) /= 2, Tuple(0.5, -1, 1.5, -2));
}

TEST(Tuple, Length) 
{
    ASSERT_DOUBLE_EQ(vector(1, 0, 0).length(), 1);
    ASSERT_DOUBLE_EQ(vector(0, 1, 0).length(), 1);
    ASSERT_DOUBLE_EQ(vector(0, 0, 1).length(), 1);
    ASSERT_DOUBLE_EQ(vector(1, 2, 3).length(), std::sqrt(14));
    ASSERT_DOUBLE_EQ(vector(-1, -2, -3).length(), std::sqrt(14));
}

TEST(Tuple, Normalize) 
{
    ASSERT_EQ(vector(4, 0, 0).normalized(), vector(1, 0, 0));
    Tuple a = vector(4, 0, 0); a.normalize(); ASSERT_EQ(a, vector(1, 0, 0));
    ASSERT_EQ(vector(1, 2, 3).normalized(), vector(1 / std::sqrt(14), 2 / std::sqrt(14), 3 / std::sqrt(14)));
    Tuple b = vector(1, 2, 3); b.normalize(); ASSERT_EQ(b, vector(1 / std::sqrt(14), 2 / std::sqrt(14), 3 / std::sqrt(14)));
}

TEST(Tuple, Dot) 
{   
    ASSERT_DOUBLE_EQ(dot(vector(1, 2, 3), vector(2, 3, 4)), 20);
}

TEST(Tuple, Cross) 
{   
    ASSERT_EQ(cross(vector(1, 2, 3), vector(2, 3, 4)), vector(-1, 2, -1));
    ASSERT_EQ(cross(vector(2, 3, 4), vector(1, 2, 3)), vector(1, -2, 1));
}