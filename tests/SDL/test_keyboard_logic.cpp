/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include <gtest/gtest.h>
#include "SDL/Keyboard/Keyboard.hpp"

/* ----- TESTs ----- */
TEST(KeyboardTest, InitializationNoCrash)
{
    EXPECT_NO_THROW({
        sdl::Keyboard kb;
    });
}

TEST(KeyboardTest, BindPressedDoesNotCrash)
{
    sdl::Keyboard kb;
    kb.bindOnPressed(SDL_SCANCODE_W, [](double dt) {});
    SUCCEED();
}

TEST(KeyboardTest, BindReleasedDoesNotCrash)
{
    sdl::Keyboard kb;
    kb.bindOnReleased(SDL_SCANCODE_E, [](double dt) {});
    SUCCEED();
}

TEST(KeyboardTest, UnbindPressed)
{
    sdl::Keyboard kb;
    kb.bindOnPressed(SDL_SCANCODE_W, [](double dt) {});
    EXPECT_NO_THROW({
        kb.unbindOnPressed(SDL_SCANCODE_W);
    });
}

TEST(KeyboardTest, ClearBindings)
{
    sdl::Keyboard kb;
    kb.bindOnPressed(SDL_SCANCODE_W, [](double dt) {});
    kb.bindOnReleased(SDL_SCANCODE_E, [](double dt) {});
    EXPECT_NO_THROW({
        kb.clear();
    });
}
