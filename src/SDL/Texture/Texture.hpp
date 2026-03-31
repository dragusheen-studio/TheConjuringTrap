/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- GRADE_DE_TEXTURE_HPP_ ----- */
#ifndef GRADE_DE_TEXTURE_HPP_
#define GRADE_DE_TEXTURE_HPP_

/* ----- INCLUDEs ----- */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include <string>
#include <vector>
#include "SDL/Color/Color.hpp"
#include "SDL/Error/Error.hpp"
#include "SDL/Render/Render.hpp"
#include "SDL/Vector/Vector.hpp"

/* ----- CLASS ----- */
namespace sdl
{
    class Texture
    {
        public:
            Texture(sdl::Render &render, const std::string &path);
            ~Texture();

            SDL_Texture *getSDLTexture() const;
            sdl::Vector<int> getSize() const;
            int getWidth() const;
            int getHeight() const;

            void setColor(sdl::Color &color);
            void setOpacity(int opacity);
            void setBlendMode(SDL_BlendMode blendMode);

            sdl::Color getPixel(int x, int y) const;

        private:
            SDL_Texture *_texture;
            sdl::Vector<int> _size;
            std::vector<sdl::Color> _pixelCache;
    };
}; // namespace sdl

/* ----- GRADE_DE_TEXTURE_HPP_ ----- */
#endif
