/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/* ----- INCLUDEs ----- */
#include "./Indicator.hpp"

/* ----- CLASS ----- */
namespace Raycaster
{
    /* ----- DEFAULTs ----- */
    Indicator::Indicator(sdl::Render &render, sdl::Vector<double> position, const std::string &iconPath)
        : sdl::Movable(position)
    {
        _bg = sdl::TextureManager::get().get(render, "ui/bg.png");
        _bg->setOpacity(150);

        _icon = sdl::TextureManager::get().get(render, "ui/" + iconPath);
        _icon->setBlendMode(SDL_BLENDMODE_BLEND);

        onTransformChanged();
    }

    /* ----- DRAWABLE ----- */
    void Indicator::draw(sdl::Render &render)
    {
        SDL_RenderCopy(render.getRenderer(), _bg->getSDLTexture(), NULL, &_bgRect);
        SDL_RenderCopy(render.getRenderer(), _icon->getSDLTexture(), NULL, &_iconRect);
    }

    /* ----- MOVABLE ----- */
    void Indicator::onTransformChanged()
    {
        _bgRect = {(int)_position.x, (int)_position.y, _size, _size};
        _iconRect = {(int)_position.x + _iconPadding, (int)_position.y + _iconPadding, _size - (_iconPadding * 2), _size - (_iconPadding * 2)};
    }

    /* ----- FUNCTIONs ----- */
    void Indicator::update(double deltaTime, const Player *player)
    {
    }
}; // namespace Raycaster
