/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDES ----- */
#include "./Render.hpp"

/* ----- CLASS ----- */
namespace sdl
{
    /* ----- DEFAULTs ----- */
    Render::Render(Vector<int> size, const char *title, sdl::Color clearColor, Vector<int> position)
        : _size(size), _title(title), _clearColor(clearColor)
    {
        SDL_Init(SDL_INIT_VIDEO);
        IMG_Init(IMG_INIT_PNG);

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

        _window = SDL_CreateWindow(_title, position.x, position.y, _size.x, _size.y, SDL_WINDOW_SHOWN);
        _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    }

    Render::~Render()
    {
        SDL_DestroyRenderer(_renderer);
        SDL_DestroyWindow(_window);
        IMG_Quit();
        SDL_Quit();
    }

    /* ----- GETTERs ----- */
    SDL_Renderer *Render::getRenderer()
    {
        return _renderer;
    }

    sdl::Vector<int> Render::getDimension()
    {
        return _size;
    }

    /* ----- SETTERs ----- */
    void Render::setUseMouse(bool useMouse)
    {
        _useMouse = useMouse;
        SDL_SetRelativeMouseMode(_useMouse ? SDL_TRUE : SDL_FALSE);
    }

    /* ----- FUNCTIONs ----- */
    void Render::clear()
    {
        _clearColor.apply(*this);
        SDL_RenderClear(_renderer);
    }

    void Render::present()
    {
        SDL_RenderPresent(_renderer);
    }
}; // namespace sdl
