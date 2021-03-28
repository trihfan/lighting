#include <gtest/gtest.h>
#include "core/Sphere.h"
#include "core/Ray.h"

using namespace lighting;

int main(int argc, char **argv) 
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(Sphere, IntersectionFront) 
{
  Ray r(Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1));
  Sphere s;
  std::vector<double> intersections;
  s.intersect(r, intersections);
  ASSERT_EQ(intersections.size(), 2);
  ASSERT_DOUBLE_EQ(intersections[0], 4);
  ASSERT_DOUBLE_EQ(intersections[1], 6);
}

TEST(Sphere, IntersectionTengent) 
{
  Ray r(Tuple::Point(0, 1, -5), Tuple::Vector(0, 0, 1));
  Sphere s;
  std::vector<double> intersections;
  s.intersect(r, intersections);
  ASSERT_EQ(intersections.size(), 2);
  ASSERT_DOUBLE_EQ(intersections[0], 5);
  ASSERT_DOUBLE_EQ(intersections[1], 5);
}

TEST(Sphere, IntersectionMiss) 
{
  Ray r(Tuple::Point(0, 2, -5), Tuple::Vector(0, 0, 1));
  Sphere s;
  std::vector<double> intersections;
  s.intersect(r, intersections);
  ASSERT_EQ(intersections.size(), 0);
}

TEST(Sphere, IntersectionFromInside) 
{
  Ray r(Tuple::Point(0, 0, 0), Tuple::Vector(0, 0, 1));
  Sphere s;
  std::vector<double> intersections;
  s.intersect(r, intersections);
  ASSERT_EQ(intersections.size(), 2);
  ASSERT_DOUBLE_EQ(intersections[0], -1);
  ASSERT_DOUBLE_EQ(intersections[1], 1);
}

TEST(Sphere, IntersectionBehind) 
{
  Ray r(Tuple::Point(0, 0, 5), Tuple::Vector(0, 0, 1));
  Sphere s;
  std::vector<double> intersections;
  s.intersect(r, intersections);
  ASSERT_EQ(intersections.size(), 2);
  ASSERT_DOUBLE_EQ(intersections[0], -6);
  ASSERT_DOUBLE_EQ(intersections[1], -4);
}