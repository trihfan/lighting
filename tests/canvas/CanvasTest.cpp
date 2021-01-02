#include <gtest/gtest.h>
#include <cmath>
#include <sstream>
#include <iostream>
#include "presentation/Canvas.h"

using namespace lighting;

#define ASSERT_LINE_EQ(X, Y) std::getline(X, line); ASSERT_EQ(line, Y)

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

TEST(Canvas, PPMExport) 
{
    Canvas c(5, 3);
    c(0, 0) = color(1.5, 0, 0);
    c(2, 1) = color(0, 0.5, 0);
    c(4, 2) = color(-0.5, 0, 1);

    std::stringstream output;
    std::string line;
    ASSERT_TRUE(c.exportTo(output, "ppm"));

    // header
    ASSERT_LINE_EQ(output, "P3");
    ASSERT_LINE_EQ(output, "5 3");
    ASSERT_LINE_EQ(output, "255");

    // content
    ASSERT_LINE_EQ(output, "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ");
    ASSERT_LINE_EQ(output, "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0 ");
    ASSERT_LINE_EQ(output, "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255 ");

    // end
    ASSERT_EQ(output.str().back(), '\n');
}

TEST(Canvas, PPMSplit) 
{
    Canvas c(10, 2);
    for (size_t i = 0; i < 20; i++)
    {
        c(i) = color(1, 0.8, 0.6);
    }

    std::stringstream output;
    std::string line;
    ASSERT_TRUE(c.exportTo(output, "ppm"));

    // header
    ASSERT_LINE_EQ(output, "P3");
    ASSERT_LINE_EQ(output, "10 2");
    ASSERT_LINE_EQ(output, "255");

    // content
    ASSERT_LINE_EQ(output, "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204 ");
    ASSERT_LINE_EQ(output, "153 255 204 153 255 204 153 255 204 153 255 204 153 ");
    ASSERT_LINE_EQ(output, "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204 ");
    ASSERT_LINE_EQ(output, "153 255 204 153 255 204 153 255 204 153 255 204 153 ");
}