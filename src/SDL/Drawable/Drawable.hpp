/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- GRADE_DE_DRAWABLE_HPP_ ----- */
#ifndef GRADE_DE_DRAWABLE_HPP_
#define GRADE_DE_DRAWABLE_HPP_

/* ----- INCLUDEs ----- */
#include <SDL2/SDL.h>
#include "SDL/Render/Render.hpp"

/* ----- CLASS ----- */
namespace sdl
{
    class Drawable
    {
        public:
            Drawable() = default;
            ~Drawable() = default;

            virtual void draw(Render &render);
    };
}; // namespace sdl

/* ----- GRADE_DE_DRAWABLE_HPP_ ----- */
#endif
