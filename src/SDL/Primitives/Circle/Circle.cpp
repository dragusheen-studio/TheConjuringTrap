/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include "./Circle.hpp"

/* ----- CLASS ----- */
namespace sdl
{
    /* ----- DEFAULTs ----- */
    Circle::Circle(int radius, Vector<double> position, Color color)
        : Movable(position), _radius(radius), _color(color)
    {
    }

    /* ----- DRAWABLE ----- */
    void Circle::draw(Render &render)
    {
        _color.apply(render);

        int x = _radius - 1;
        int y = 0;
        int dx = 1;
        int dy = 1;
        int err = dx - (_radius << 1);
        SDL_Renderer *renderer = render.getRenderer();

        while (x >= y) {
            SDL_RenderDrawLine(renderer, _position.x + x, _position.y + y, _position.x - x, _position.y + y);
            SDL_RenderDrawLine(renderer, _position.x - y, _position.y + x, _position.x + y, _position.y + x);
            SDL_RenderDrawLine(renderer, _position.x - y, _position.y - x, _position.x + y, _position.y - x);
            SDL_RenderDrawLine(renderer, _position.x - x, _position.y - y, _position.x + x, _position.y - y);

            if (err <= 0) {
                y++;
                err += dy;
                dy += 2;
            }
            if (err > 0) {
                x--;
                dx += 2;
                err += dx - (_radius << 1);
            }
        }
    }
}; // namespace sdl
