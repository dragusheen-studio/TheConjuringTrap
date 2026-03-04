/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- GRADE_DE_COLOR_HPP_ ----- */
#ifndef GRADE_DE_COLOR_HPP_
#define GRADE_DE_COLOR_HPP_

/* ----- INCLUDEs ----- */
#include <SDL2/SDL.h>

/* ----- CLASS ----- */
namespace sdl
{
    class Render;

    class Color
    {
        public:
            Color(int r, int g, int b, int a = 255);
            ~Color() = default;

            int r;
            int g;
            int b;
            int a;

            Color &operator*=(const double value);
            Color operator*(const double value);

            void apply(Render &render);

            static const Color BLACK;
            static const Color WHITE;
            static const Color RED;
            static const Color GREEN;
            static const Color BLUE;
            static const Color YELLOW;
            static const Color MAGENTA;
            static const Color CYAN;
            static const Color TRANSPARENT;
    };
}; // namespace sdl

/* ----- GRADE_DE_COLOR_HPP_ ----- */
#endif
