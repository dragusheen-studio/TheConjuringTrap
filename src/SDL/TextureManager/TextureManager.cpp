/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include "./TextureManager.hpp"

/* ----- CLASS ----- */
namespace sdl
{
    /* ----- DEFAULTs ----- */
    TextureManager::TextureManager()
        : _prefix("./assets/images/")
    {
    }

    TextureManager &TextureManager::get()
    {
        static TextureManager instance;
        return instance;
    }

    /* ----- FUNCTIONs ----- */
    std::shared_ptr<sdl::Texture> TextureManager::get(sdl::Render &render, const std::string &path, bool usePrefix)
    {
        const std::string finalPath = usePrefix ? _prefix + path : path;
        if (_textures.find(finalPath) == _textures.end()) _textures[finalPath] = std::make_shared<sdl::Texture>(render, finalPath);
        return _textures[finalPath];
    }
}; // namespace sdl
