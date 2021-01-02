#include <gtest/gtest.h>
#include <cmath>
#include <sstream>
#include <iostream>
#include "presentation/Canvas.h"

using namespace lighting;

int main(int argc, char **argv) 
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(Canvas, Creation) 
{
    Canvas c(10, 20);
    ASSERT_EQ(c.width(), 10);
    ASSERT_EQ(c.height(), 20);
    for (size_t i = 0; i < 10 * 20; i++)
    {
        ASSERT_EQ(c(i), color(0, 0, 0, 0));
    }
    for (size_t x = 0; x < 10; x++)
    {
        for (size_t y = 0; y < 20; y++)
        {
            ASSERT_EQ(c(x, y), color(0, 0, 0, 0));
        }
    }
}

TEST(Canvas, Write) 
{
    Canvas c(10, 20);
    c(2, 3) = color(1, 0, 0);
    ASSERT_EQ(c(2, 3), color(1, 0, 0));
}

TEST(Canvas, ExportHeader) 
{
    Canvas c(5, 3);
    std::stringstream output;
    ASSERT_TRUE(c.exportTo(output, "ppm"));

    std::string line;
    std::getline(output, line);
    ASSERT_EQ(line, "P3");

    std::getline(output, line);
    ASSERT_EQ(line, "5 3");

    std::getline(output, line);
    ASSERT_EQ(line, "255");
}