/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include <gtest/gtest.h>
#include "SDL/Error/Error.hpp"

/* ----- TESTs ----- */
TEST(ErrorTest, ConstructorAndWhat)
{
    sdl::Error e("Failed to load Texture");
    EXPECT_STREQ(e.what(), "Failed to load Texture");
}

TEST(ErrorTest, ConstructorAndWhere)
{
    sdl::Error e("Crash", "Texture::Texture");
    EXPECT_STREQ(e.where(), "Texture::Texture");
}

TEST(ErrorTest, DefaultWhereIsUnknown)
{
    sdl::Error e("Crash");
    EXPECT_STREQ(e.where(), "Unknown");
}

TEST(ErrorTest, EmptyStrings)
{
    sdl::Error e("", "");
    EXPECT_STREQ(e.what(), "");
    EXPECT_STREQ(e.where(), "");
}

TEST(ErrorTest, InheritsStdException)
{
    sdl::Error e("Msg");
    std::exception *stdE = &e;
    EXPECT_STREQ(stdE->what(), "Msg");
}
