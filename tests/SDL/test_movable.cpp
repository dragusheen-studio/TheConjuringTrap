/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include <gtest/gtest.h>
#include "SDL/Movable/Movable.hpp"

/* ----- CLASS ----- */
class MockMovable : public sdl::Movable
{
    public:
        int transformCount = 0;
        MockMovable(sdl::Vector<double> pos = {0, 0, 0}) : sdl::Movable(pos) {}
        void onTransformChanged() override { transformCount++; }
};

/* ----- TESTs ----- */
TEST(MovableTest, DefaultPosition)
{
    sdl::Movable m;
    EXPECT_DOUBLE_EQ(m.getX(), 0.0);
    EXPECT_DOUBLE_EQ(m.getY(), 0.0);
    EXPECT_DOUBLE_EQ(m.getZ(), 0.0);
}

TEST(MovableTest, CustomPosition)
{
    sdl::Movable m(sdl::Vector<double>(10.5, -5.5, 2.0));
    EXPECT_DOUBLE_EQ(m.getX(), 10.5);
    EXPECT_DOUBLE_EQ(m.getY(), -5.5);
    EXPECT_DOUBLE_EQ(m.getZ(), 2.0);
}

/* ----- TESTs ----- */
TEST(MovableTest, SetX)
{
    MockMovable m;
    m.setX(42.0);
    EXPECT_DOUBLE_EQ(m.getX(), 42.0);
    EXPECT_EQ(m.transformCount, 1);
}

TEST(MovableTest, SetX_NoChange)
{
    MockMovable m(sdl::Vector<double>(42.0, 0, 0));
    m.setX(42.0);
    EXPECT_EQ(m.transformCount, 0);
}

TEST(MovableTest, SetY)
{
    MockMovable m;
    m.setY(99.9);
    EXPECT_DOUBLE_EQ(m.getY(), 99.9);
    EXPECT_EQ(m.transformCount, 1);
}

TEST(MovableTest, SetZ)
{
    MockMovable m;
    m.setZ(-10.0);
    EXPECT_DOUBLE_EQ(m.getZ(), -10.0);
    EXPECT_EQ(m.transformCount, 1);
}

TEST(MovableTest, SetPositionVector)
{
    MockMovable m;
    m.setPosition(sdl::Vector<double>(1.1, 2.2, 3.3));
    EXPECT_DOUBLE_EQ(m.getX(), 1.1);
    EXPECT_DOUBLE_EQ(m.getY(), 2.2);
    EXPECT_DOUBLE_EQ(m.getZ(), 3.3);
    EXPECT_EQ(m.transformCount, 1);
}

TEST(MovableTest, MoveX)
{
    MockMovable m(sdl::Vector<double>(10.0, 0, 0));
    m.moveX(5.0);
    EXPECT_DOUBLE_EQ(m.getX(), 15.0);
    EXPECT_EQ(m.transformCount, 1);
}

TEST(MovableTest, MoveY)
{
    MockMovable m(sdl::Vector<double>(0, 10.0, 0));
    m.moveY(-15.0);
    EXPECT_DOUBLE_EQ(m.getY(), -5.0);
}

TEST(MovableTest, MoveZ)
{
    MockMovable m;
    m.moveZ(3.14);
    EXPECT_DOUBLE_EQ(m.getZ(), 3.14);
}

TEST(MovableTest, MoveVector)
{
    MockMovable m(sdl::Vector<double>(10, 10, 10));
    m.move(sdl::Vector<double>(5, -5, 10));
    EXPECT_DOUBLE_EQ(m.getX(), 15);
    EXPECT_DOUBLE_EQ(m.getY(), 5);
    EXPECT_DOUBLE_EQ(m.getZ(), 20);
    EXPECT_EQ(m.transformCount, 1);
}

TEST(MovableTest, MoveVector_NoChange)
{
    MockMovable m;
    m.move(sdl::Vector<double>(0, 0, 0));
    EXPECT_EQ(m.transformCount, 0);
}
