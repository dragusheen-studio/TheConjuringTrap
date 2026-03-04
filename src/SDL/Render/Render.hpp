/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- GRADE_DE_RENDER_HPP ----- */
#ifndef GRADE_DE_RENDER_HPP
#define GRADE_DE_RENDER_HPP

/* ----- INCLUDEs ----- */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SDL/Color/Color.hpp"
#include "SDL/Vector/Vector.hpp"

/* ----- CLASS ----- */
namespace sdl
{
    class Render
    {
        public:
            Render(Vector<int> size, const char *title, sdl::Color clearColor = sdl::Color::BLACK, Vector<int> position = Vector<int>(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED));
            ~Render();

            SDL_Renderer *getRenderer();
            Vector<int> getDimension();

            void clear();
            void present();

        private:
            SDL_Window *_window;
            SDL_Renderer *_renderer;
            Vector<int> _size;
            const char *_title;
            sdl::Color _clearColor;
    };
}; // namespace sdl

/* ----- GRADE_DE_RENDER_HPP ----- */
#endif
