/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- GRADE_DE_TEXTURE_MANAGER_HPP_ ----- */
#ifndef GRADE_DE_TEXTURE_MANAGER_HPP_
#define GRADE_DE_TEXTURE_MANAGER_HPP_

/* ----- INCLUDEs ----- */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include <string>
#include <unordered_map>
#include "SDL/Render/Render.hpp"
#include "SDL/Texture/Texture.hpp"
#include "Utils/Path/Path.hpp"

/* ----- CLASS ----- */
namespace sdl
{
    class TextureManager
    {
        public:
            static TextureManager &get();
            ~TextureManager() = default;

            std::shared_ptr<sdl::Texture> get(sdl::Render &render, const std::string &path, bool usePrefix = true);

        private:
            std::string _prefix;
            std::unordered_map<std::string, std::shared_ptr<sdl::Texture>> _textures;

            TextureManager();
    };
}; // namespace sdl

/* ----- GRADE_DE_TEXTURE_MANAGER_HPP_ ----- */
#endif
