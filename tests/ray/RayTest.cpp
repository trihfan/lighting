#include <gtest/gtest.h>
#include "core/Ray.h"

using namespace lighting;

int main(int argc, char **argv) 
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(Ray, Creation) 
{
    Ray r(Tuple::Point(1, 2, 3), Tuple::Vector(4, 5, 6));
    ASSERT_EQ(r.origin(), Tuple::Point(1, 2, 3));
    ASSERT_EQ(r.direction(), Tuple::Vector(4, 5, 6));
}

TEST(Ray, Position) 
{
    Ray r(Tuple::Point(2, 3, 4), Tuple::Vector(1, 0, 0));
    ASSERT_EQ(r.position(0), Tuple::Point(2, 3, 4));
    ASSERT_EQ(r.position(1), Tuple::Point(3, 3, 4));
    ASSERT_EQ(r.position(-1), Tuple::Point(1, 3, 4));
    ASSERT_EQ(r.position(2.5), Tuple::Point(4.5, 3, 4));
}