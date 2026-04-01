/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include <gtest/gtest.h>
#include "SDL/Color/Color.hpp"

/* ----- TESTs ----- */
TEST(ColorTest, DefaultAlpha)
{
    sdl::Color c(10, 20, 30);
    EXPECT_EQ(c.r, 10);
    EXPECT_EQ(c.g, 20);
    EXPECT_EQ(c.b, 30);
    EXPECT_EQ(c.a, 255);
}

TEST(ColorTest, CustomAlpha)
{
    sdl::Color c(10, 20, 30, 100);
    EXPECT_EQ(c.a, 100);
}

TEST(ColorTest, ZeroValues)
{
    sdl::Color c(0, 0, 0, 0);
    EXPECT_EQ(c.r, 0);
    EXPECT_EQ(c.g, 0);
    EXPECT_EQ(c.b, 0);
    EXPECT_EQ(c.a, 0);
}

TEST(ColorTest, StaticBlack)
{
    EXPECT_EQ(sdl::Color::BLACK.r, 0);
    EXPECT_EQ(sdl::Color::BLACK.g, 0);
    EXPECT_EQ(sdl::Color::BLACK.b, 0);
}

TEST(ColorTest, StaticWhite)
{
    EXPECT_EQ(sdl::Color::WHITE.r, 255);
    EXPECT_EQ(sdl::Color::WHITE.g, 255);
    EXPECT_EQ(sdl::Color::WHITE.b, 255);
}

TEST(ColorTest, StaticTransparent)
{
    EXPECT_EQ(sdl::Color::TRANSPARENT.a, 0);
}

TEST(ColorTest, MultiplyEqualsHalve)
{
    sdl::Color c(100, 200, 50);
    c *= 0.5;
    EXPECT_EQ(c.r, 50);
    EXPECT_EQ(c.g, 100);
    EXPECT_EQ(c.b, 25);
}

TEST(ColorTest, MultiplyEqualsZero)
{
    sdl::Color c(255, 255, 255);
    c *= 0.0;
    EXPECT_EQ(c.r, 0);
    EXPECT_EQ(c.g, 0);
    EXPECT_EQ(c.b, 0);
}

TEST(ColorTest, MultiplyEqualsIncrease)
{
    sdl::Color c(50, 50, 50);
    c *= 2.0;
    EXPECT_EQ(c.r, 100);
    EXPECT_EQ(c.g, 100);
    EXPECT_EQ(c.b, 100);
}

TEST(ColorTest, MultiplyOperator)
{
    sdl::Color c1(100, 100, 100, 255);
    sdl::Color c2 = c1 * 0.25;
    EXPECT_EQ(c2.r, 25);
    EXPECT_EQ(c2.g, 25);
    EXPECT_EQ(c2.b, 25);
    EXPECT_EQ(c1.r, 100);
    EXPECT_EQ(c2.a, 255);
}
