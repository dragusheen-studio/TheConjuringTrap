/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include "./Color.hpp"
#include "SDL/Render/Render.hpp"

/* ----- CLASS ----- */
namespace sdl
{
    /* ----- DEFAULTs ----- */
    Color::Color(int r, int g, int b, int a)
        : r(r), g(g), b(b), a(a)
    {
    }

    /* ----- OPERATORs ----- */
    Color &Color::operator*=(const double value)
    {
        r *= value;
        g *= value;
        b *= value;
        return *this;
    }

    Color Color::operator*(const double value)
    {
        return Color(r * value, g * value, b * value);
    }

    /* ----- FUNCTIONs ----- */
    void Color::apply(Render &render)
    {
        SDL_SetRenderDrawColor(render.getRenderer(), r, g, b, a);
    }

    /* ----- STATICs ----- */
    const Color Color::BLACK = Color(0, 0, 0);
    const Color Color::WHITE = Color(255, 255, 255);
    const Color Color::RED = Color(255, 0, 0);
    const Color Color::GREEN = Color(0, 255, 0);
    const Color Color::BLUE = Color(0, 0, 255);
    const Color Color::YELLOW = Color(255, 255, 0);
    const Color Color::MAGENTA = Color(255, 0, 255);
    const Color Color::CYAN = Color(0, 255, 255);
    const Color Color::TRANSPARENT = Color(0, 0, 0, 0);
}; // namespace sdl
