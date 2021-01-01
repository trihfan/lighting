#include <gtest/gtest.h>
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
    Tuple a = point(4.3, -4.2, 3.1);
    ASSERT_EQ(a, Tuple(4.3, -4.2, 3.1, 1));
}

TEST(Tuple, Vector) 
{
    Tuple a = vector(4.3, -4.2, 3.1);
    ASSERT_EQ(a, Tuple(4.3, -4.2, 3.1, 0));
}