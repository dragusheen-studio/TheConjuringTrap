/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include "./Texture.hpp"
#include <iostream>

/* ----- CLASS ----- */
namespace sdl
{
    /* ----- DEFAULTs ----- */
    Texture::Texture(sdl::Render &render, const std::string &path)
        : _texture(nullptr), _size(0, 0)
    {
        SDL_Surface *tempSurface = IMG_Load(path.c_str());
        if (!tempSurface) throw Error(std::string("Erreur de chargement: ") + path, "Texture::Texture");

        SDL_Surface *surface = SDL_ConvertSurfaceFormat(tempSurface, SDL_PIXELFORMAT_RGBA32, 0);
        SDL_FreeSurface(tempSurface);

        _texture = SDL_CreateTextureFromSurface(render.getRenderer(), surface);
        _size.x = surface->w;
        _size.y = surface->h;

        _pixelCache.resize(_size.x * _size.y, sdl::Color::BLACK);

        Uint32 *pixels = (Uint32 *)surface->pixels;

        for (int y = 0; y < _size.y; y++) {
            for (int x = 0; x < _size.x; x++) {
                Uint32 pixelColor = pixels[y * _size.x + x];
                Uint8 r, g, b, a;
                SDL_GetRGBA(pixelColor, surface->format, &r, &g, &b, &a);
                _pixelCache[y * _size.x + x] = sdl::Color(r, g, b, a);
            }
        }

        SDL_FreeSurface(surface);
    }

    Texture::~Texture()
    {
        if (_texture) SDL_DestroyTexture(_texture);
    }

    /* ----- GETTERs ----- */
    SDL_Texture *Texture::getSDLTexture() const
    {
        return _texture;
    }

    int Texture::getWidth() const
    {
        return _size.x;
    }

    int Texture::getHeight() const
    {
        return _size.y;
    }

    sdl::Vector<int> Texture::getSize() const
    {
        return _size;
    }

    /* ----- FUNCTIONs ----- */
    sdl::Color Texture::getPixel(int x, int y) const
    {
        if (x < 0 || x >= _size.x || y < 0 || y >= _size.y)
            return sdl::Color::BLACK;
        return _pixelCache[y * _size.x + x];
    }

    void Texture::applyOnTexture(sdl::Color &color)
    {
        SDL_SetTextureColorMod(_texture, color.r, color.g, color.b);
    }
}; // namespace sdl
