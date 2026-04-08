/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include <gtest/gtest.h>
#include "SDL/Render/Render.hpp"
#include "Raycaster/Item/Factory/Factory.hpp"
#include "Raycaster/Player/Player.hpp"

/* ----- CLASS ----- */
class FactoryTestFixture : public ::testing::Test
{
    protected:
        sdl::Render *render;
        Raycaster::Player *player;

        void SetUp() override
        {
            render = new sdl::Render(sdl::Vector<int>(100, 100), "Test", sdl::Color::Black, sdl::Vector<int>(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED));
            player = new Raycaster::Player(sdl::Vector<double>(0, 0));
        }
        void TearDown() override
        {
            delete render;
            delete player;
        }
};

/* ----- TESTs ----- */
TEST_F(FactoryTestFixture, FactorySingleton)
{
    auto &f1 = Raycaster::ItemFactory::get();
    auto &f2 = Raycaster::ItemFactory::get();
    EXPECT_EQ(&f1, &f2);
}

TEST_F(FactoryTestFixture, CreateKeyAddsToInventory)
{
    auto keyItem = Raycaster::ItemFactory::get().create(Raycaster::ItemFactory::KEY, *render);
    ASSERT_NE(keyItem, nullptr);

    EXPECT_FALSE(player->inventory->hasKey());
    keyItem->pickup(*player);
    EXPECT_TRUE(player->inventory->hasKey());
}

TEST_F(FactoryTestFixture, CreatePillAddsToInventory)
{
    auto pillItem = Raycaster::ItemFactory::get().create(Raycaster::ItemFactory::PILL, *render);
    ASSERT_NE(pillItem, nullptr);

    EXPECT_FALSE(player->inventory->hasPill());
    pillItem->pickup(*player);
    EXPECT_TRUE(player->inventory->hasPill());
}

TEST_F(FactoryTestFixture, CreateScreamerDropsMentalHealth)
{
    auto screamerItem = Raycaster::ItemFactory::get().create(Raycaster::ItemFactory::SCREAMER, *render);
    ASSERT_NE(screamerItem, nullptr);

    double initialMentalHealth = player->getMentalHealth();
    screamerItem->pickup(*player);
    EXPECT_LT(player->getMentalHealth(), initialMentalHealth);
}

TEST_F(FactoryTestFixture, CreateInvalidItemReturnsNull)
{
    auto invalidItem = Raycaster::ItemFactory::get().create((Raycaster::ItemFactory::Type)99, *render);
    EXPECT_EQ(invalidItem, nullptr);
}
