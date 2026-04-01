/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include <gtest/gtest.h>
#include "Raycaster/Player/Player.hpp"

/* ----- TESTs ----- */
TEST(PlayerStatsTest, DefaultValues)
{
    Raycaster::Player p(sdl::Vector<double>(0, 0));
    EXPECT_DOUBLE_EQ(p.getAngle(), 0.0);
    EXPECT_DOUBLE_EQ(p.getPitch(), 0.0);
    EXPECT_DOUBLE_EQ(p.getStamina(), 100.0);
    EXPECT_DOUBLE_EQ(p.getMaxStamina(), 100.0);
    EXPECT_DOUBLE_EQ(p.getMentalHealth(), 100.0);
    EXPECT_DOUBLE_EQ(p.getMaxMentalHealth(), 100.0);
    EXPECT_DOUBLE_EQ(p.getScaredFactor(), 0.0);
}

TEST(PlayerStatsTest, RotatePositive)
{
    Raycaster::Player p(sdl::Vector<double>(0, 0));
    p.rotate(1.0, 1.0);
    EXPECT_DOUBLE_EQ(p.getAngle(), 2.5);
}

TEST(PlayerStatsTest, RotateWrapsAroundPositive)
{
    Raycaster::Player p(sdl::Vector<double>(0, 0));
    p.rotate(1.0, 3.0);
    EXPECT_LT(p.getAngle(), 2 * M_PI);
    EXPECT_GT(p.getAngle(), 0.0);
}

TEST(PlayerStatsTest, PitchLimits)
{
    Raycaster::Player p(sdl::Vector<double>(0, 0));
    p.pitchMouse(-500);
    EXPECT_LE(p.getPitch(), 200.0);

    p.pitchMouse(1000);
    EXPECT_GE(p.getPitch(), -200.0);
}

TEST(PlayerStatsTest, ScareIncreasesFactor)
{
    Raycaster::Player p(sdl::Vector<double>(0, 0));
    p.scare(0.5);
    EXPECT_DOUBLE_EQ(p.getScaredFactor(), 0.5);
}

TEST(PlayerStatsTest, ScareDropsMentalHealth)
{
    Raycaster::Player p(sdl::Vector<double>(0, 0));
    p.scare(1.0);
    EXPECT_DOUBLE_EQ(p.getMentalHealth(), 90.0);
}

TEST(PlayerStatsTest, ScaredFactorClampsAtOne)
{
    Raycaster::Player p(sdl::Vector<double>(0, 0));
    p.scare(2.0);
    EXPECT_DOUBLE_EQ(p.getScaredFactor(), 1.0);
}

TEST(PlayerStatsTest, UsePillRestoresMentalHealth)
{
    Raycaster::Player p(sdl::Vector<double>(0, 0));
    p.inventory->gainPill();
    p.scare(1.0);
    p.scare(1.0);
    p.scare(1.0);
    p.usePill();
    EXPECT_DOUBLE_EQ(p.getMentalHealth(), 100.0);
}

TEST(PlayerStatsTest, UsePillWithoutInventoryFails)
{
    Raycaster::Player p(sdl::Vector<double>(0, 0));
    p.scare(1.0);
    p.usePill();
    EXPECT_DOUBLE_EQ(p.getMentalHealth(), 90.0);
}

TEST(PlayerStatsTest, UpdateReducesScaredFactor)
{
    Raycaster::Player p(sdl::Vector<double>(0, 0));
    p.scare(1.0);
    p.update(1.0);
    EXPECT_DOUBLE_EQ(p.getScaredFactor(), 0.8);
}

TEST(PlayerStatsTest, MentalHealthRecoversWhenIdle)
{
    Raycaster::Player p(sdl::Vector<double>(0, 0));
    p.scare(1.0);

    p.update(5.0);
    EXPECT_GT(p.getMentalHealth(), 90.0);
}
