/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include <gtest/gtest.h>
#include "Raycaster/Player/Inventory/Inventory.hpp"

/* ----- TESTs ----- */
TEST(InventoryTest, InitialStateEmpty)
{
    Raycaster::Inventory inv;
    EXPECT_FALSE(inv.hasKey());
    EXPECT_FALSE(inv.hasPill());
}

TEST(InventoryTest, GainSingleKey)
{
    Raycaster::Inventory inv;
    inv.gainKey();
    EXPECT_TRUE(inv.hasKey());
}

TEST(InventoryTest, GainMultipleKeys)
{
    Raycaster::Inventory inv;
    inv.gainKey();
    inv.gainKey();
    EXPECT_TRUE(inv.hasKey());
}

TEST(InventoryTest, UseKeyReducesCount)
{
    Raycaster::Inventory inv;
    inv.gainKey();
    inv.gainKey();
    inv.useKey();
    EXPECT_TRUE(inv.hasKey());
    inv.useKey();
    EXPECT_FALSE(inv.hasKey());
}

TEST(InventoryTest, UseKeyUnderflowPrevention)
{
    Raycaster::Inventory inv;
    inv.useKey();
    EXPECT_FALSE(inv.hasKey());
}

TEST(InventoryTest, GainSinglePill)
{
    Raycaster::Inventory inv;
    inv.gainPill();
    EXPECT_TRUE(inv.hasPill());
}

TEST(InventoryTest, GainMultiplePills)
{
    Raycaster::Inventory inv;
    inv.gainPill();
    inv.gainPill();
    inv.gainPill();
    EXPECT_TRUE(inv.hasPill());
}

TEST(InventoryTest, UsePillReducesCount)
{
    Raycaster::Inventory inv;
    inv.gainPill();
    inv.usePill();
    EXPECT_FALSE(inv.hasPill());
}

TEST(InventoryTest, UsePillUnderflowPrevention)
{
    Raycaster::Inventory inv;
    inv.usePill();
    EXPECT_FALSE(inv.hasPill());
}
