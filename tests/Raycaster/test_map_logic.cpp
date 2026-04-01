/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include <fstream>
#include <gtest/gtest.h>
#include "SDL/Render/Render.hpp"
#include "Raycaster/Map/Map.hpp"

/* ----- CLASS ----- */
class MapTestFixture : public ::testing::Test
{
    protected:
        sdl::Render *render;
        const char *testMapPath = "test_map.txt";

        void SetUp() override
        {
            render = new sdl::Render(sdl::Vector<int>(100, 100), "Test", sdl::Color::BLACK, sdl::Vector<int>(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED));

            std::ofstream mapFile(testMapPath);
            mapFile << "XXXX\n";
            mapFile << "XP X\n";
            mapFile << "XC X\n";
            mapFile << "XXXX\n";
            mapFile.close();
        }

        void TearDown() override
        {
            remove(testMapPath);
            delete render;
        }
};

/* ----- TESTs ----- */
TEST_F(MapTestFixture, LoadDimensions)
{
    Raycaster::Map map(64, testMapPath, *render);
    sdl::Vector<int> size = map.getSize();
    EXPECT_EQ(size.x, 4);
    EXPECT_EQ(size.y, 4);
}

TEST_F(MapTestFixture, CellSizeSaved)
{
    Raycaster::Map map(32, testMapPath, *render);
    EXPECT_EQ(map.getCellSize(), 32);
}

TEST_F(MapTestFixture, PlayerSpawnParsed)
{
    Raycaster::Map map(64, testMapPath, *render);
    sdl::Vector<double> spawn = map.getPlayerStart();
    EXPECT_DOUBLE_EQ(spawn.x, 96.0);
    EXPECT_DOUBLE_EQ(spawn.y, 96.0);
}

TEST_F(MapTestFixture, EntitySpawnsParsed)
{
    Raycaster::Map map(64, testMapPath, *render);
    const auto &spawns = map.getEntitySpawns();

    ASSERT_EQ(spawns.size(), 1);
    EXPECT_EQ(spawns[0].type, Raycaster::CellType::CHEST);
    EXPECT_DOUBLE_EQ(spawns[0].position.x, 96.0);
    EXPECT_DOUBLE_EQ(spawns[0].position.y, 160.0);
}

TEST_F(MapTestFixture, CollisionOutOfBoundsReturnsFalse)
{
    Raycaster::Map map(64, testMapPath, *render);
    EXPECT_FALSE(map.isSolidCellAt(sdl::Vector<double>(-10, -10)));
    EXPECT_FALSE(map.isSolidCellAt(sdl::Vector<double>(9999, 9999)));
}

TEST_F(MapTestFixture, CollisionOnWallReturnsTrue)
{
    Raycaster::Map map(64, testMapPath, *render);
    EXPECT_TRUE(map.isSolidCellAt(sdl::Vector<double>(10, 10)));
}

TEST_F(MapTestFixture, CollisionOnEmptyReturnsFalse)
{
    Raycaster::Map map(64, testMapPath, *render);
    EXPECT_FALSE(map.isSolidCellAt(sdl::Vector<double>(96, 96)));
}

TEST_F(MapTestFixture, CollisionOnChestReturnsFalse)
{
    Raycaster::Map map(64, testMapPath, *render);
    EXPECT_FALSE(map.isSolidCellAt(sdl::Vector<double>(96, 160)));
}
