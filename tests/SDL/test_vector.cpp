/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include <gtest/gtest.h>
#include "SDL/Vector/Vector.hpp"

/* ----- TESTs ----- */
TEST(VectorIntTest, DefaultConstructor)
{
    sdl::Vector<int> v;
    EXPECT_EQ(v.x, 0);
    EXPECT_EQ(v.y, 0);
    EXPECT_EQ(v.z, 0);
}

TEST(VectorIntTest, PartialConstructor)
{
    sdl::Vector<int> v(5);
    EXPECT_EQ(v.x, 5);
    EXPECT_EQ(v.y, 0);
    EXPECT_EQ(v.z, 0);
}

TEST(VectorIntTest, FullConstructor)
{
    sdl::Vector<int> v(1, 2, 3);
    EXPECT_EQ(v.x, 1);
    EXPECT_EQ(v.y, 2);
    EXPECT_EQ(v.z, 3);
}

TEST(VectorIntTest, NegativeValues)
{
    sdl::Vector<int> v(-10, -20, -30);
    EXPECT_EQ(v.x, -10);
    EXPECT_EQ(v.y, -20);
    EXPECT_EQ(v.z, -30);
}

TEST(VectorDoubleTest, DefaultConstructor)
{
    sdl::Vector<double> v;
    EXPECT_DOUBLE_EQ(v.x, 0.0);
    EXPECT_DOUBLE_EQ(v.y, 0.0);
    EXPECT_DOUBLE_EQ(v.z, 0.0);
}

TEST(VectorDoubleTest, FullConstructor)
{
    sdl::Vector<double> v(1.5, 2.5, 3.5);
    EXPECT_DOUBLE_EQ(v.x, 1.5);
    EXPECT_DOUBLE_EQ(v.y, 2.5);
    EXPECT_DOUBLE_EQ(v.z, 3.5);
}

TEST(VectorIntTest, PlusEqualsPositive)
{
    sdl::Vector<int> v1(10, 10, 10);
    v1 += sdl::Vector<int>(5, 5, 5);
    EXPECT_EQ(v1.x, 15);
    EXPECT_EQ(v1.y, 15);
    EXPECT_EQ(v1.z, 15);
}

TEST(VectorIntTest, PlusEqualsNegative)
{
    sdl::Vector<int> v1(10, 10, 10);
    v1 += sdl::Vector<int>(-15, -5, 0);
    EXPECT_EQ(v1.x, -5);
    EXPECT_EQ(v1.y, 5);
    EXPECT_EQ(v1.z, 10);
}

TEST(VectorDoubleTest, PlusEqualsDouble)
{
    sdl::Vector<double> v1(1.5, 1.5, 1.5);
    v1 += sdl::Vector<double>(1.5, 0.5, -1.5);
    EXPECT_DOUBLE_EQ(v1.x, 3.0);
    EXPECT_DOUBLE_EQ(v1.y, 2.0);
    EXPECT_DOUBLE_EQ(v1.z, 0.0);
}

TEST(VectorIntTest, PlusOperator)
{
    sdl::Vector<int> v1(1, 2, 3);
    sdl::Vector<int> v2 = v1 + sdl::Vector<int>(4, 5, 6);
    EXPECT_EQ(v2.x, 5);
    EXPECT_EQ(v2.y, 7);
    EXPECT_EQ(v2.z, 9);
    EXPECT_EQ(v1.x, 1);
    EXPECT_EQ(v1.y, 2);
    EXPECT_EQ(v1.z, 3);
}

TEST(VectorDoubleTest, PlusOperatorDouble)
{
    sdl::Vector<double> v1(1.1, 2.2, 3.3);
    sdl::Vector<double> v2 = v1 + sdl::Vector<double>(1.1, 1.1, 1.1);
    EXPECT_DOUBLE_EQ(v2.x, 2.2);
    EXPECT_DOUBLE_EQ(v2.y, 3.3);
    EXPECT_DOUBLE_EQ(v2.z, 4.4);
}

TEST(VectorIntTest, EqualityTrue)
{
    EXPECT_TRUE(sdl::Vector<int>(5, 5, 5) == sdl::Vector<int>(5, 5, 5));
}

TEST(VectorIntTest, EqualityFalseX)
{
    EXPECT_FALSE(sdl::Vector<int>(4, 5, 5) == sdl::Vector<int>(5, 5, 5));
}

TEST(VectorIntTest, EqualityFalseY)
{
    EXPECT_FALSE(sdl::Vector<int>(5, 4, 5) == sdl::Vector<int>(5, 5, 5));
}

TEST(VectorIntTest, EqualityFalseZ)
{
    EXPECT_FALSE(sdl::Vector<int>(5, 5, 4) == sdl::Vector<int>(5, 5, 5));
}

TEST(VectorDoubleTest, DistanceZero)
{
    sdl::Vector<double> p1(5.0, 5.0, 5.0);
    EXPECT_DOUBLE_EQ(p1.dist(p1), 0.0);
}

TEST(VectorDoubleTest, DistanceXAxis)
{
    sdl::Vector<double> p1(0.0, 0.0, 0.0);
    sdl::Vector<double> p2(10.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(p1.dist(p2), 10.0);
}

TEST(VectorDoubleTest, DistanceYAxis)
{
    sdl::Vector<double> p1(0.0, 5.0, 0.0);
    sdl::Vector<double> p2(0.0, -5.0, 0.0);
    EXPECT_DOUBLE_EQ(p1.dist(p2), 10.0);
}

TEST(VectorDoubleTest, DistancePythagore)
{
    sdl::Vector<double> p1(0.0, 0.0, 0.0);
    sdl::Vector<double> p2(3.0, 4.0, 0.0);
    EXPECT_DOUBLE_EQ(p1.dist(p2), 5.0);
}

TEST(VectorDoubleTest, Distance3D)
{
    sdl::Vector<double> p1(0.0, 0.0, 0.0);
    sdl::Vector<double> p2(2.0, 3.0, 6.0);
    EXPECT_DOUBLE_EQ(p1.dist(p2), 7.0);
}
