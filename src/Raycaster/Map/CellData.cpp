/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include "./Map.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    /* ----- DEFAULTs ----- */
    Map::CellData::CellData(CellType type, bool isSolid, sdl::Render &render, std::string textureFile)
        : _type(type), _isSolid(isSolid), _textureFile(textureFile), _texture(nullptr)
    {
        if (_textureFile != "") _texture = sdl::TextureManager::get().get(render, _textureFile);
    }

    /* ----- GETTERs ----- */
    CellType Map::CellData::getType() const
    {
        return _type;
    }

    bool Map::CellData::isSolid() const
    {
        return _isSolid;
    }

    std::shared_ptr<sdl::Texture> Map::CellData::getTexture() const
    {
        if (!_texture) return nullptr;
        return _texture;
    }
}; // namespace Raycaster
