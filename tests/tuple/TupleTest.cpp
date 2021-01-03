#include <gtest/gtest.h>
#include "maths/Tuple.h"
#include "maths/Color.h"

using namespace lighting;

int main(int argc, char **argv) 
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(Tuple, IsPoint) 
{
    Tuple a(4.3, -4.2, 3.1, 1);
    ASSERT_DOUBLE_EQ(a.x(), 4.3);
    ASSERT_DOUBLE_EQ(a.y(), -4.2);
    ASSERT_DOUBLE_EQ(a.z(), 3.1);
    ASSERT_DOUBLE_EQ(a.w(), 1);
    ASSERT_TRUE(a.isPoint());
    ASSERT_FALSE(a.isVector());
}

TEST(Tuple, IsVector) 
{
    Tuple a(4.3, -4.2, 3.1, 0);
    ASSERT_DOUBLE_EQ(a.x(), 4.3);
    ASSERT_DOUBLE_EQ(a.y(), -4.2);
    ASSERT_DOUBLE_EQ(a.z(), 3.1);
    ASSERT_DOUBLE_EQ(a.w(), 0);
    ASSERT_FALSE(a.isPoint());
    ASSERT_TRUE(a.isVector());
}

TEST(Tuple, Point) 
{
    ASSERT_EQ(Tuple::Point(4.3, -4.2, 3.1), Tuple(4.3, -4.2, 3.1, 1));
}

TEST(Tuple, Vector) 
{
    ASSERT_EQ(Tuple::Vector(4.3, -4.2, 3.1), Tuple(4.3, -4.2, 3.1, 0));
}

TEST(Tuple, Color) 
{
    ASSERT_EQ(Color(-0.5, 0.4, 1.7), Tuple(-0.5, 0.4, 1.7, 1));
    ASSERT_DOUBLE_EQ(Color(-0.5, 0.4, 1.7).r(), -0.5);
    ASSERT_DOUBLE_EQ(Color(-0.5, 0.4, 1.7).g(), 0.4);
    ASSERT_DOUBLE_EQ(Color(-0.5, 0.4, 1.7).b(), 1.7);
    ASSERT_DOUBLE_EQ(Color(-0.5, 0.4, 1.7).a(), 1);
}

TEST(Tuple, Add) 
{
    ASSERT_EQ(Tuple(3, -2, 5, 1) + Tuple(-2, 3, 1, 0), Tuple(1, 1, 6, 1));
}

TEST(Tuple, Sub) 
{
    ASSERT_EQ(Tuple::Point(3, 2, 1) - Tuple::Point(5, 6, 7), Tuple::Vector(-2, -4, -6));
    ASSERT_EQ(Tuple::Point(3, 2, 1) -= Tuple::Point(5, 6, 7), Tuple::Vector(-2, -4, -6));
    ASSERT_EQ(Tuple::Point(3, 2, 1) - Tuple::Vector(5, 6, 7), Tuple::Point(-2, -4, -6));
    ASSERT_EQ(Tuple::Point(3, 2, 1) -= Tuple::Vector(5, 6, 7), Tuple::Point(-2, -4, -6));
    ASSERT_EQ(Tuple::Point(3, 2, 1) - Tuple::Vector(5, 6, 7), Tuple::Point(-2, -4, -6));
    ASSERT_EQ(Tuple::Point(3, 2, 1) -= Tuple::Vector(5, 6, 7), Tuple::Point(-2, -4, -6));
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
    ASSERT_EQ(Tuple(1, -2, 3, -4) * Tuple(1, -2, 3, -4), Tuple(1, 4, 9, 16));
    ASSERT_EQ(Tuple(1, -2, 3, -4) *= Tuple(1, -2, 3, -4), Tuple(1, 4, 9, 16));
}

TEST(Tuple, Div) 
{
    ASSERT_EQ(Tuple(1, -2, 3, -4) / 2, Tuple(0.5, -1, 1.5, -2));
    ASSERT_EQ(Tuple(1, -2, 3, -4) /= 2, Tuple(0.5, -1, 1.5, -2));
}

TEST(Tuple, Length) 
{
    ASSERT_DOUBLE_EQ(Tuple::Vector(1, 0, 0).length(), 1);
    ASSERT_DOUBLE_EQ(Tuple::Vector(0, 1, 0).length(), 1);
    ASSERT_DOUBLE_EQ(Tuple::Vector(0, 0, 1).length(), 1);
    ASSERT_DOUBLE_EQ(Tuple::Vector(1, 2, 3).length(), std::sqrt(14));
    ASSERT_DOUBLE_EQ(Tuple::Vector(-1, -2, -3).length(), std::sqrt(14));
}

TEST(Tuple, Normalize) 
{
    ASSERT_EQ(Tuple::Vector(4, 0, 0).normalized(), Tuple::Vector(1, 0, 0));
    Tuple a = Tuple::Vector(4, 0, 0); a.normalize(); ASSERT_EQ(a, Tuple::Vector(1, 0, 0));
    ASSERT_EQ(Tuple::Vector(1, 2, 3).normalized(), Tuple::Vector(1 / std::sqrt(14), 2 / std::sqrt(14), 3 / std::sqrt(14)));
    Tuple b = Tuple::Vector(1, 2, 3); b.normalize(); ASSERT_EQ(b, Tuple::Vector(1 / std::sqrt(14), 2 / std::sqrt(14), 3 / std::sqrt(14)));
}

TEST(Tuple, Dot) 
{   
    ASSERT_DOUBLE_EQ(dot(Tuple::Vector(1, 2, 3), Tuple::Vector(2, 3, 4)), 20);
}

TEST(Tuple, Cross) 
{   
    ASSERT_EQ(cross(Tuple::Vector(1, 2, 3), Tuple::Vector(2, 3, 4)), Tuple::Vector(-1, 2, -1));
    ASSERT_EQ(cross(Tuple::Vector(2, 3, 4), Tuple::Vector(1, 2, 3)), Tuple::Vector(1, -2, 1));
}

TEST(Tuple, Colors) 
{   
    ASSERT_EQ(Color(0.9, 0.6, 0.75) + Color(0.7, 0.1, 0.25), Tuple(1.6, 0.7, 1.0, 2));
    ASSERT_EQ(Color(0.9, 0.6, 0.75) - Color(0.7, 0.1, 0.25), Tuple(0.2, 0.5, 0.5, 0));
    ASSERT_EQ(Color(0.2, 0.3, 0.4) * 2, Tuple(0.4, 0.6, 0.8, 2));
    ASSERT_EQ(Color(1, 0.2, 0.4) * Color(0.9, 1, 0.1), Tuple(0.9, 0.2, 0.04, 1));
}