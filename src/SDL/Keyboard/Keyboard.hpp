/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- GRADE_DE_KEYBOARD_HPP_ ----- */
#ifndef GRADE_DE_KEYBOARD_HPP_
#define GRADE_DE_KEYBOARD_HPP_

/* ----- INCLUDEs ----- */
#include <SDL2/SDL.h>
#include <functional>
#include <memory>
#include <utility>
#include <vector>

/* ----- CLASS ----- */
namespace sdl
{
    class Keyboard
    {
        public:
            Keyboard();
            ~Keyboard() = default;

            void bindOnPressed(SDL_Scancode key, std::function<void(double)> callback);
            void bindOnReleased(SDL_Scancode key, std::function<void(double)> callback);
            void unbindOnPressed(SDL_Scancode key);
            void unbindOnReleased(SDL_Scancode key);
            void update(double deltaTime);
            void clear();

        private:
            std::vector<Uint8> _oldKeyboardState;
            std::vector<std::pair<SDL_Scancode, std::function<void(double)>>> _pressed;
            std::vector<std::pair<SDL_Scancode, std::function<void(double)>>> _released;
    };
}; // namespace sdl

/* ----- GRADE_DE_KEYBOARD_HPP_ ----- */
#endif
